#include <map>
#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/advantage-shuffle/
/*
 * 	This is an array Greedy problem.
 *
 * 	For this problem, say we have a value from B, v2, we would pair with a number in A such that the value is still
 * 	larger than v2, but is least larger.
 * 	Also, if v2 cannot be paired anymore with any other number in A, we would pair it with the smallest number available
 *
 * 	Therefore, how can we perform such search easily? One way is to use TreeMap.
 * 	With Treemap, we give it values of B, and hopefully it returns the least larger value to one number in A. We store it
 * 	such that the value also counts frequencies in A. Once frequeny hit 0, delete that value as no more is available in A.
 *
 * 	------------------------------------------------------
 *
 * 	Best way is to do sorting. Sort A in ascending order and keep 2 pointers at both ends of it.
 * 	Then, sort B in descending order. The idea is:
 * 		>	Deal with largest element in B first. Because:
 * 			>	If it cannot be dealt with, pair with smallest number of A (left pointer of A)
 * 			>	If it can be dealt with, we can pair with largest in A as currently it is largest in B already. No worries
 */

class Solution {
public:

    //  TreeMap solution.
    //  I don't know how this is implemented in C++, but this results in Time Limit Exceeded apparently...
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        const int len = A.size();

        map<int, int> bst;
        vector<int> res(len);

        for (int i : A)
            ++bst[i];

        for (int i = 0; i < len; ++i) {
            auto toIns = upper_bound(bst.begin(), bst.end(), B[i] + 1, [](auto x, auto y) -> bool {
                return x <= y.first;
                });

            //  If no number is at least higher than current, take smallest number
            if (toIns == bst.end())
                toIns = upper_bound(bst.begin(), bst.end(), 0, [](auto x, auto y) -> bool {
                return x <= y.first;
                    });

            res[i] = toIns->first;
            --bst[toIns->first];
            if (!bst[toIns->first]) bst.erase(toIns->first);
        }

        return res;
    }



    //  Real Greedy Sorting solution
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        const int len = A.size();

        int l = 0, r = len - 1;
        sort(A.begin(), A.end());

        //  Create a new 2D array of pairs <val, idx>
        //  Then sort them based on value
        vector<pair<int, int>> B_idx;
        for (int i = 0; i < len; ++i)
            B_idx.emplace_back(make_pair<>(B[i], i));
            sort(B_idx.begin(), B_idx.end(), [](auto x, auto y)-> bool {
                return x.first > y.first;
             });


        vector<int> res(len);

        for (auto& i : B_idx) {
            if (A[r] > i.first) res[i.second] = A[r--];
            else res[i.second] = A[l++];
        }

        return res;
    }
};