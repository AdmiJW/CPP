#include <vector>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/unique-binary-search-trees-ii/
/*
 * 	This is a Recursion, (Optional)- DP problem with memoization
 *
 * 	This problem can be first solved using recursion because the input is small enough to contain O(N!)
 *
 * 	Given initial range [1,N], we could attempt all the nodes from 1 to N as our root node.
 * 	Say we picked an integer i as our root. Then, the left subtree will surely contain the nodes from
 * 	1 to i-1, and the right subtree will contain nodes from i+1 to N.
 *
 * 	Notice the above process is not restricted for 1 to N only. It can be used in cases where we need to
 * 	construct the nodes from any range of integer A..B where A <= B. This is the recurrence relation we
 * 	are looking for!
 *
 * 	In each recursion call where we need to find unique BST ranging from A...B:
 * 		>	For each i selected as root node from A...B
 * 			- Query all unique BST in left subtree, ranging A.. i-1
 * 			- Query all unique BST in right subtree, ranging i+1...B
 * 			- Construct root node and append all possible combinations of left and right subtree.
 * 		>	Return the result as a list to upper level of recursion.
 *
 * 	---------------------------
 *
 * 	Notice how the problem can easily be memoized. Say our case N=8, then for example the range 1..2 will be
 * 	queried many times. We can avoid repeated computations using Dynamic Programming's memoization approach
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
	// Memoization solution
	vector<TreeNode*> generateTrees(int n) {
		unordered_map<int, vector<TreeNode*>> memoi;
		return generateTrees(1, n, memoi);
	}

	vector<TreeNode*> generateTrees(int from, int to, unordered_map<int, vector<TreeNode*>>& memoi) {
		// Encode the range [from,to] as a two digit integer.
		int index = from * 10 + to;
		if (memoi.count(index)) return memoi[index];

		if (from > to) {
			memoi[index].push_back(nullptr);
			return memoi[index];
		};

		// Select one node in range to be the root, then recurse for left and right subtree
		for (int i = from; i <= to; ++i) {
			vector<TreeNode*> leftSubtrees = generateTrees(from, i - 1, memoi);
			vector<TreeNode*> rightSubtrees = generateTrees(i + 1, to, memoi);

			for (TreeNode* l : leftSubtrees) {
				for (TreeNode* r : rightSubtrees) {
					TreeNode* root = new TreeNode(i);
					root->left = l;
					root->right = r;
					memoi[index].push_back(root);
				}
			}
		}
		return memoi[index];
	}

	
};