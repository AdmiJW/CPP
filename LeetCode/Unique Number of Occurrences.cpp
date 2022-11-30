#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;


// https://leetcode.com/problems/unique-number-of-occurrences/
/*
 * Given an array of integers arr, write a function that returns true if and only 
 * if the number of occurrences of each value in the array is unique.
 * 
 * Get the frequency of each number, then check if the frequency is unique using a HashSet.
 * 
 * Optionally, the problem can be solved using counting sort, but it is more complex for small input size like this problem
 */


class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> freq;
        unordered_set<int> occ;

        for (int i : arr) freq[i]++;

        for (auto& p : freq) {
            if (occ.count(p.second)) return false;
            occ.insert(p.second);
        }

        return true;
    }
};