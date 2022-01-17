#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/word-pattern/
/*
 * 	HashTable problem. Notice that pattern = 'abba' and String = 'dog dog dog dog' would fail because a and b pattern would map to
 * 	the same word which is 'dog'
 *
 * 	The direct solution is to keep 2 hashmaps.
 * 	Here I use one hashset which keeps the seen before pattern of size 26, since pattern can only be in [a-z]
 *
 * 	Now, i will use a HashMap which maps from word to the pattern character.
 *
 * 	Now for every word that i encounter in the String:
 *
 * 		If the map already contains such word, check if the current pattern is equal to the past recorded one. If not, return false
 *
 * 		If the map don't recorded such word,
 * 		>	Check if the current pattern is used before. If it is, the pattern is paired with another different word already.
 * 			Return false
 * 		>	Else, we can safely assign the pattern to this word, and continue with the next word.
 */


class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> splitted = split(s, ' ');
        if (pattern.length() != splitted.size()) return false;

        unordered_map<char, string> map;
        unordered_set<string> used;

        for (int i = 0; i < pattern.length(); ++i) {
            char p = pattern[i];
            string str = splitted[i];

            if (map.count(p) && map[p] != str || !map.count(p) && used.count(str)) return false;
            map[p] = str;
            used.insert(str);
        }

        return true;
    }



    // Helper function to split string based on delimiter
    vector<string> split(string& s, char delim) {
        vector<string> res;
        if (!s.length() ) return res;
        
        string temp;

        for (char c : s) {
            if (c == delim) {
                res.push_back(temp);
                temp.clear();
            }
            else temp += c;
        }

        if (temp.length()) res.push_back(temp);
        return res;
    }
};