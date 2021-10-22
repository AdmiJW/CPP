#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;


//https://leetcode.com/problems/sort-characters-by-frequency/
/*
 * 	This is a string, sorting problem.
 * 
 *  First of all, we must agree that we have to obtain the information on the frequencies of the character. A minimum of O(N) is required.
 *  One solution is that we could obtain the frequency in <char, int> pair. Eg: <'a', 3> means there are 3 'a' in the string
 *  Then, we sort the pairs using the frequency as the sorting key. At the end, the list would have pairs in descending sorted order.
 *  Finally, append to our result string and return.
 * 
 *  Time complexity is O(N + K log K) where N is length of string, K is the character space, in this case ASCII, thus 127 is adequate
 * 
 *  Note that the similar can also be done using priorityqueue, which also handles the sorting
 * 
 *  ---------------------------------------------------------------------
 * 
 *  To use bucket sort, we need to realize that any character c in the string can only have maximum frequency of s.length. Therefore, 
 *  we can just initialize an bucket array of size s.length + 1, obtain the frequencies of characters, and put the characters into the bucket
 *  by their frequencies. Eg: bucket[20] should contain characters that appear 20 times.
 *  Due to natural ordering, we construct the result string by iterating the bucket backwards. At the end we'll get what we needed too.
 * 
 *  Time complexity is O(N), space O(N).
 */


class Solution {
public:
    // Sort pairs solution
    string frequencySort(string s) {
        string res = "";

        // Maps character -> frequency
        vector<pair<char, int>> freq(127);
        for (int i = 0; i < 127; ++i) freq[i] = { i, 0 };

        // Count frequencies
        for (char c : s) ++freq[c].second;

        // Sort by frequency
        sort(freq.begin(), freq.end(), [](auto& l, auto& r)-> bool {
            return l.second > r.second;
        });

        // Build sorted string based on sorted frequency
        for (auto& f : freq) {
            for (int i = 0; i < f.second; ++i)
                res += f.first;
        }

        return res;
    }


    string frequencySort2(string s) {
        string res = "";
        unordered_map<char, int> freq;
        vector<string> bucket(s.length() + 1, "");

        // Count frequencies
        for (char c : s) ++freq[c];

        // Put in bucket
        for (auto& f : freq) {
            bucket[f.second] += f.first;
        }

        // Build sorted string based on bucket
        for (int i = s.length(); i > 0; --i) {
            for (char c : bucket[i]) {
                for (int f = i; f > 0; --f)
                    res += c;
            }
        }

        return res;
    }
};