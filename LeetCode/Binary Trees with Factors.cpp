#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/binary-trees-with-factors/
/*
 * 	Turns out, this problem has nothing to do with binary trees, but instead, Dynamic Programming
 *
 * 	Well, for each value n, what valid binary trees that we can form?
 *
 * 	First of all, the tree can consist only of 1 node: n only. Therefore, the number of valid trees
 * 	formed must be at least 1.
 * 	Then, we try to search for it's factors. We know for a fact that it's factors must be smaller than
 * 	n. To find one factor, try to divide n by that number and see if it perfectly divides.
 *
 * 	If we successfully find a pair of factor f where both f and n/f exists in the array, then how many
 * 	binary trees can we form with n as the root we might ask?
 * 	The answer is: (no of bin. tree with f as root) * (no of bin. tree with n/f as root)
 *
 * 	This requires us to know the answer to both child node as root cases beforehand, and that's what
 * 	dynamic programming fits perfectly! Using solutions to subproblems to solve current problem.
 *
 * 	----------------------------------------------
 *
 * 	Sort the array from small to large. Solve the smallest problem first, then proceed to larger value
 * 	of n. When we reached the case of larger value, if there is a factor pair, the cases where
 * 	(no of bin. tree with f as root) and (no of bin. tree with n/f as root) would already be solved,
 * 	since we solve the subproblems from small value of n to large values of n.
 *
 */

typedef long long int LONG;

class Solution {
public:
	int numFactoredBinaryTrees(vector<int>& arr) {
		const int len = arr.size();
		LONG res = 0;
		unordered_map<int, LONG> freq;		//	Record answer: N -> no of bin. trees that can form
		sort(arr.begin(), arr.end());		//	Required for DP: to solve smaller cases first

		for (int i = 0; i < len; ++i) {
			int n = arr[i];
			LONG thisres = 1;				//	By default, the node can form a binary tree with one node only: N

			//	Try to find factor f
			for (int j = i - 1; j >= 0; --j) {
				int m = arr[j];
				if (n % m || !freq.count(n/m) ) continue;

				//	Factor f is found, if n/f is not in array, multiply 0 so it will change nothing
				thisres = (thisres + freq[m] * freq[n / m]) % 1000000007;
			}
			freq[n] = thisres;						//	Record in DP
			res = (res + thisres) % 1000000007;		//	Update global result
		}
		return res;
	}
};