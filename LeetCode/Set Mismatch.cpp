#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/set-mismatch/
/*
 * 	A HashTable / Sorting / In place marking problem
 *
 * 	The easiest way is to use a counting table. In this, we use an array of the same size as the input
 * 	array, due to the input can only be in range 1-n only, the indices of the array immediately becomes
 * 	the key for the frequency map.
 *
 * 	Iterate the input array and update the frequency table. At the end, iterate the frequency table again.
 * 	The number with frequency 2 is duplicated, and the number with frequency 0 is missing.
 *
 * 	-------------------------------------------------------------------------------
 *
 * 	When the input array are sorted, each input will essentially be counting up, like 1,2,3,4... except:
 * 		>	The duplicated number will clump together in pair. like 1,2,2,3...
 * 		>	One number will be skipped. Like: 1,2,4,5...
 *
 * 	So, when scanning the sorted array, if one element is same as previous one, it is duplicated element.
 * 	Also, if the element, compared to previous is not one ahead, but TWO, the supposed number is skipped.
 * 	Thus this number - 1 is the missing number.
 *
 * 	THere are edge case to be handled, when the missing number is:
 * 		>	At the end of array, like 1,2,2,3		<- Checked by looking at last element, is it same as nums.length?
 * 		>	At the start of array, like 2,2			<- We can initialize missing value to be 1
 *
 * 	-----------------------------------------------------------------------------------
 *
 * 	To avoid using extra space but still keep information about what elements is seen before, we can use
 * 	in place marking technique. Notice:
 *
 * 		>	Elements are only 1 to n inclusive. Means all positive
 *		>	Elements can always be mapped to a index in array
 *
 *	So, for elements seen before, simply negate it / make it negative. During the process if we see an element
 *	already is negative, it is duplicated element.
 *
 *	Run a second iteration to find out a element which isn't negative. That is missing element.
 */

class Solution {
public:

	//	Simple Frequency Table solution
	vector<int> findErrorNums(vector<int>& nums) {
		vector<int> freq(nums.size());
		for (int i : nums) ++freq[i - 1];

		vector<int> res(2);
		for (int i = 0; i < nums.size(); ++i) {
			if (freq[i] == 2) res[0] = i + 1;
			else if (!freq[i]) res[1] = i + 1;
		}
		return res;
	}



	//	Sorting and scan solution 
	vector<int> findErrorNums2(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<int> res(2);					//	{duplicate, missing}
		res[1] = 1;							//	Handle Edge case like [2,2]. In this case missing is 1, but never found

		for (int i = 1; i < nums.size(); ++i) {
			if (nums[i] == nums[i - 1])
				res[0] = nums[i];
			else if (nums[i] == nums[i - 1] + 2)
				res[1] = nums[i] - 1;
		}
		//	Handle edge case where missing is nums.length
		res[1] = nums[nums.size() - 1] != nums.size() ? nums.size() : res[1];
		return res;
	}



	//	In place marking solution
	vector<int> findErrorNums3(vector<int>& nums) {
		vector<int> res(2);

		for (int i : nums) {
			i = abs(i);					//	May be previously marked already, so make it positive
			if (nums[i - 1] < 0) res[0] = i;
			else nums[i - 1] *= -1;
		}
		for (int i = 0; i < nums.size(); ++i)
			if (nums[i] > 0) res[1] = i + 1;
		return res;
	}
};