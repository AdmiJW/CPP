//https://leetcode.com/problems/search-a-2d-matrix/

#include <vector>
#include <iostream>
#include <string>

/*
	Given a sorted 2D matrix
	>	Each row is sorted from left to right
	>	Each column first element is greater than the LAST element from LAST row

*/

bool searchMatrix(std::vector< std::vector <int> >& matrix, int target) {

	int rows = matrix.size();
	if (!rows) return false;		//	Number of Rows is 0
	int cols = matrix[0].size();
	if (!cols) return false;		//	Number of columns is 0

	int left, right, mid;

	//	Row Binary Search
	left = 0;
	right = rows - 1;

	while (left < right) {
		mid = ( left + (right - left) / 2 ) + 1;	//	The calculation of mid index shall be right biased (Instead of left biased)
		if (matrix[mid][0] > target) {
			right = mid - 1;
		}
		else {
			left = mid;
		}
	}

	int rowSearch = left;		//	Obtain the row to search

	left = 0;
	right = cols - 1;

	//	Column Binary Search
	while (left < right) {
		mid = ( left + ( right - left ) / 2) + 1;
		if (matrix[rowSearch][mid] > target) {
			right = mid - 1;
		}
		else {
			left = mid;
		}
	}

	return matrix[rowSearch][left] == target;
}