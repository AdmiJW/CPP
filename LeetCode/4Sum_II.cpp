#include <unordered_map>
#include <vector>
using namespace std;

//https://leetcode.com/problems/4sum-ii/
/*
 * 	This is a Hash Map Problem, with a little mix of Divide n Conquer Idea (But not really).
 *
 * 	Naively, we could brute force it. For each a in A for each b in B for each c in C
 * 	and for each d in D, we keep attempting to find the 4 elements which sum up to 0.
 *
 * 	The time complexity then will be O(N^4). This is not good even for test case where
 * 	each array consists of 500 elements which ends up in billions of computations
 *
 * 	Maybe we could introduce some kind of Set? It can immediately perform lookup in O(1) time
 * 	and by putting one array into Set, the time complexity is immediately reduced to O(N^3)
 *
 * 	What if we make more than one array into Sets? How can that help us as to determine if one number
 * 	sum another needs to be 0, it must need 3 numbers fixed?
 *
 * 	This is where the divide n conquer part comes in. Essentially, we are checking if
 * 			a + b + c + d = 0
 * 	and if we split it into 2, then it becomes (a + b) + (c + d) = 0
 *
 * 	Therefore, we can record the sums of a and b, then sums of c and d. Then, iterate over all sums of
 * 	a with b, check if the negative sum (complement, -(a+b) ) is exist in c + d
 * 	This way the time complexity is reduced to O(N^2), albeit the space is increased to O(N^2) for recording the
 * 	sums.
 *
 * 	However, multiple element in 2 sets can result in the same sum. In that case, then we actually need to count
 * 	the frequency as well. This is where hashmap comes in. Instead of adding 1 each time a sum is found, we add
 * 	the total frequency of the same sum found each time to the result.
 *
 * 	-----------------------------------------------------------
 *
 * 	One optimization is that we dont need to keep 2 HashMaps, as it is O( 2N^2) actually that way. Keep the sum in one
 * 	hashmap, and another we'll just use normal nested loop.
 *
 */

class Solution {
public:
	int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
		unordered_map<int, int> sum;
		
		for (int i : A) {
			for (int j : B) {
				auto find = sum.find(i + j);

				if (find == sum.end())
					sum[i + j] = 1;
				else
					find->second++;
			}
		}

		int res = 0;

		for (int i : C) {
			for (int j : D) {
				if (sum.count(-(i + j)))
					res += sum.at(-(i + j));
			}
		}
		return res;
	}
};