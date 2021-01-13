#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/boats-to-save-people/
/*
 * 	This is a Two pointers, greedy problem.
 *
 * 	Say we are trying to fit peoples into boat. Each boat can sit only 2 people, and has a weight limit on it!
 *
 * 	How can you fit with minimum boats?
 * 	The idea is:
 * 		>	Say we have selected a person to sit in the boat. Say he has weight of W1. Now, we want to select another
 * 			person to sit in the same boat. If we are greedy, we would want to fit the other person to be as close
 * 			to the limit as possible! Find the person with weight W2, which W1 + W2 is closest, but not exceeding
 * 			limit!
 * 		>	If the lighest person we pick can already fit in the same boat as heaviest person, that means any person
 * 			can already fit with the lighest person already. We might as well fit the heaviest person with it to avoid
 * 			considering heaviest person in the future.
 *
 * 	Thus, sort the peoples by weight. Initialize the two pointers to the start and end of the array respectively.
 *
 * 	Initially it points at the lightest and heaviest person. Therefore, try to fit them into same boat:
 * 		>	If limit is exceeded, it means that the heaviest person must only can be sitting on the boat alone.
 * 			The currently selected heaviest person can't even sit with the lighest person!
 *
 * 		>	If limit is not exceeded, sure we'll put them into same boat. Proceed to the second lightest person and
 * 			second heaviest person
 *
 */


class Solution {
public:
	int numRescueBoats(vector<int>& people, int limit) {
		sort(people.begin(), people.end());

		int left = 0, right = people.size() - 1;
		int boats = 0;

		while (left < right) {
			if (people[left] + people[right] <= limit) {
				++left;
				--right;
			}
			else --right;

			++boats;
		}
		//  If the left and right pointer is at same location.
		//  We still has one lone person haven't boarded any boats
		return left == right ? boats + 1 : boats;
	}
};