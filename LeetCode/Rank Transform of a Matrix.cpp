#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/rank-transform-of-a-matrix/
/*
 * This is a Hard, Disjoint Set, Greedy problem.
 *
 * We have to assign each elements a rank, where ranks of higher values shall be higher than those of lower value ones.
 *
 * Approaching from greedy idea, we should always assign rank to those smaller values first, so we will not have conflicting rank
 * later on. Using idea from DP, we can record the maximum ranks that exist so far in particular column and row, so we can always
 * assign the valid, next rank.
 *
 * 		> Sort the positions (x,y) by their actual value in matrix, ascending
 * 		> Fill the ranks according to the sorted positions. Derive rank from minRank DP array of both row and column
 *
 * In fact, this will already be the solution if say, every element in the matrix is unique. However, that is not the case here
 * as duplicate values do exist.
 *
 * ---------------------------
 *
 * The greatest challenge faced in this problem is mainly from the fact that duplicate values exist. In that case, we need to
 * assign them same rank as long as those values do somehow 'connect' to each other in rows or columns.
 *
 * This require the usage of Disjoint sets. Say we have a value X, in which it occurs in matrix N times. If suddenly one element
 * from one group is in same row/column as the other element in other group, we need to union the group together. In other words,
 * THIS GROUP OF DUPLICATED VALUES SHALL HAVE SAME RANK.
 *
 * With this, the general algorithm goes:
 * 		>	Group (x,y) by actual value in the matrix
 * 		>	Traverse the positions (x,y) from small to large. (Assign rank to small values first)
 * 			-	Split them into groups and union related groups using Disjoint Set
 * 			-	Within each of these groups:
 * 				>	Find the rank that should be assigned to them. All of them has to have same rank. The rank is derived from
 * 					minRank from both row and column of each of these elements
 * 				>	Set the derived rank to each of these elements, as well as update minRank DP array
 */

// Abstract Union Find Data Structure, operates using index
class UnionFind {
public:
    vector<int> parent;

    UnionFind(int size) : parent(vector<int>(size)) {
        for (int i = 0; i < size; ++i) parent[i] = i;
    }

    int find(int index) {
        if (parent[index] == index) return index;
        parent[index] = find(parent[index]);
        return parent[index];
    }

    void join(int i, int j) {
        int p1 = find(i), p2 = find(j);
        parent[p1] = p2;
    }
};

// A Node for elements of same values, used for Disjoint Set purpose (Indirectly)
struct GroupNode {
    int x, y, index;
    GroupNode(pair<int, int> pos, int index)
        :x(pos.first), y(pos.second), index(index) {}
};


class Solution {
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        const int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> res(m, vector<int>(n, 0));
        vector<int> maxRankInRow(m, 0);
        vector<int> maxRankInCol(n, 0);

        // Value -> Positions. We want them sorted ascendingly
        map<int, vector<pair<int, int>>> mapOfSameValue;
        // Fill the map
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                mapOfSameValue[matrix[i][j]].push_back({ i, j });
            }
        }

        // Now for each of the same values, we have to perform union find
        for (auto& value : mapOfSameValue) {
            auto& positions = value.second;
            vector<GroupNode> nodes;
            // Map the positions into GroupNode, which preserves their index
            for (auto& p : positions)
                nodes.push_back({ p, static_cast<int>(nodes.size()) });

            UnionFind uf(nodes.size());

            // Sort by row number to find same rows
            sort(nodes.begin(), nodes.end(), [](GroupNode& l, GroupNode& r)-> bool {
                return l.x < r.x;
                });
            for (int i = 0; i < nodes.size() - 1; ++i)
                if (nodes[i].x == nodes[i + 1].x)
                    uf.join(nodes[i].index, nodes[i + 1].index);

            // Sort by col number to find same columns
            sort(nodes.begin(), nodes.end(), [](GroupNode& l, GroupNode& r)-> bool {
                return l.y < r.y;
                });
            for (int i = 0; i < nodes.size() - 1; ++i)
                if (nodes[i].y == nodes[i + 1].y)
                    uf.join(nodes[i].index, nodes[i + 1].index);

            // Now they are grouped, perform operation by group
            unordered_map<int, vector<GroupNode>> mapByGroup;
            for (GroupNode gn : nodes) {
                int parent = uf.find(gn.index);
                mapByGroup[parent].push_back(gn);
            }

            // For each of the groups, find their supposed ranks
            for (auto& li : mapByGroup) {
                int rank = 0;
                for (auto& e : li.second) {
                    rank = max(rank, maxRankInRow[e.x] + 1);
                    rank = max(rank, maxRankInCol[e.y] + 1);
                }

                for (auto& e : li.second)
                    res[e.x][e.y] = maxRankInRow[e.x] = maxRankInCol[e.y] = rank;
            }
        }
        return res;
    }
};