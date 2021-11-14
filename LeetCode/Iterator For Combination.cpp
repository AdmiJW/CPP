#include <string>
#include <queue>
#include <vector>
using namespace std;


//https://leetcode.com/problems/iterator-for-combination/
/*
 * 	Using backtracking, we can generate the combinations for a string.
 * 	We can pick the characters from first one until the length() - charleft one as first letter. Then, the problem becomes
 * 	subproblem where character pick must be one of the characters to the right, with charleft - 1. Repeat the recursion
 *
 * 	========================================================================================================
 *
 * 	However, this directly ignores the purpose of iterator. If I initialized the iterator and only call the next() once before
 * 	disposing, all the computations are wasted!
 *
 * 	Instead, the optimal way is to only compute the next lexicographical string once on every next() call. This would potentially
 * 	save up a lot of computations in the case where the iterator is rarely called.
 *
 * 	I done this by keeping a K length int array of 'pointers', where K is the combinationLength.
 * 	For example, if characters = 'abcde' and combinationLength = 2,
 *
 * 	Then pointers = [1,3] means currently, the result string is "bd", which is at index 1 and 3 of base string respectively.
 * 	On each next() call, the pointers will be incremented, due to the nature of combination.
 */


// Backtracking solution - Generates everything on init, but ignores the purpose of iterator.
class CombinationIterator {
public:
    queue<string> queue;
    string base;

    CombinationIterator(string characters, int combinationLength) {
        base = characters;

        string s = "";
        recursion(s, 0, combinationLength);
    }

    void recursion(string& sb, int idx, int charleft) {
        if (!charleft) {
            queue.push(sb);
            return;
        }

        for (int i = idx; i <= base.length() - charleft; ++i) {
            sb += base[i];
            recursion(sb, i + 1, charleft - 1);
            sb.pop_back();
        }
    }

    string next() {
        string res = queue.front();
        queue.pop();
        return res;
    }

    bool hasNext() {
        return !queue.empty();
    }
};




// Iterator based solution - Compute only when necessary
class CombinationIterator {
public:
    string base;
    string nextstr;
    vector<int> pointers;

    CombinationIterator(string characters, int combinationLength) {
        base = characters;
        pointers = vector<int>(combinationLength);

        // Initialize pointers to [0,1,2,3,4...]
        for (int i = 0; i < pointers.size(); ++i) pointers[i] = i;
        nextstr = getStringFromPointers();
    }

    string next() {
        string res = nextstr;
        generateNext();
        return res;
    }

    bool hasNext() {
        return nextstr.size();
    }

    string getStringFromPointers() {
        string s = "";
        for (int i : pointers) s += base[i];
        return s;
    }


    void generateNext() {
        // 1 - Obtain the position to update
        int i = pointers.size() - 1;
        while (i >= 0 && pointers[i] == i + (base.length() - pointers.size())) --i;

        // Case - Exhausted next combination.
        if (i == -1) {
            nextstr = "";
            return;
        }

        // 2 - Increment pointers
        ++pointers[i];
        for (i = i + 1; i < pointers.size(); ++i) pointers[i] = pointers[i - 1] + 1;

        // 3 - Update the next
        nextstr = getStringFromPointers();
    }
};
