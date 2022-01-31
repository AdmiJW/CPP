
#include <vector>
using namespace std;

//https://leetcode.com/problems/richest-customer-wealth/
/*
 * Simple matrix summation problem
 *
 * Sum each row. Return the maximum.
 */


class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
		int res = 0;

		for (auto& cust : accounts) {
			int sum = 0;
			for (int amt : cust) sum += amt;
			res = max(res, sum);
		}
		return res;
    }
};