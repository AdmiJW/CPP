#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
		unordered_map<int, int> mod;
		int sum = 0;

		mod[0] = 0;

		for (int i = 0; i < nums.size(); ++i) {
			sum += nums[i];

			if (!mod.count(sum % k)) mod[sum% k] = i + 1;
			else if (mod[sum% k] < i) return true;
		}

		return false;
    }
};