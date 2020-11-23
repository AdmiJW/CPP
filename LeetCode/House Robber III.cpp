#include <utility>

//https://leetcode.com/problems/house-robber-iii/

/*
 * 	This is a Binary Tree, Depth First Search Problem with a little Dynamic Programming element in it.
 *
 * 	Binary Tree itself is a recursive data structure. We should be using recursion here.
 *
 * 	Now, at each node, we have 2 choices:
 * 		>	Rob the node.
 * 		>	Not rob the current node.
 * 	And we essentially have to return the maximum profit that will gained by robbing this tree.
 *
 *  If we dont want to rob this node, then we can rob the children nodes. Children node recursion will return the maximum
 *  profit that can be gained by robbing them and its children. Therefore we'll just add the 2 profits and return.
 *
 * 	If we want to rob this node, that means the children node are locked. We must only at most rob the grandchildren
 *  nodes. We cannot rob the direct children node. Since the children nodes know about the maximum profit when robbing
 *  grandchildren, perhaps we can retrieve that maximum profit information from child node recursion itself?
 *
 *  Therefore, a recursion call should return 2 values:
 *  	>	Max profit with current node robbed		-	Node.val + children's NoRob value
 *  	>	Max profit without current node robbed	-	children's Rob value OR children's NoRob value
 *
 *  Remember that in max profit without current node robbed, we can choose to rob the direct children, or NOT rob
 *  the direct children. See case:
 *
 *  			(4)
 *  		  (1)
 *  		(2)
 *  	  (3)
 *
 *  In this tree, max profit is 7 obtained by (4) and (3). See that in node (1),
 *  	>	It should return rob current node value of 4
 *  	>	However for NOT rob curent node value, it should return 3 as well, not direct children of 2. Therefore it
 *  		should be MAX( children rob, children not rob )
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
	int rob(TreeNode* root) {
		auto res = recurse(root);

		return std::max(res.first, res.second);
	}

	/*
		THe recursive algorithm
		Will return a STL pair object. Where
			>	First element is the max profit with robbing the child node
			>	Second element is the max profit without robbing the child node, which is max of robbing and not robbing
	*/
	std::pair<int,int> recurse(TreeNode* node) {
		if (!node) return std::make_pair(0, 0);

		auto left = recurse(node->left);
		auto right = recurse(node->right);

		return std::make_pair(
			node->val + left.second + right.second,
			std::max(left.first, left.second) + std::max(right.first, right.second)
		);
	}
};