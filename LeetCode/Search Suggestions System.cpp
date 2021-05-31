#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//https://leetcode.com/problems/search-suggestions-system/
/*
 * 	This is a String sorting / Trie DFS problem
 *
 * 	The Brute force solution actually works here, since input size is small.
 * 	First, sort the products lexicographically, so we ensure that first 3 products that are retrieved,
 * 	are guaranteed lowest lexicographical among possible answers.
 *
 * 	Iterate through all possible query substrings from length 1 to N. Each iteration, scan through the sorted
 * 	products name and add the string into result only if it starts with the query substring, up until res is
 * 	size 3.
 *
 *  ==================================================================
 *
 *  Since products is already sorted and strings can easily be compared lexicographically, we can use binary search.
 *  Since our query strings majority cases are shorter than the product names
 *  	>	If product[i] is lexi smaller than query, left = mid + 1
 *  	>	Otherwise, right = mid
 *  Do comparison to ensure whether the binary search result is indeed prefixed with query string. If not, we can terminate
 *  early since latter queries will guaranteed yield no result too.
 *
 *  ===================================================================
 *
 *  A much more efficient solution is two pointers. Since query substring build up, we can use left and right pointer
 *  to keep narrowing down the range of possible product names that fit into the result.
 *  Once the two pointers pass by each other (left > right), it is no longer possible, and thus we can terminate early
 *  as well
 *
 *  ===================================================================
 *
 *  In real world situations, it is likely we have to deal with large input sizes. In that case, data structure like Trie,
 *  are fitting this job.
 *	Trie are able to let us easily search for prefix. Once the prefix is found, we can perform dfs on that node to search for
 *	the first 3 fitting product names.
 */

class Solution {
public:
	//	Helper function to check prefix
	bool startsWith(const string& s1, const string& s2) {
		if (s2.size() > s1.size()) return false;
		for (int i = 0; i < s2.size(); ++i)
			if (s1[i] != s2[i]) return false;
		return true;
	}


	//	Brute force solution
	//	Sort the products list so the first 3 matches are guaranteed to be lowest in lexicographical
	//	Futhermore, we can optimize the iteration via binary search
	vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
		const int len = products.size();
		sort(products.begin(), products.end());
		vector<vector<string>> res;

		for (int sub = 1; sub <= searchWord.size(); ++sub) {
			string query = searchWord.substr(0, sub);
			vector<string> localResult;

			for (int i = 0; i < len && localResult.size() < 3; ++i)
				if (startsWith(products[i], query)) 
					localResult.push_back(products[i]);
			res.push_back(localResult);
		}
		return res;
	}



	//	Binary Search Optimization
	vector<vector<string>> suggestedProducts2(vector<string>& products, string searchWord) {
		const int len = products.size();
		sort(products.begin(), products.end());
		vector<vector<string>> res;

		for (int sub = 1; sub <= searchWord.size(); ++sub) {
			string query = searchWord.substr(0, sub);
			int start = binarySearch(products, query);
			//	Early termination. If this query does not yield result, surely further, longer queries will not yield result
			if (start == -1) break;

			vector<string> localres;
			for (int offset = 0; offset < 3; ++offset)
				if (start + offset < len && startsWith(products[start+offset], query))
					localres.push_back(products[start+offset]);
			res.push_back(localres);
		}

		//	Due to early termination, we need to fill in the latter, more lengthy queries with blank arrays
		while (res.size() < searchWord.length())
			res.emplace_back(vector<string>());
		return res;
	}
	//	Helper method for binary search. Returns -1 if no search result.
	int binarySearch(vector<string>& products, string& query) {
		int l = 0, r = products.size() - 1;
		while (l < r) {
			int mid = l + (r - l) / 2;
			if (products[mid] < query)
				l = mid + 1;
			else
				r = mid;
		}
		if (!startsWith(products[l], query)) return -1;
		return l;
	}



	//	Two pointers narrowing solution
	vector<vector<string>> suggestedProducts3(vector<string>& products, string searchWord) {
		const int len = products.size();
		sort(products.begin(), products.end());
		vector<vector<string>> res;
		int l = 0, r = len - 1;

		for (int sub = 1; sub <= searchWord.size(); ++sub) {
			string query = searchWord.substr(0, sub);
			
			//	Narrow from left
			while (l <= r && !startsWith(products[l], query)) ++l;
			//	Narrow from right
			while (l <= r && !startsWith(products[r], query)) --r;

			if (l > r) break;	//	Early termination.

			vector<string> localres;
			for (int offset = 0; offset < 3 && l + offset <= r; ++offset)
					localres.push_back(products[l + offset]);
			res.push_back(localres);
		}

		//	Due to early termination, we need to fill in the latter, more lengthy queries with blank arrays
		while (res.size() < searchWord.length())
			res.emplace_back(vector<string>());
		return res;
	}

};