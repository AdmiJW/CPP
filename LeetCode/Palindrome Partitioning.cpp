#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/palindrome-partitioning/
/*
 *	This is mainly a backtracking (which uses Depth First Search), optionally Dynamic programming question
 *
 *	Say we have the string AAB
 *
 *	At every subarray that involves first character until the last (A, AA, AAB), if we checked that the subarray
 *	indeed forms a palindrome (A, AA), then surely, the question left is,
 *
 *			what is the palindrome partitions to the right of this subarray?
 *
 *	This is because if the right DOES have its own palindrome partitions, surely we can just append the current
 *	palindrome to the result palindrom of right side, and have a full palindrome partitions already!
 *
 *	DP uses bottom up approach, so we can start from the back and work our way to the front, to obtain the final
 *	answer - Palindrome partitions starting with first character.
 *
 *	We use a 2D dynamic array to record the solutions to previous palindrome partitions. The first indexing is
 *	the starting index, then follows a series of String arrays which contains individual partitions.
 *
 *	Eg: At index [3], it contains one or many String arrays, each representing the possible partitions formed
 *	from the character at index 3 onwards.
 *
 * 	Iterating from backward to choose the starting character, we are going to try all possible length of substring
 * 	within the range starting character to end. If one of such is found to be palindrome, we know immediately that
 * 	a palindrome partition can be formed, so for each palindrome partition formed at starting character to the right
 * 	of current ending range, form a partition using current palindrome and that existing palindrome.
 *
 * 	-------------------------------------------------------------------------------------
 *
 * 	This is actually still a backtracking problem. From leftmost character, expand the substring one by one.
 * 	If found to be a palindrome, push substring into backtracking array, and recurse to find the partitions
 * 	to the right of the end of substring.
 *
 * 	When the recursion hits the end of full length string, we know one partition is fully formed for the string
 * 	thus we push the backtracking array contents into result array.
 *
 * 	--------------------------------------------------------------------------------------
 *
 * 	Instead of using two pointers for checking palindrome, we can use DP to check palindrome in O(1) time instead.
 *
 * 	A string is palindrome if
 * 		>	Length less than or equal 3, and first & last char is same
 * 		>	Else, first & last char same, and substring in between them is also palindrome
 *
 * 	Therefore the checking substring in between the first and last char part can be done in O(1) time using
 * 	DP table.
 */


class Solution {
public:
	vector<vector<string>> partition(string s) {
		const int len = s.length();

		vector<vector<vector<string>>> arr(len + 1, vector<vector<string>>() );
		arr[len].emplace_back(vector<string>() );

		for (int i = len - 1; i >= 0; --i) {
			string sb = "";

			for (int j = i; j < len; ++j) {
				sb += s[j];

				if (isPalindrome(sb)) {
					for (vector<string> prev : arr[j + 1]) {
						arr[i].emplace_back(vector<string>() );
						auto li = arr[i].end() - 1;
						li->push_back(sb);
						li->insert(li->end(), prev.begin(), prev.end());
					}
				}
			}
		}
		return arr[0];
	}





	vector<vector<string>> partition2(string s) {
		vector<vector<string>> res;
		vector<string> record;
		recurse(s, 0, record, res);
		return res;
	}
	void recurse(string& s, int start, vector<string>& record, vector<vector<string>>& res) {
		const int len = s.length();

		//	Base case: Already reached the end of string
		if (start >= len) res.emplace_back(vector<string>(record.begin(), record.end()) );

		string sb = "";
		for (int i = start; i < len; ++i) {
			sb += s[i];
			if (isPalindrome(sb)) {
				record.push_back(sb);
				recurse(s, i + 1, record, res);
				record.pop_back();
			}
		}
	}





	vector<vector<string>> partition3(string s) {
		vector<vector<string>> res;
		vector<string> record;
		vector<vector<bool>> isPalin(s.length(), vector<bool>(s.length(), false));
		recurse2(s, 0, record, res, isPalin);
		return res;
	}
	void recurse2(string& s, int start, vector<string>& record, vector<vector<string>>& res, vector<vector<bool>>& isPalin) {
		const int len = s.length();

		if (start >= len) res.push_back(vector<string>(record.begin(), record.end()));

		for (int i = start; i < len; ++i) {
			if (s[start] == s[i] && (i - start <= 2 || isPalin[start + 1][i - 1])) {
				isPalin[start][i] = true;
				record.push_back(s.substr(start, i - start + 1));
				recurse2(s, start + 1, record, res, isPalin);
				record.pop_back();
			}
		}
	}
private:
	bool isPalindrome(string& s) {
		const int len = s.length();
		for (int i = 0; i < len / 2; ++i)
			if (s[i] != s[len - i - 1]) return false;
		return true;
	}
};