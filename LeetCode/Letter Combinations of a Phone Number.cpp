#include <vector>
#include <list>
#include <string>
using namespace std;

//https://leetcode.com/problems/letter-combinations-of-a-phone-number/
/*
 * 	This is a Backtracking, DFS or BFS problem that involves generating permutation
 *
 * 	First of all, we should have something to refer to when converting a digit to its alphabets. A
 * 	Array will do since the keys are small [2,9]
 *
 * 	For Backtracking (DFS), we select one possible alphabet each time based on the digit, then go deep
 * 	one layer. We know a permutation is generated once the length of the generated string is equal to the
 * 	length of the original digits string. Therefore store it in the result array.
 *
 * 	For BFS, we need Queue to store previous states, starting with an empty string in the list.
 * 	Every layer, we would pop everything from queue, representing incomplete alphabet strings, like "ab()()"
 * 	without the () part
 * 	Therefore knowing which index we are doing, simply append the possible characters and enqueue back into the queue
 * 	At the end, the queue will have complete strings and ready to be returned
 */

class Solution {
public:
	static const string alphas[10];

	//	Backtracking with Recursion solution
	vector<string> letterCombinations(string digits) {
		vector<string> res;
		string s = "";
		if (!digits.size()) return res;
		backtrack(digits, 0, s, res);
		return res;
	}
	void backtrack(const string& digits, int index, string& sb, vector<string>& res) {
		if (index >= digits.size()) {
			res.emplace_back(sb);
			return;
		}

		int digit = digits[index] - '0';
		for (char c : alphas[digit]) {
			sb += c;
			backtrack(digits, index + 1, sb, res);
			sb.erase(index);
		}
	}



	//	Iteration solution, BFS via Queue
	vector<string> letterCombinations2(string digits) {
		if (!digits.size()) return vector<string>();

		list<string> res;
		res.emplace_back("");

		for (char c : digits) {
			int d = c - '0';
			int size = res.size();

			while (size--) {
				string& prev = res.front();
				for (char a : alphas[d]) res.emplace_back(prev + a);
				res.pop_front();
			}
		}
		return vector<string>(res.begin(), res.end());
	}
};

const string Solution::alphas[10] = {
	"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"
};