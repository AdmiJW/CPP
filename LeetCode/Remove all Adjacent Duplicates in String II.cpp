#include <list>
#include <string>
using namespace std;

//https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
/*
 * 	This is a Stack String problem.
 *
 * 	Well, if previous k characters are the very same character, then obviously we will
 * 	remove that entire group from the string. Problem is, after removing, we must also
 * 	know what is the character before the removed group. Eg:
 *
 * 		"aabbba", k = 3
 * 	After removing 3 'b', we must also know 3 'a' can be removed next.
 *
 * 	This calls for the stack data structure. Imagine the string as a stack. If the stack top
 * 	is k consecutive characters of same type, we can pop them. What remains on top of stack will
 * 	be the characters before the removed group!
 *
 * 	Since K can be large, it's better to keep a counter instead. For every character,
 * 		>	If stack peek is same character as current one, increment counter for that stack top
 * 		>	Otherwise, push a new character to top of stack, with counter initialized as 1
 * 	Also in each iteration, be sure to check the stack top whether it can be popped, once detect that
 * 	the counter is >= k.
 */

class Solution {
public:
	string removeDuplicates(string s, int k) {
		list<pair<char, int>> stack;
		stack.push_back(make_pair<>('0', 0));

		for (char c : s) {
			if (c == stack.back().first) {
				++stack.back().second;
			}
			else {
				stack.push_back(make_pair<>(c, 1));
			}

			//	Accumulated k characters alreday. Remove that duplicates
			if (stack.back().second == k)
				stack.pop_back();
		}

		stack.pop_front();		//	Remove dummy node

		string res = "";
		while (!stack.empty()) {
			auto& pop = stack.front();
			while (pop.second--) res += pop.first;
			stack.pop_front();
		}
		return res;
	}
};