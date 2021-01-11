#include <vector>
using namespace std;

/*
 * 	To merge a linked list is easy. To do so on array, it depends.
 *
 * 	The most naive method is to create a new array of the combined size of A and B. Then, keep 2 pointers to record
 * 	our progress in the arrays. Each iteration compare the elements in both array pointed by the pointers and insert the
 * 	one lesser.
 *
 * 	The time complexity is O(N) but it takes up O(N) extra space. However, this method is required if we are unable to
 * 	do it in place (No spaces allocated for array B elements).
 *
 * 	---------------------------------------------------------------------------
 *
 * 	To do it in place, one solution is to use array insertion method. AKA if we want to insert elements into middle
 * 	of array A, we have to shift every elements to right by one space, then only element is inserted at the position.
 *
 * 	This method does the merging in place, but at worst case will take up O(N^2) time complexity.
 *
 * 	-----------------------------------------------------------------------------
 *
 * 	Now, think outside the box. What's the edge cases:
 * 		-	All elements in B is larger than all elenents in A.
 * 		-	All elements in A is larger than all elements in B.
 *
 * 	Since we are trying to insert into array A, what happens if I merge from behind? AKA inserting elements at behind
 * 	which contains empty spaces?
 * 	At case 1, the array B would be exhausted by the time it hits the tail of array A!
 * 	At case 2, when the pointer meets the original array A's tail, all elements in A would be moved to end of array already!
 *
 * 	No data is loss at either cases! Therefore we conclude that we can indeed merge from behind.
 * 	O(N) time taken, O(1) space taken
 */

class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int pt = 0;
		vector<int> arr(m + n);

		int pt1 = 0;
		int pt2 = 0;

		while (pt1 < m || pt2 < n) {
			if (pt2 >= n || pt1 < m && nums1[pt1] < nums2[pt2])
				arr[pt++] = nums1[pt1++];
			else
				arr[pt++] = nums2[pt2++];
		}

		for (int i = 0; i < m; ++i) nums1[i] = arr[i];
	}


	void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int pt = 0, pt1 = 0, pt2 = 0;

		while (pt < m + n) {
			//	We are required to insert element2 at pt1
			if (pt1 >= m || pt2 < n && nums1[pt] > nums2[pt2]) {
				//	We are required to shift because elements after it still exists.
				if (pt1 < m)
					shiftRightUntil(nums1, pt);
				nums1[pt++] = nums2[pt2++];
			}
			else {
				++pt1; ++pt;
			}
		}
	}
	void shiftRightUntil(vector<int>& arr, int pos) {
		for (int i = arr.size() - 2; i >= pos; --i)
			arr[i + 1] = arr[i];
	}



	void merge3(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int pt = m + n - 1;
		int pt1 = m - 1;
		int pt2 = n - 1;

		while (pt2 >= 0) {
			//	Pointer 1 finished, or elemenet 2 is greater. Then insert element2
			if (pt1 < 0 || nums2[pt2] > nums1[pt1])
				nums1[pt--] = nums2[pt2--];
			//	Otherwise element 1 is equal or greater. Insert element1 instead
			else
				nums1[pt--] = nums1[pt1--];

		}
	}
};