#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/intersection-of-two-arrays-ii/
/*
 * This is a Hashmap / Sorting with two pointers problem.
 *
 * Of course, the small input size of this problem allows for brute force approach, but still requires a way
 * to record used element. (Like making it -INF)
 *
 * -------------------
 *
 * Using Hashmap, we would create a frequency table representing available elements left for us to be used.
 * Iterate through the other array who isn't used to build the table, if an element is in the table and frequency
 * isn't 0, we can append to res array, but remember to decrement the frequency in the table
 *
 * --------------------
 *
 * If both arrays are sorted, then we would use two pointers, one pointer for each array, initialized at leftmost
 * position
 *
 * > If arr1[left] == arr2[right], then we have intersection. Append to res, move both pointers.
 * > Else if arr1[left] > arr2[right], then proceed right pointer.
 * > Otherwise proceed left pointer.
 *
 * Iterate until one pointer hit the end of array.
 */

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        unordered_map<int, int> freq;
        vector<int>& longer = nums1.size() > nums2.size() ? nums1 : nums2;
        vector<int>& shorter = longer == nums1 ? nums2 : nums1;

        // Save the shorter array in hashmap to save space.
        for (int i : shorter)
            ++freq[i];
        // For each of the elements in i, check if any is left from hashmap
        for (int i: longer)
            if (freq.count(i) && freq[i]) {
                --freq[i];
                res.push_back(i);
            }

        return res;
    }


	// Sorting solution
	vector<int> intersect2(vector<int>& nums1, vector<int>& nums2) {
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		int l = 0, r = 0;
		vector<int> res;

		while (l < nums1.size() && r < nums2.size()) {
			if (nums1[l] == nums2[r]) {
				res.push_back(nums1[l]);
				++l; ++r;
			}
			else if (nums1[l] > nums2[r]) ++r;
			else ++l;
		}
		return res;
	}
};