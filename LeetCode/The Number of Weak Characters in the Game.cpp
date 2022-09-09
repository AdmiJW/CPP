#include <vector>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/
/*
 * 	This is a sorting, greedy problem.
 *
 * 	For each character, we want to know it there exists a character that has attack and defense greater than him. Hopefully,
 * 	we could use the information from past interation to know this. How could we achieve that?
 *
 * 	The base idea is to sort the attacks descendingly. In that case, we would know if there is a stronger character for character[i],
 * 	it would only be in c[i-1], c[i-2].....
 *
 *	Like for test case [ [3,6], [5,5], [6,3] ], it will be sorted to [ [6,3], [5,5], [3,6] ].
 *	When we are at [5,5], only [6,3] can be candidate of stronger character, because we know it has stronger attack based on
 *	sorting order.
 *
 *	Therefore, we simply keep a single variable to record the strongest defense value we've seen in past iterations.
 *	In above example at [5,5], the strongest defense value will be '3' from [6,3]. Since defense is lower than [5,5]'s '5',
 *	we know immediately [5,5] can't be a weak character since its defense value is higher than the highest value seen.
 *
 *	What about groups that has same attack value, like [ [5,3], [5,7], [5,4] ]
 *	In case of same attack value, we sort them ascendingly, like [ [5,3], [5,4], [5,7] ].
 *	So that when iterating from left to right, the highestDefense value won't actually make us wrongly determine a weak character
 *	where in reality the stronger character is actually having the same attack value as the accused weak character.
 */

class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        // Sort attack by descendingly,
        // then defense ascendingly (So that in a group of same attack, is not affected by highest defense record) 
        sort(properties.begin(), properties.end(), [](auto& x, auto& y)-> bool {
            if (x[0] == y[0]) return x[1] < y[1];
            return x[0] > y[0];
        });

        int weak = 0;
        int highestDefense = properties[0][1];

        for (auto& c : properties) {
            if (highestDefense > c[1]) ++weak;
            highestDefense = max(highestDefense, c[1]);
        }

        return weak;
    }
};