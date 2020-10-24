
#include <vector>
#include <algorithm>
#include <iostream>

/*
 * 	This is a greedy, sorting problem.
 *
 * 	Given the actions that we could perform on a token:
 * 	>	Flip DOWN the token, so we gain 1 Point but lose token[i] Power
 * 	>	Flip UP the token, so we gain token[i] Power but lose 1 Point
 *
 * 	If we are facing this choice, we would want to always flip DOWN the least power costly token first, and if needed,
 * 	flip UP only the most power costly token.
 *
 * 	We will be sorting the tokens, and keep 2 pointers at both ends. On the start pointer is the token we'll most likely
 * 	flip DOWN, and on the end pointer is the token we'll most likely flip UP.
 * 	Keep flipping the token DOWN until we are out of POWER, save the state if it is greater than last score, then
 * 	attempt to flip up until we have enough power again, or run out of scores or token.
 * 	Check at the end of flipping UP, if we have enough power to keep playing. If it's not, then immediately return the
 * 	maximum score.
 */

class Solution {
public:
    int bagOfTokensScore(std::vector<int>& tokens, int P) {
        int len = tokens.size();
        if (len <= 0) return 0;
        std::vector<int>::iterator head = tokens.begin(), tail = tokens.end() - 1;
        int res = 0;
        int score = 0;

        std::sort(tokens.begin(), tokens.end());

        //  While tail pointer is greater or equal to head pointer. We could flip DOWN the token pointed by tail pointer as well
        while (tail - head >= 0) {

            //  Keep flipping DOWN tokens as much as possible
            while (tail - head >= 0 && P >= *head) {
                P -= *head;
                score++;
                head++;

            }

            //  Save the state if it is greater
            res = std::max(score, res);

            //  Keep flipping UP tokens until it is enough to flip HEAD token
            while (tail - head > 0 && score > 0 && P < *head) {
                P += *tail;
                score--;
                tail--;
            }

            //  Impossible to continue playing.
            if (head != tokens.end() && P < *head) {
                return res;
            }
        }
        return res;
    }
};