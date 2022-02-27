
#include <list>
#include <vector>
using namespace std;

//https://leetcode.com/problems/maximum-width-of-binary-tree/
/*
*	This is a Tree, Breadth first search, Doubly linked list problem
*	
*	First, you need to realize the way to index each node in one level:
*		Left node = currIndex * 2
*		Right node = currIndex * 2 + 1
*	Results in:
* 
*					(0)
*				(0)		(1)
*		(0)	(1)				(2)	(3)
*	(0) (1) (2) (3)		(4) (5) (6) (7)
* 
*	With this, seems like getting the width is not so hard! In our BFS, we simply store the nodes along with their computed
*	indices. Then, if we are using a data structure that can retrieve both ends in O(1) time, we can quickly compute the width
*	of one level.
* 
*	However, problem arises when the tree is long: Consider a tree where there is always a right node - The indices increases
*	exponentially! 
*	One solution is to "shift" the indices according to the leftmost node. Consider:
* 
*					(0)
*						(1)
*						(2)	(3)
*								(6) (7)
* 
*	You can see, even if (1), (2) and (6) are leftmost node in the level, they still increase at an exponential rate, and that's
*	not good at all.
*	One remedy is to "shift" them! Before iteration of one level, obtain the leftmost node's index as the shift value, so that
*	leftmost node will become index 0:
* 
*					(0)
*						(0)
*						(0)	(1)
*							(0)	(1)
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

	int widthOfBinaryTree(TreeNode* root) {
		list< pair<TreeNode*, long long int> > level;
		long long int res = 0;

		level.push_back({ root, 0 });

		while (level.size()) {
			// Record size.
			res = max(
				res,
				level.back().second - level.front().second + 1
			);
			
			// We have to use shift to prevent overflow
			auto shift = level.front().second;

			// Level traversal.
			for (int i = level.size(); i > 0; --i) {
				auto pop = level.front();
				level.pop_front();

				if (pop.first->left)
					level.push_back({ pop.first->left, (pop.second - shift) * 2});
				if (pop.first->right)
					level.push_back({ pop.first->right, (pop.second - shift) * 2 + 1 });
			}
		}


		return res;
	}
};
