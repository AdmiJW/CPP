#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/
/*
 * This is a String sorting, greedy problem.
 *
 * We have to reduce the string s until no two character's frequency are the same (Unless it is 0). If we
 * first process it into an array of frequencies, then the problem are reduced to simply total amount we have
 * to decrease so that no two elements in array are the same.
 *
 * In my solution, I will sort the frequencies, then iterate over the frequencies. For each frequency:
 * 		> If the frequency is same as previous (Recall array is sorted), then we have to reduce the current
 * 		  frequencies by deleting this character. I do this by iterating the array again backwards, and find the
 * 		  maximum possible frequency that I can reduce it to.
 *
 * 		Eg: [1,2,4,5,5]
 * 					 ^
 * 		Since 5's previous is also 5, I have to reduce this frequency. I will try 4 first, but soon, I will encounter
 * 		the 4 at index 2. Therefore, the final frequency will be 3.
 *
 * The time complexity is O(N + K^2 log K) where K is number of unique characters.
 */

class Solution {
public:
    int minDeletions(string s) {
        // Obtain frequency array
        vector<int> freq = vector<int>(26, 0);
        for (char c : s) ++freq[c - 'a'];
        // Sort the frequencies
        sort(freq.begin(), freq.end());

        int res = 0;

        for (int i = 1; i < 26; ++i) {
            if (freq[i] == 0) continue;

            // Collided frequency. We need to find how many to delete
            if (freq[i] == freq[i - 1]) {
                int remain = freq[i] - 1;

                for (int j = i - 1; j >= 0; --j)
                    if (remain == freq[j]) remain = max(0, freq[j] - 1);

                res += freq[i] - remain;
                freq[i] = remain;
            }
            // Sort again due to manipulating the frequency
            sort(freq.begin(), freq.end());
        }
        return res;
    }
};