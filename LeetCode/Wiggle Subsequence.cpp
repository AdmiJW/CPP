#include <vector>
using namespace std;


class Solution {
public:
	//	Initial solution - Using Finite State Machine and DP
	int wiggleMaxLength(vector<int>& nums) {
		int prevInc = INT32_MAX;
		int prevDec = INT32_MIN;
		int incLen = 0, decLen = 0;

		for (int i : nums) {
			int currInc = prevInc, currDec = prevDec;
			int incLen2 = incLen, decLen2 = decLen;

			//===============================
			//	Updating the Increment state
			//===============================
			//	The decrement state can transition to current increment state thru this number, and it is
			//	worthy to do so (after transition, length is higher)
			currInc = i;
			if (i > prevDec && decLen + 1 > incLen)
				incLen2 = decLen + 1;

			//===============================
			//	Updating the Decrement State
			//===============================
			//	The increment state can transition to current decrement state thru this number, and it is
			//	worthy to do so (after transition, length is higher)
			currDec = i;
			if (i < prevInc && incLen + 1 > decLen)
				decLen2 = incLen + 1;

			//=============================================
			//	DP - Current becomes previous in next iter
			//=============================================
			prevInc = currInc; prevDec = currDec;
			incLen = incLen2; decLen = decLen2;
		}
		return max(incLen, decLen);
	}


	//	Space optimized DP solution
	int wiggleMaxLength2(vector<int>& nums) {
		if (nums.size() < 2) return nums.size();

		int down = 1, up = 1;
		for (int i = 1; i < nums.size(); ++i) {
			if (nums[i] > nums[i - 1]) up = down + 1;
			else if (nums[i] < nums[i - 1]) down = up + 1;
		}
		return max(down, up);
	}


	//	Pure greedy solution
	int wiggleMaxLength3(vector<int>& nums) {
		if (nums.size() < 2) return nums.size();

		int prevdiff = nums[1] - nums[0];
		int count = prevdiff == 0 ? 1 : 2;		//	If diff = 0, means front 2 is same, only 1 can picken.

		for (int i = 2; i < nums.size(); ++i) {
			int diff = nums[i] - nums[i - 1];
			if ((diff > 0 && prevdiff <= 0) || (diff < 0 && prevdiff >= 0)) {
				++count;
				prevdiff = diff;
			}
		}
		return count;
	}
};