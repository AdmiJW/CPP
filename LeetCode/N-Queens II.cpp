#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/n-queens-ii/
/*
 * 	This is the same as N-Queens problem (Backtracking), except it only require us to give the number of solution
 * 	this time.
 *
 * 	The same rule applies as in the problem N-Queens. I recommend you to refer that in Hard > N_Queens
 * 	Here I use 3 Hashsets to represent the occupied column, diagonal and antidiagonal for backtracking
 *
 *	Note that this code is slow for some reasons especially in C++. For top speed, you may prompt for bitwise solution to represent which
 *	cols, diagonals and antidiagonals had been visited.
 */

class Solution {
public:
	int totalNQueens(int n) {
		unordered_set<int> cols;
		unordered_set<int> diags;
		unordered_set<int> antidiags;
		return recurse(0, 0, n, n, cols, diags, antidiags);
	}


	int recurse(int r, int c, int n, int q, unordered_set<int>& cols, unordered_set<int>& diags, unordered_set<int>& antidiags) {
		if (!q) return 1;		//	All queens successfully placed. 1 Solution found
		if (r >= n) return 0;	//	Otherwise we ran out of grids. Return 0 solution
	
		int next_r = r + (c + 1) / n;
		int next_c = (c + 1) % n;

		int res = 0;
		//	Attempts to place queen
		if (!cols.count(c) && !diags.count(r - c) && !antidiags.count(r + c)) {
			cols.insert(c);
			diags.insert(r - c);
			antidiags.insert(r + c);
			res += recurse(r + 1, 0, n, q - 1, cols, diags, antidiags);
			cols.erase(c);
			diags.erase(r - c);
			antidiags.erase(r + c);
		}
		//	Not placing queen
		return res + recurse(next_r, next_c, n, q, cols, diags, antidiags);
	}
};