#include <string>
using namespace std;

//https://leetcode.com/problems/next-greater-element-iii/
/*
 * 	This is a String problem which Next Lexicographical Permutation Algorithm is used
 *
 * 	For more information about this algorithm, check out Topics/Algorithms/Next_Lexicographical_Permutation
 *
 *
 * 	It is an algorithm which when passed in a String or anything iterable and ordering is important, the algorithm
 * 	will go and generate the permutation which is the LEAST greater lexicographical compared to the original value
 *
 * 	Eg: 124 -> 142.
 *
 * 	The algorthm generally takes several passes:
 * 		>	First pass find out the decreasing pattern from behind
 * 		>	Second pass find out the element to be swapped with the smaller element
 * 		>	Third pass invert everything behind the swapped value
 *
 * 	Therefore it takes O(3N) time which is O(N). Space however is O(1). In this case, N is the length of the number
 *
 *  --------------------------------------------------------------------------------------------------
 *	Note that in C++ <algorithm> header, there is already a next_permutation() function implemented
 */

class Solution {
public:
	int nextGreaterElement(int n) {
		string sb = to_string(n);
		const int len = sb.length();

		for (int i = len - 2; i >= 0; --i) {
			if (sb[i] < sb[i + 1]) {
				//	Find out the least larger element to be swappd
				for (int j = len - 1; j > i; --j) {
					if (sb[j] > sb[i]) {
						swap(sb, i, j);
						break;
					}
				}


				//	All the parts beyond it has to be inverted
				for (int j = i + 1; j <= (len + i) / 2; ++j)
					swap(sb, j, len - j + i);

				try {
					return stoi(sb);
				}
				catch (...) {
					return -1;
				}
			}
		}
		return -1;
	}
private:
	void swap(string& sb, int x, int y) {
		char temp = sb[x];
		sb[x] = sb[y];
		sb[y] = temp;
	}
};