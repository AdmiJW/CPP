#include <queue>
using namespace std;

// https://leetcode.com/problems/leaf-similar-trees/
/*
 * A binary tree, depth first search problem.
 * 
 * Perform a DFS on the first tree, record all the leaves in a linear data structure like a queue.
 * Then perform a DFS on the second tree, compare the leaves with the queue. 
 */



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};



class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        queue<TreeNode*> leaves;
        dfsAndAddLeaves(root1, leaves);
        return dfsAndCompareLeaves(root2, leaves) && leaves.empty();
    }

    void dfsAndAddLeaves(TreeNode* root, queue<TreeNode*>& leaves) {
        if (!root) return;
        if ( !(root->left) && !(root->right)) leaves.push(root);
        dfsAndAddLeaves(root->left, leaves);
        dfsAndAddLeaves(root->right, leaves);
    }

    bool dfsAndCompareLeaves(TreeNode* root, queue<TreeNode*>& leaves) {
        if (!root) return true;
        if (!(root->left) && !(root->right)) {
            if (leaves.empty()) return false;
            if (root->val != leaves.front()->val) return false;
            leaves.pop();
            return true;
        }

        return dfsAndCompareLeaves(root->left, leaves) && dfsAndCompareLeaves(root->right, leaves);
    }
}