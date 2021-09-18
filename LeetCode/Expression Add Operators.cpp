#include <string>
#include <vector>
using namespace std;

//https://leetcode.com/problems/expression-add-operators/
/*
 * This is a String backtracking problem.
 * (Marked - I see solution)
 *
 * The core idea is, for every digit, we can choose from 4 operations:
 * 	>	Appending a + before current digit
 * 	>	Appending a - before current digit
 * 	>	Appending a * before current digit
 * 	>	Append current digit to the previous operand to create larger number.
 *
 * Therefore the recursive backtracking algorithm looks like:
 *
 * 	if (reached end)
 * 		append path if evaluated == target
 *
 * 	else
 * 		backtrack append +
 * 		backtrack append -
 * 		backtrack append *
 * 		backtrack append operand
 *
 *
 * But then, we also need to take care of some edge cases:
 *
 * 		>	An operand cannot have padded zeroes.
 * 		>	An operand + - * cannot go before first digit.
 * 		> 	Multiplication must be higher precedence.
 *
 * To deal with multiplication, we would keep a reference to the previous operand. Say we have 2 - 5 * 3 and
 * we are dealing with *3, so far the variables eval = -3 and prev = -5
 *
 * Then we simply do eval - prev + (prev * 3)
 * 										   ^
 * 									 Current operand
 */

typedef long long int LONG;

class Solution {
public:
    vector<string> addOperators(string num, int target) {
		vector<string> res;
		vector<string> objects;
		recurse(0, objects, 0, 0, 0, num, target, res);
		return res;
    }


    void recurse(int index, vector<string>& objects, LONG current, LONG prev, LONG eval,
        string num, int target, vector<string>& res) {
		const int len = num.length();

		// Reached the end of string. Check if formed the target or not
		if (index == len) {
			if (eval == target && current == 0) {
				string exp = "";
				for (int i = 1; i < objects.size(); ++i) exp += objects[i];
				res.push_back(exp);
			}
			return;
		}

		// Operation 1 - Extend current operand by this digit (Effects the rest of the operation too)
		current = current * 10 + (num[index] - '0');
		string currentInStr = to_string(current);

		// However, ensure that we are not doing operand with padded zeroes like 0005
		if (current > 0)
			recurse(index + 1, objects, current, prev, eval, num, target, res);


		// Note: In the solution, we represent valid expressions like +1+2+3 which we have a leading + sign.
		// However, we would not want a leading - or *

		// Operation 2 - Append '+' before current operand (Already extended)
		objects.push_back("+");
		objects.push_back(currentInStr);
		recurse(index + 1, objects, 0, current, eval + current, num, target, res);
		// Revert
		objects.pop_back();
		objects.pop_back();

		if (!objects.empty()) {
			// Operation 3 - Append '-' before current operand (Already extended)
			objects.push_back("-");
			objects.push_back(currentInStr);
			recurse(index + 1, objects, 0, -current, eval - current, num, target, res);
			// Revert
			objects.pop_back(); 
			objects.pop_back();


			// Operation 4 - Append '*' before current operand (Already extended)
			objects.push_back("*");
			objects.push_back(currentInStr);
			recurse(index + 1, objects, 0, current * prev, eval - prev + (prev * current), num, target, res);
			// Revert
			objects.pop_back();
			objects.pop_back();
		}
    }
};