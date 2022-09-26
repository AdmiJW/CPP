#include <string>
#include <vector>
using namespace std;


//https://leetcode.com/problems/satisfiability-of-equality-equations/
/*
 * 	This is actually a Union Find (Disjoint Set) problem.
 *
 *	The intuition to solve this problem is:
 *		> Establish all the equalities first. If I meet "a == b", assign a imiginary value to them, so that later I can
 *		  check for inequalities, like when i encounter "a != b"
 *		> Then, verify all inequalities.
 *
 *	Here I perform 2 linear scan, 1 that handles equalities only and another to verify inequalities. O(2N) time.
 *
 *	---------------------------------------
 *
 *	The hard part is to establish equality. Let's say we encounter "a == b". We could assign a temporary value to both a
 *	and b, let a = b = 1.
 *
 *	Now, imagine we encounter "c == d". We assign another temp value: c = d = 2.
 *
 *	If we now encounter "a == c", we now have to group all of the 4 values together, as "a == b == c == d"! This is where
 *	disjoint set have to be used.
 *
 *	In my implementation, since the variables can only be 'a' until 'z' (space 26), I used an integer array of size 26 that
 *	points character to their "parents". When I have to union the sets, simply run a linear scan through the array to map
 *	all old parents to the new one.
 *
 *
 *	So we can split into 4 (actually 3) cases in establishing equality:
 *
 *	> Both a and b already have parent  -- Union the parents
 *	> Only a have parent  -- Make b have a's parent
 *	> Only b have parent  -- Make a have b's parent
 *	> a and b don't have parent  -- Create a new parent to a and b
 */



class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
		int nextInt = 1;
		vector<int> parent(26, 0);

		// First iteration - Establish equalities.
		for (auto& eq : equations) {
			if (eq[1] == '!') continue;

			int a = eq[0] - 'a';
			int b = eq[3] - 'a';

			// Cases like "a == a" don't need to be handled
			if (a == b) continue;
			if (parent[a] != 0 && parent[b] != 0 && parent[a] != parent[b]) {
				int from = parent[a];
				int to = parent[b];
				convertAll(parent, from, to);
			}
			else if (parent[a] != 0) parent[b] = parent[a];
			else if (parent[b] != 0) parent[a] = parent[b];
			else parent[a] = parent[b] = nextInt++;
		}


		// Second iteration - Process inequalities.
		for (auto& eq : equations) {
			if (eq[1] == '=') continue;
			int a = eq[0] - 'a';
			int b = eq[3] - 'a';

			// Cases like "a != a" is directly false
			if (a == b) return false;
			if (parent[a] != 0 && parent[b] != 0 && parent[a] == parent[b]) return false;
		}

		return true;
    }




	void convertAll(vector<int>& arr, int fromValue, int toValue) {
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i] == fromValue) arr[i] = toValue;
		}
	}
};