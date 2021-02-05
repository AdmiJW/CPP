
#include <deque>
#include <string>
using namespace std;

//https://leetcode.com/problems/simplify-path/
/*
 *	Let's observe what the problem wants:
 *		>	Starting with a slash /, it shall be followed by periods '.' or filename.
 *		>	If we have a filename, we do deep one level into the file itself.
 *		>	If we have '..', simply return to the upper level.
 *		>	Multiple slashes treated as single slash.
 *
 *	Therefore we need a data structure which allow us to go back upper one level, while easy for us to
 *	add data into it! It is like recording path histories. Does that ring a bell?
 *
 *	Stack
 *
 *	Firstly, split the string based on delimiter '/'. Then, check each split tokens from front to back
 *
 *	If '.', safely ignore
 *	If '..', pop from stack if its not empty
 *	If filename, push to stack
 *	If empty string, means we have '//' or more slashes. Simply ignore.
 */

class Solution {
public:
	string simplifyPath(string path) {
		const int len = path.length();
		deque<string> tokens;
		size_t pos = 0;


		//	Tokenize manually. Instead of using string::find, you can also utilize stringstream and getline with delimiter
		while (pos < len) {
			size_t end = fmin(path.find('/', pos), len);	//	Since in case like "/..", the last one also need to be recorded. find() will return
															//	an very large integer. So, use min() to ensure everything is good
			tokens.emplace_back(path.substr(pos, end - pos));
			pos = end + 1;
		}


		//	Deque action
		deque<string> endpath;
		for (string& s : tokens) {
			if (s == "" || s == ".") continue;
			if (s == "..") {
				if (!endpath.empty()) endpath.pop_back();
			}
			else
				endpath.emplace_back(s);
		}

		//	Appending to construct valid path
		string res = "";
		for (string& s : endpath)
			res += '/' + s;
		return res.length() ? res : "/";

	}
};