#include <vector>
using namespace std;

// https://leetcode.com/problems/utf-8-validation/
/*
 * 	This is a bit manipulation problem.
 *
 * 	The basic logic is simple:
 *
 * 		1. Determine the length of one UTF-8 character. It can only be up until maximum 4 bytes
 * 				> 0xxx xxxx   	= length 1
 * 				> 110x xxxx		= length 2
 * 				> 1110 xxxx		= length 3
 * 				> 1111 0xxx		= length 4
 *
 * 		2. For the following length-1 bytes, check if the most significant 2 bits are '10'.
 *
 * 	All of these involves AND with bit masks. Please don't convert integers to binary string and check them.
 */






class Solution {
public:

    bool validUtf8(vector<int>& data) {
		
		const int masks[5] = {
			(1 << 7),		// 10000000
			(3 << 6),		// 11000000
			(7 << 5),		// 11100000
			(15 << 4),		// 11110000
			(31 << 3)		// 11111000
		};

		int i = 0;

		while (i < data.size()) {

			// Determine how much byte
			int len = -1;
			if ((data[i] & masks[0]) == 0) len = 1;
			else if ((data[i] & masks[2]) == masks[1]) len = 2;
			else if ((data[i] & masks[3]) == masks[2]) len = 3;
			else if ((data[i] & masks[4]) == masks[3]) len = 4;

			if (len == -1) return false;
			if (i + len > data.size()) return false;

			// Check if the following len-1 bytes prefix by '10'
			for (int j = i + 1; j < i + len; ++j)
				if ((data[j] & masks[1]) != masks[0]) return false;

			i += len;
		}
		return true;
    }
};

