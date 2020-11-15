#include <vector>

//https://leetcode.com/problems/range-sum-of-bst/

/*
*   This is a BST traversal problem, which is easily solved using recursion or any iteration method of Stack or Queue
* 
*   At each recursion call, we receive a node. Since we know the left and right boundaries, we check:
*   If the node's value is in range, this node value must be included in sum.
*   Then, we know left subtree all values must be less than this node value, and reverse for right subtree.
* 
*   If the left boundary is still lower than the node value, then some node in left subtree may be valid node. Recurse
*   left
*   If the right boundary is still higher than the node value, then some node in right subtree may be valid node.
*   Recurse right
* 
*   ================================================================
* 
*   The very same can be done iteratively, usign Stack (DFS) or Queue (BFS)
* 
*/

struct TreeNode {
int val;
TreeNode* left;
TreeNode* right;
TreeNode() : val(0), left(nullptr), right(nullptr) {}
TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        if (!root) return 0;

        int sum = root->val >= low && root->val <= high? root->val: 0;
        if (root->val > low) sum += rangeSumBST(root->left, low, high);
        if (root->val < high) sum += rangeSumBST(root->right, low, high);
        return sum;
    }

    int rangeSumBST2(TreeNode* root, int low, int high) {
        if (!root) return 0;

        int sum = 0;
        std::vector<TreeNode*> stack;
        TreeNode* node;
        stack.push_back(root);

        while (!stack.empty()) {
            node = stack.back();
            stack.pop_back();

            sum += node->val >= low && node->val <= high ? node->val : 0;
            
            if (node->left && node->val > low ) stack.push_back(node->left);
            if (node->right && node->val < high ) stack.push_back(node->right);
        }

        return sum;
    }
};