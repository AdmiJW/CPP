#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// https://leetcode.com/problems/find-players-with-zero-or-one-losses/
/*
 *  This is a HashMap, Optionally Counting sort problem
 * 
 *  For the matches, we simply has to record how many losses each player has.
 *  Then, we return the list of players that has losses = 0 or 1
 * 
 *  To return the list in ascending order, we can sort the list after filtering the players
 *  Or we could use counting sort, which does not have to sort, but may have space redundancy,
 *  done by initializing an array of size O(N), which N is the possible maximum player ID
 */



class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int, int> map;
        vector<int> noLosses, oneLosses;
        
        // Record the team's losses
        for (auto& match: matches) {
            if ( !map.count(match[0]) ) map[match[0]] = 0;
            ++map[match[1]];
        }


        for (const auto& [key, value] : map) {
            if ( value == 0 ) noLosses.push_back(key);
            else if ( value == 1) oneLosses.push_back(key);
        }

        // Sort
        sort(noLosses.begin(), noLosses.end());
        sort(oneLosses.begin(), oneLosses.end());

        return {noLosses, oneLosses};
    }
};