#include <unordered_set>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/erect-the-fence/
/*
 * 	This is a Computational Geometry - Convex Hull problem.
 *
 * 	See Topics:
 * 		- Jarvis March COnvex Hull Gift Wrapping Algorithm
 * 		- Graham Scan Algorithm
 *
 * 	for detailed explaination
 */

class Solution {
public:

	// Computes the cross product of PQ x QR
	int crossProduct(const vector<int>& p, const vector<int>& q, const vector<int>& r) {
		return (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
	}

	// Checks if point I is on line PQ
	bool isBetween(vector<int>& p, vector<int>& i, vector<int>& q) {
		bool isInX = i[0] >= p[0] && i[0] <= q[0] || i[0] <= p[0] && i[0] >= q[0];
		bool isInY = i[1] >= p[1] && i[1] <= q[1] || i[1] <= p[1] && i[1] >= q[1];
		return isInX && isInY;
	}

	// Jarvis's ALgorithm
	vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
		const int len = trees.size();
		unordered_set<vector<int>*> res;

		// Locate the leftmost point first
		int leftmost_index = 0;
		for (int i = 0; i < len; ++i) {
			if (trees[i][0] < trees[leftmost_index][0])
				leftmost_index = i;
		}

		// Start running the algorithm.
		// current_index is the index of current pivot point
		int current_index = leftmost_index;
		do {
			// Randomly select a point as potential first
			int potential_index = (current_index + 1) % len;

			// Determine rightmost by cross product
			for (int i = 0; i < len; ++i)
				if (crossProduct(trees[current_index], trees[i], trees[potential_index]) < 0)
					potential_index = i;

			// Check for any collinear points
			for (int i = 0; i < len; ++i) {
				if (i != current_index && i != potential_index &&
					crossProduct(trees[current_index], trees[i], trees[potential_index]) == 0 &&
					isBetween(trees[current_index], trees[i], trees[potential_index]))
					res.insert(&trees[i]);
			}

			// Officially include the potential rightmost point into our list
			res.insert(&trees[potential_index]);
			// This rightmost point become our current pivot point
			current_index = potential_index;

		} while (current_index != leftmost_index);

		vector<vector<int>> ans;
		for (auto& r : res)
			ans.push_back(*r);
		return ans;
	}



	// Obtains the bottom left point among a set of points.
	// Returns the most bottom point. If there are several candidates, return the leftmost one
	vector<int> getBottomLeftPoint(vector<vector<int>>& points) {
		vector<int> res = points[0];

		for (vector<int>& p : points) {
			if (p[0] < res[0] || p[0] == res[0] && p[1] < res[1])
				res = p;
		}
		return res;
	}

	// Calculates the distance of two points
	int calcDistance(const vector<int>& p1, const vector<int>& p2) {
		return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
	}

	// Swaps two points in points array
	void swap(vector<vector<int>>& points, int l, int r) {
		vector<int> temp(points[l]);
		points[l] = vector<int>(points[r]);
		points[r] = temp;
	}

	// Sorts the array based on polar angle referenced from bottom leftmost point provided
	void sortByAngle(vector<vector<int>>& points, vector<int>& bottomleft_point) {


		// Sort by angle. If angle is same, sort by increasing distance (Closer to bottomleft, is in front)
		sort(points.begin(), points.end(), [this, bottomleft_point](auto& x, auto& y)-> bool {
			int angle = crossProduct(x, bottomleft_point, y);
			return angle == 0 ? calcDistance(x, bottomleft_point) < calcDistance(y, bottomleft_point) : angle < 0;
			});


		// However, for points that are collinear with bottomleft point, should be sorted such that
		// the furthest distance comes first
		// First, obtain the first collinear point in the sorted list.
		vector<int>& last = points[points.size() - 1];
		int pointer = points.size() - 2;

		while (pointer >= 0 && crossProduct(points[pointer], bottomleft_point, last) == 0)
			--pointer;

		// Reverse sort collinear points using two pointer
		for (int l = pointer + 1, r = points.size() - 1; l < r; ++l, --r)
			swap(points, l, r);
	}


	// Computes the Convex Hull using Graham Scan Algorithm
	vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
		const int len = trees.size();
		if (len <= 1) return trees;

		// Sort by the angle of bottom leftmost point
		vector<int> bottomLeft = getBottomLeftPoint(trees);
		sortByAngle(trees, bottomLeft);

		// Stack to store the hull points
		stack< vector<int> > stack;
		stack.push(trees[0]);
		stack.push(trees[1]);

		// Graham's scan
		for (int i = 2; i < len; ++i) {
			vector<int> top = stack.top();
			stack.pop();

			// While the previous point makes a 'right' turn to reach current point, pop it
			while (crossProduct(stack.top(), top, trees[i]) < 0) {
				top = stack.top();
				stack.pop();
			}

			stack.push(top);
			stack.push(trees[i]);
		}

		// Extract and return
		vector<vector<int>> res;
		while (!stack.empty()) {
			res.push_back(stack.top());
			stack.pop();
		}
		return res;
	}
};