#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/partition-labels/
/*
 * 	This is a Greedy question.
 * 	We have to partition the strings (Meaning to split the strings, no rearranging), such that each part's character cannot occur
 * 	in another part.
 *
 * 	For me, we need to get more information regarding the string itself. Therefore, here I obtained the frequency of each character
 * 	in String S, at most 26 lowercase letters.
 *
 * 	Now, I will also have a Set, where the characters included in the current partition are put inside it.
 *
 * 	So the algorithm goes as this:
 *
 * 		For each character in S:
 * 			if the character is not present in Set, add it
 * 			Since we used this current character, decrement the frequency count in the freq table
 * 			If the character in freq table hit 0, means we exhausted this character. At this point, remove the character from the
 * 			Set
 * 			Now, if the set is empty (Means a valid partition is formed), add to the result the length of the partition
 *
 *
 *
 * 	================================================================
 *
 * 	Instead of using the frequency of each character, we can also use the Last index of occurrence of this character to
 * 	solve the problem.
 *
 * 	For each character:
 * 		If we have reached the current partition's last length for partitioning, then add the result this length of partition
 * 		Otherwise, find the last occurrence of this current character.
 * 		We will keep a variable to keep track of the largest index of the last character included in the current partition.
 * 		If it is larger, then we overwrite it.
 *
 *
 */



class Solution {
public:
    vector<int> partitionLabels(string s) {
        int index[26] = {};
        vector<int> res;

        // Obtain last most index
        for (int i = 0; i < s.length(); ++i) index[s[i] - 'a'] = i;

        int until = 0;
        int size = 0;

        // Second scan to partition strings
        for (int i = 0; i < s.length(); ++i) {
            ++size;
            char c = s[i];

            // Update where the partition should last
            until = max(until, index[c - 'a']);

            // If the partition is complete, update.
            if (until == i) {
                res.push_back(size);
                size = 0;
                until = i + 1;
            }
        }

        return res;
    }
};