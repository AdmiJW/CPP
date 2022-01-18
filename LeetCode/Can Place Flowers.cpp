#include <vector>
#include <cmath>
using namespace std;

//https://leetcode.com/problems/can-place-flowers/
/*
 * 	This can be considered greedy problem.
 *
 * 	Given a flowerpot, I will attempt to put flower in valid spot as soon as I see it.
 * 	This is done by checking 3 things:
 * 		>	Current spot empty
 * 		>	Previous spot empty
 * 		>	Next spot empty
 * 	In edge cases where idx is 0 (No previous) and last spot (No next spot), just take current spot
 * 	instead	as placeholder
 *
 * 	As soon as countdown hits 0, we finished flower and can immediately return
 *
 * 	Notice how we increment index:
 * 		>	If we did place a flower, next spot must be unavailable. Jump to next 2
 * 		>	Otherwise no flower placed. It may be due to previous spot contains flower only (Therefore next spot
 * 			is actually available) or not the case. So it's undeterministic and we have to check next spot.
 */

class Solution {
public:
	bool canPlaceFlowers(vector<int>& flowerbed, int n) {
		const int len = flowerbed.size();

		for (int i = 0; i < len && n != 0; ++i) {
			// Current spot empty, previous & next spot as well
			if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) && (i == len - 1 || flowerbed[i + 1] == 0)) {
				--n;
				flowerbed[i] = 1;
			}
		}

		return false;
	}
};