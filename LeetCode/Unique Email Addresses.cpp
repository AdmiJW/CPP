#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

//https://leetcode.com/problems/unique-email-addresses/
/*
 * This is a string problem.
 *
 * For '.', we ignore it. For '+', we will ignore '+' and everything after it. This rule applies for local name.
 * This is the way to uniformize the email addresses.
 * Then, we store in HashSet, so we can know if current email is unique, or already been sent email before.
 */


class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> exist;

        for (auto& s : emails) {
            string clean = "";
            int delimiter = s.find("@");

            // Uniform the local name - Ignore ., ignore everything after +
            for (char c : s) {
                if (c == '.') continue;
                if (c == '+' || c == '@') break;
                clean += c;
            }
            clean += '@' + s.substr(delimiter + 1);
            exist.insert(clean);
        }
        return exist.size();
    }
};