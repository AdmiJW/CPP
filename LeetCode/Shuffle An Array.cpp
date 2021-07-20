#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

//https://leetcode.com/problems/shuffle-an-array/
/*
 * 	This is a Shuffle problem, which usually we use the popular shuffling algorithm: Fisher Yates Algorithm
 *
 * 	For the details, see Topics > Algorithms > Fisher_Yates_Shuffle.java
 */

class Solution {
public:
	int length;
	vector<int> ori;
	vector<int> perm;

	Solution(vector<int>& nums) {
		length = nums.size();
		srand(time(nullptr));
		ori = vector<int>(nums);
		perm = vector<int>(ori);
	}

	vector<int> reset() {
		perm = vector<int>(ori);
		return perm;
	}

	vector<int> shuffle() {
		for (int i = length - 1; i > 0; --i) {
			int j = rand() % (i + 1);
			int temp = perm[i];
			perm[i] = perm[j];
			perm[j] = temp;
		}
		return perm;
	}

};