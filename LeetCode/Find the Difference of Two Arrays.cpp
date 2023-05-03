
#include <vector>
#include <unordered_map>
using namespace std;


// https://leetcode.com/problems/find-the-difference-of-two-arrays
/*
 * This is a HashMap problem.
 *
 * We need a way to knowing the occurrence of an element in both arrays in O(1) time. HashMap is the best choice.
 *
 * First, we store all elements in nums1 into the map, with value 1.
 * Then, iterate through elements in nums2, if the element is not in map, store it with value 2.
 * Else, store it with value 3, meaning it has occurred in both arrays.
 *
 * Finally, iterate through the map, and add all elements with value 1 into res1, and all elements with value 2 into res2.
 * The total iteration is (M + N + (M + N - distinct(M,N))) = O(M + N)
 * Space is O(M + N)
 */



class Find_the_Difference_of_Two_Arrays {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> map;
        vector<vector<int>> res;
        vector<int> res1, res2;

        for (int i: nums1) map[i] = 1;
        for (int i: nums2) {
            if (!map.count(i)) map[i] = 2;
            if (map[i] == 1) map[i] = 3;
        }

        for (auto& [k, v]: map) {
            if (v == 1) res1.push_back(k);
            else if (v == 2) res2.push_back(k);
        }

        res.push_back(res1);
        res.push_back(res2);
        return res;
    }


    // Use array as bucket
    vector<vector<int>> findDifference2(vector<int>& nums1, vector<int>& nums2) {
        vector<int> bucket(2001, 0);
        vector<vector<int>> res;
        vector<int> res1, res2;

        for (int i: nums1) bucket[i + 1000] = 1;
        for (int i: nums2) {
            if (bucket[i + 1000] == 1) bucket[i + 1000] = 3;
            if (bucket[i + 1000] == 0) bucket[i + 1000] = 2;
        }

        for (int i = 0; i < bucket.size(); i++) {
            if (bucket[i] == 1) res1.push_back(i - 1000);
            else if (bucket[i] == 2) res2.push_back(i - 1000);
        }

        res.push_back(res1);
        res.push_back(res2);
        return res;
    }
};