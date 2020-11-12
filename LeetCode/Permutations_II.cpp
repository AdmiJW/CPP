
#include <vector>
#include <unordered_map>
#include <algorithm>

//https://leetcode.com/problems/permutations-ii/

/*
 * 	This is a Backtracking / Permutation Problem
 *
 * 	For backtracking, the idea is simply from the list of numbers, we can pick one element out, append it to current
 * 	tracking array, remove from the list of available elements, and proceed the same procedure again until the available
 * 	element is empty. Then, we know that a permutation is generated.
 *
 * 	However, this time, duplicates are allowed. In the backtracking solution, each recursion call basically means one
 * 	single place in the resulting array. Eg:
 * 		>	The first call will iterate over all possible values to be put in the FIRST PLACE.
 * 		>	The second layer call will iterate over all possible values to be put in the SECOND PLACE.
 * 	Therefore, we need a way to basically only iterate over the duplicated value ONLY ONCE in each of the calls, but
 * 	in the subsequent calls, it still knows that the duplicated value is also selectable.
 *
 * 	This is achieved using frequency table.
 * 	At each layer calls, simply iterate over the key values of the table. If counter is 0, we know this key is used up
 * 	by prior calls. If not, we could attempt to insert the element here. Decrement the available count by 1 in the table,
 * 	then recurse into another layer. When the recurse layer returns, undo the changes.
 *
 * 	==============================================================================================================
 *
 * 	Another solution would be using the next permutation algorithm. Next permutation 100% complies with the duplicate
 * 	value law in this problem. Just that before the iteration itself, we have to sort the nums array, then add the initial
 * 	state into the result array first before it generates the next lexicographical permutation.
 *
 * 	For more info, see Topics > Algorithms > Next_Lexicographical_Permutation
 */


class Solution {
public:
    std::vector< std::vector<int>> permuteUnique(std::vector<int>& nums) {
        std::unordered_map<int, int> freq;
        for (int i : nums) {
            auto p = freq.emplace(i, 0);
            p.first->second = p.first->second + 1;
        }

        std::vector< std::vector<int> > res;
        std::vector<int> curr;

        recurse(res, freq, curr, nums.size());

        return res;
    }


    std::vector< std::vector<int>> permuteUnique2(std::vector<int>& nums) {
        int len = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> res;
        res.emplace_back(std::vector<int>(nums));

        while (1) {
            int pivot = len - 2;
            while (pivot >= 0 && nums[pivot + 1] <= nums[pivot])
                pivot--;

            if (pivot < 0) break;

            int swapper = len - 1;
            while (nums[swapper] <= nums[pivot])
                swapper--;

            swapElem(nums, swapper, pivot);
            revSubArray(nums, pivot + 1, len - 1);
            res.emplace_back(std::vector<int>(nums));
        }
        return res;
    }
private:
    void recurse(std::vector< std::vector<int> >& res, std::unordered_map<int, int>& freq, std::vector<int>& curr, int sizeLeft) {
        if (sizeLeft <= 0) {
            res.emplace_back(std::vector<int>(curr));
            return;
        }

        for (auto x : freq) {
            if (x.second == 0) continue;

            freq.at(x.first) = x.second - 1;
            curr.push_back(x.first);
            recurse(res, freq, curr, sizeLeft - 1);
            curr.pop_back();
            freq.at(x.first) = x.second;
        }
    }

    void swapElem(std::vector<int>& arr, int i1, int i2) {
        int temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
    }
    void revSubArray(std::vector<int>& arr, int from, int to) {
        while (from < to) {
            swapElem(arr, from, to);
            from++; to--;
        }
    }
};