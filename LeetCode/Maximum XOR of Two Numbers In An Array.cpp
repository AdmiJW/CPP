#include <vector>
#include <unordered_set>
using namespace std;


//https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
/*
 * 	This is mainly a Trie and bit manipulation problem.
 *	How do we achieve a big XOR? A Big value in a binary number is must have the '1' in the leftmost position, as left as possible.
 *	Also, a '1' in the left is more important than how many 1 is in the subsequent places.
 *	Eg: 10000 is still larger than 01111
 *	Therefore there might be a GREEDY element in here
 *
 *	We basically have to find 2 numbers in which they have the XOR element to be the largest. Instead of iterating through the array
 *	each time when a new number is introduced O(N^2) brute force approach, we can somehow store the information about which numbers
 *	have the bit of 0 or 1.
 *	How do we know if there is a FULL number which at a specific position is a 0 or 1? We can think of the binary integer as 'string'
 *	and therefore use the TRIE data structure.
 *
 *	Every time a number is introduced, we would always be greedy and try to find for the another digit in the Trie which has each bit
 *	to be different (XOR switches on different digits). Since in the trie all valid integers must be extend until 32 level (int),
 *	We don't have to worry about hitting a dead end, nor checking a boolean of isWord. There must be a valid integer as long as there
 *	is a valid Trie node.
 *
 *	=================================================================================================
 *
 *	An ingenious solution (Although same time complexity) is:
 *		>	First, we would run a loop that iterates 32 times. Each time, only the front n bits of each binary integers are considered.
 *			Eg in iteration 3, we would create a mask of 1110000...000 (31 bits long), and in iteration 5, it would be
 *			1111100...000 (31 bits long). Then we would use this mask and apply AND to all the numbers in the array. Those
 *			will be added into a Set
 *
 *		>	Now, since we run the loop like this, let's say the maximum so far is 1010100...000. Now we would like to extend it
 *			to 1010110...000. (An extra 1 in the next bit).
 *			We have to check if there is a combination in the Set, that XOR with each other, to give this desired maximum
 *			1010110...000.
 *
 *			This is a boolean algebra trick:
 *				A XOR B = C
 *				A XOR C = B
 *				B XOR C = A
 *			In XOR, anything we can flip around with no problem.
 *
 *			Therefore C is our desired maximum. We need to find if there is A and B in the set that XOR to become C.
 *			So iterate through elements in the set, and use above property: A XOR B = C, then A XOR C = B.
 *			We check if there is B in the set. If there is, just set the result to be maximum and continue to next loop (Next bit)
 *
 */



class Solution {
public:
	struct TrieNode {
		TrieNode* zero;
		TrieNode* one;
	};



	// Trie solution
	int findMaximumXOR(vector<int>& arr) {
		const int len = arr.size();
		if (len == 0) return 0;

		TrieNode* head = new TrieNode();
		int res = 0;

		constructTrie(arr[0], head);

		for (int i = 1; i < len; i++) {
			res = max(findMaxXOR(arr[i], head), res);
			constructTrie(arr[i], head);
		}
		return res;

	}


	// Finds the maximum number from the trie that could XOR n to yield maximum
	int findMaxXOR(int n, TrieNode* node) {
		int res = 0;

		for (int i = 1 << 30; i > 0; i >>= 1) {
			//	The current bit of n is 1.
			if ((n & i) != 0) {
				//	No choice because no digit at current place is 0. Select 1 
				if (!node->zero) node = node->one;
				//	Select 0 so XOR switches to 1.
				else {
					node = node->zero;
					res += i;
				}
			}
			//	Otherwise the current bit of n is 0
			else {
				//	No choice because no previous digit at current place is 1. Select 0
				if (!node->one) node = node->zero;
				//	Select 1 so XOR switches to 1
				else {
					node = node->one;
					res += i;
				}
			}
		}
		return res;
	}


	// Inserts a value into the trie
	void constructTrie(int n, TrieNode* node) {
		for (int i = 1 << 30; i > 0; i >>= 1) {
			if ((n & i)) {
				if (!node->one) node->one = new TrieNode();
				node = node->one;
			}
			else {
				if (!node->zero) node->zero = new TrieNode();
				node = node->zero;
			}
		}
	}



	//=============================================================
	// Set solution
	//=============================================================
	int findMaximumXOR2(vector<int>& arr) {
		int max = 0;
		int mask = 0;

		for (int i = 31; i >= 0; i--) {
			mask = mask | (1 << i);

			unordered_set<int> set;

			for (int n : arr) {
				set.insert(mask & n);
			}

			int desire = max | (1 << i);

			for (int n : set) {
				if (set.count(n ^ desire)) {
					max = desire;
					break;
				}
			}
		}

		return max;
	}
};