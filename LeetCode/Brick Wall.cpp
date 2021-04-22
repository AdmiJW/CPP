#include <vector>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/brick-wall/
/*
 * This is a HashMap problem.
 *
 * 	Intuitively, we want to draw a verticle line among the bricks. Therefore since the problem
 * 	stated that crossing the middle of two adjacent bricks doesn't count as crossing a brick,
 * 	we would greedily want to cross as many 'middle spaces between two bricks' as possible
 *
 * 		0 1  2  3  4
 *  Eg: [ ][ ][   ]
 *  	[    ][   ]
 *  	[ ][ ][   ]
 *
 *  We see if we cross column 2, that column has most 'middle spaces between two bricks', so we
 *  choose to cross that column!
 *
 *  Unfortunately, we cannot simply use array to record middle space counts, because the brick may
 *  span up to INT_MAX, which is too much to handle. Fortunately, we can use HashMap.
 *
 * 	For each row, keep a running sum of the widths. The running sum will indicate the end of a single
 * 	brick in that row, therefore is a 'space between bricks'. Record it as increment in the Hashmap
 * 	in x position.
 *
 * 	At the end, find out the column with max no of middle spaces, and return (No of rows - spaces)
 */

class Solution {
public:
	int leastBricks(vector<vector<int>>& wall) {
		const int height = wall.size();
		unordered_map<int, int> count;

		for (auto& row : wall) {
			int sum = 0;
			for (int b : row) {
				++count[sum];
				sum += b;
			}
		}

		count.erase(0);
		int res = 0;
		for (auto i = count.cbegin(); i != count.cend(); ++i)
			res = max(res, i->second);

		return height - res;
	}
};