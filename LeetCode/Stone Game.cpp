#include <vector>
using namespace std;

//https://leetcode.com/problems/stone-game/
/*
 * 	This is a Dynamic Programming problem (Unless you lucky or pro in math, and guess that Alex always wins)
 *
 * 	First of all, starting out the game with Alex, he can pick the leftmost or rightmost stone. Then, opponent
 *  will face a similar problem as before, see:
 *
 *  	Say there are 5 piles of stones, indexed from 0 to 4
 *
 *  		>	If Alex picks leftmost stone first, opponent is left with 4 piles, starting from index 1
 *  		>	If Alex picks rightmost stone, opponent is left with 4 piles, starting from index 0
 *
 *  The idea is, we are back to original problem statement where we just have to think from opponent perspective,
 *  that which stone to actually pick to gain best advantage.
 *  In other words, the opponent can pick leftmost or rightmost stone too, and Alex will be left with 3 piles and so on.
 *
 *  Therefore, we came up with DP solution, where we can start calculating subpiles first up to the original problem statmeent
 *  of N piles.
 *
 *  Also, we can use single integer to represent the game state. Positive means Alex is at advantage while Negative means
 *  Lee is at advantage. For example, 5 means Alex is 5 points ahead of Lee.
 *
 *  Since problem states there is always even piles of stone, Lee always pick the last pile. Therefore, the DP array intiially
 *  with pilesize of 1, is original values but negated.
 *
 *  Then, on pilesize 2, Alex's turn. If he picks leftmost stone, check the dp array at index [i+1]. If he picks rightmost
 *  stone, check the dp array at index[i]. Choose whatever Alex will have most advantage.
 */

class Solution {
public:
	
    // DP solution - Work from bottom up, from various subpile sizes
    bool stoneGame(vector<int>& piles) {
        const int len = piles.size();
        vector<int> dp(len, 0);

        // Intiialize DP as if considering subpile of size 1 - When size 1 - Its Lee's turn
        for (int i = 0; i < len; ++i)
            dp[i] = -piles[i];

        // Consider all subsequent pile sizes
        for (int size = 2; size <= len; ++size) {
            // Alex's Turn. He wants to be as positive as possible
            if (size % 2 == 0) {
                for (int left = 0; left <= len - size; ++left) {
                    dp[left] = max(
                        piles[left] + dp[left + 1], 			// Taking leftmost stone
                        piles[left + size - 1] + dp[left]		// Taking rightmost stone
                    );
                }
            }
            // Lee's Turn. He wants to be as negative as possible
            else {
                for (int left = 0; left <= len - size; ++left) {
                    dp[left] = min(
                        -piles[left] + dp[left + 1], 			// Taking leftmost stone
                        -piles[left + size - 1] + dp[left]		// Taking rightmost stone
                    );
                }
            }
        }

        return dp[0] > 0;	// Check if Alex has point advantage (Wins)
    }
};