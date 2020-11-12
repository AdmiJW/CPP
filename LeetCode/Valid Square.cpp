#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>

//https://leetcode.com/problems/valid-square/

/*
 * 	This is a Mathematical Based Question
 *
 * 	A square, if we compare all point with all other 3 points, it will basically have 2 lengths only.
 * 		>	Side Length
 * 		>	Vertex Length
 *
 * 	Furthermore, the side lengths should be equal, and occur 4 times only (Accounting into repetition, thats 8)
 * 				 the vertex lengths should be equal, and occur 2 times only (Accounting into repetition, thats 4)
 *
 * 	So, for each point, as long as it is not itself, find distance, record the length occurrences in frequency table
 * 	If there is only unique lengths, and the length occurrence is one 8, and one 4 (IF repetition), thats A SQUARE
 *
 * 	================================================================================================================
 *
 * 	If we sort the 4 points, first by x value, then only by y value, we will get a nice pattern which
 * 		>	First and last element is a vertex
 * 		>	Second and third element is a vertex
 *
 * 	Then we easily check if the lengths of one point with other points are equal. This can simplify things
 */

class Solution {
public:
    bool validSquare(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& p3, std::vector<int>& p4) {
        std::unordered_map<double, int> freq;
        std::vector< std::vector<int> > pts;
        pts.push_back(p1);
        pts.push_back(p2);
        pts.push_back(p3);
        pts.push_back(p4);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) continue;
                double dist = findDist(pts[i], pts[j]);
                auto p = freq.emplace(dist, 0);
                p.first->second = p.first->second + 1;
            }
        }

        if (freq.size() != 2) return false;

        bool is8 = false, is4 = false;
        for (auto& x : freq) {
            if (x.second == 8) is8 = true;
            if (x.second == 4) is4 == true;
        }

        return is8 && is4;
    }


    bool validSquareSort(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& p3, std::vector<int>& p4) {
        std::vector< std::vector<int> > pts;
        pts.push_back(p1);
        pts.push_back(p2);
        pts.push_back(p3);
        pts.push_back(p4);

        std::sort(pts.begin(), pts.end(), [](auto x, auto y)-> bool {
            if (x[0] == y[0]) return x[1] < y[1];
            return x[0] < y[0];
        });

        double side = findDist(pts[0], pts[1]);
        double vertex = findDist(pts[1], pts[2]);
        if (findDist(pts[0], pts[3]) != vertex) return false;
        if (findDist(pts[0], pts[2]) != side) return false;
        if (findDist(pts[3], pts[1]) != side) return false;
        if (findDist(pts[3], pts[2]) != side) return false;
        return side != vertex;
    }

private:
    double findDist(std::vector<int>& p1, std::vector<int>& p2) {
        int dx = p1[0] - p2[0];
        int dy = p1[1] - p2[1];

        return std::sqrt(dx * dx + dy * dy);
    }
};