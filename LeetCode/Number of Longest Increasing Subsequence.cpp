#include <vector>
#include <cmath>


class Solution {
public:

    int findNumberOfLIS(std::vector<int>& nums) {
        const int len = nums.size();

        int globalLen = INT_MIN;        //  The global longest substring length.
        int globalCnt = 0;                 //  The global count for longest substring

        int* dplen = new int[len];      //  Stores the maximum length substring can be formed by this as last element
        int* dpcnt = new int[len];      //  Stores the number of maximum length substring can be formed by this last element

        for (int i = 0; i < len; i++) {
            int n = nums[i];

            int localLen = 1;       //  Will be storing the maximum length substring met so far with this element.
            int localCnt = 1;       //  Will be storing the number of maximum length substring met so far with this element

            for (int j = i - 1; j >= 0; j--) {
                if (nums[j] >= n) continue;

                int lenFormed = dplen[j] + 1;       //  We combine this element with the said previous element, this is length of
                                                    //  of subsequence formed
                if ( lenFormed == localLen) localCnt += dpcnt[j]; //  Formed the maximum subsequence
                else if ( lenFormed > localLen) {
                    localLen = lenFormed;
                    localCnt = dpcnt[j];            //  The count becomes the count of maximum length subsequence of that prev element
                }
            }

            dplen[i] = localLen;
            dpcnt[i] = localCnt;

            if (globalLen == localLen) globalCnt += localCnt;
            else if (localLen > globalLen) {
                globalLen = localLen;
                globalCnt = localCnt;
            }
        }
        return globalCnt;
    }

};