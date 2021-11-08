#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/unique-binary-search-trees/

/*
 * 	A Dynamic Programming question. We can divide the problem into subproblems.
 *
 * 	A binary search tree has the following properties: The left node must be less than the parent node, and the right node must be more than
 * 	the parent node. Therefore, we shall iterate through all possibilities of selecting the parent node from 1 to n, and ask ourselves:
 *
 * 		If I select this number as parent node, how many combinations will form at the left subtree, and how many combinations will
 * 		form at the right subtree?
 *
 * 	First, we know that all the elements in the BST is ranged from 1 to n. Therefore for a constant c selected as parent node, then
 * 	the left subtree range must be enclosed to only [1, c), and right subtree range is enclosed to (c, n]
 * 	How many nodes in the range? Just do difference subtraction, c - 1 for left subtree, n - c for right subtree.
 *
 * 	Therefore there are n ways we can select a node as parent, and for each case, we can easily compute how many nodes goes to the left and
 * 	how many nodes goes to the right. A smaller yet similar question arises though, how many combinations can the left subtree and right
 * 	subtree make?
 *
 *  Therefore we can do a bottom up approach to tackle the problem. The base case is, given 0 nodes, there is 1 way to form BST (Which is do nothing)
 *  Then for n = 1, We have 1 ways to select a node as parent (1 itself), and 0 nodes goes to left as well as right. Since there is 1 way to form
 *  left and right subtree (0 nodes), we find out it is 1 way to form with n = 1.
 *
 *  For n = 2, we have 2 ways to select a node as parent, (1 or 2).
 *  If parent = 1, then 1 nodes goes to right (2), and there is 1 way to form subtree to both left and right
 *  If parent = 2, then 1 nodes goes to left  (1), and there is 1 way to form subtree to both left and right
 *  Sum those combinations up, we get 2 ways!
 *
 *  Similarly for n = 3,
 *  If parent = 1, then 0 nodes goes left, 2 nodes goes right. Using data computed before, there is (1) * (2) ways to form subtree
 *  If parent = 2, then 1 nodes goes left, 1 nodes goes right. there is (1) * (1) ways to form subtree
 *  If parent = 3, then 2 nodes goes left, 0 nodes goes right. there is (2) * (1) ways to form subtree
 *  Sum those combinations, we get 6 ways!
 *
 */


class Solution {
public:

	// Pure Recursive solution - Time limit Exceeded
	int numTrees(int n) {
		if (n <= 1) return 1;

		int res = 0;
		for (int i = 1; i <= n; ++i)
			res += numTrees(i - 1) * numTrees(n - i);

		return res;
	}


	vector<int> memoi;

	// What's important is the number of nodes available
	// Memoization (You can also use Iterative DP)
	int numTreesDP(int n) {
		if (n <= 0) return 1;
		if (n <= memoi.size()) return memoi[n-1];

		int res = 0;
		for (int i = 1; i <= n; ++i)
			res += numTreesDP(i - 1) * numTreesDP(n - i);

		// Memoi
		if (n > memoi.size()) memoi.push_back(res);
		return res;
	}
};