#include <vector>
using namespace std;

//https://leetcode.com/problems/pascals-triangle/
/*
 * 	This is a Dynamic Programming Problem - Pascal Triangle!
 *
 * 	If we have previous row, we easily compute the next row! THat's it!
 */

class Solution {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> res(numRows, vector<int>());
		res.push_back({ 1 });

		for (int r = 2; r <= numRows; ++r) {
			res.push_back(vector<int>({ 1 }));
			vector<int>& prevrow = res.back();

			for (int i = 0; i < prevrow.size() - 1; ++i)
				res[r-1].push_back(prevrow[i] + prevrow[i+1]);

			res[r - 1].push_back(1);
		}
		return res;
	}
};