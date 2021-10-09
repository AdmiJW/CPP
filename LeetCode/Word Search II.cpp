#include <string>
#include <vector>
using namespace std;


//https://leetcode.com/problems/word-search-ii/

/*
 * 	For this question, it is inevitable the need to iterate through every single character in the grid. However, having to loop through every searched word for each
 * 	character is more time consuming. Is there any way to easily get access to the characters and next characters in constant time? Trie/Prefix Tree is your solution.
 *
 * 	The Trie is constructed as follows:
 * 		-There will be a root node where itself is not actually representing a character, but contains a Map to instantly find any word starting character in constant time
 * 		-At the end of a word, there may be still more characters to connect in HashMap (Imagine 'sat' and 'saturate'). Therefore we will kept a additional String variable
 * 		 in the TrieNode object. If it is null, then it is not a full word, else it stores the complete word
 *
 *
 */


// The Trie class that we will use in our problem
class Trie {
public:
    struct TrieNode {
        TrieNode* next[26];

        ~TrieNode() {
            for (TrieNode* t : next)
                if (t) delete t;
        }
    };

    TrieNode* root;

    // Constructor. Constructs a Trie up to layer 10 as given by problem constraint (word length <= 10)
    Trie(vector<vector<char>>& board) : root(new TrieNode()) {
        for (int r = 0; r < board.size(); ++r) {
            for (int c = 0; c < board.size(); ++c)
                recurse(board, root, r, c, 0);
        }
    }

    bool exists(string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!(curr->next[c - 'a'])) return false;
            curr = curr->next[c - 'a'];
        }
        return true;
    }

    ~Trie() {
        if (root) delete root;
    }

private:
    void recurse(vector<vector<char>>& board, TrieNode* t, int r, int c, int l) {
        // Base case
        if (l == 10 || r == -1 || r == board.size() || c == -1 || c == board[0].size() || board[r][c] == ' ') return;

        char ch = board[r][c];
        if (!(t->next[ch - 'a']))
            t->next[ch - 'a'] = new TrieNode();
        TrieNode* next = t->next[ch - 'a'];

        board[r][c] = ' ';

        recurse(board, next, r + 1, c, l + 1);
        recurse(board, next, r - 1, c, l + 1);
        recurse(board, next, r, c + 1, l + 1);
        recurse(board, next, r, c - 1, l + 1);

        board[r][c] = ch;
    }
};



class Solution {
public:

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie t(board);
        vector<string> res;
        for (auto& w : words) {
            if (t.exists(w))
                res.push_back(w);
        }
        return res;
    }

};


