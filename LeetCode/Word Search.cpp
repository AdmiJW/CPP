#include <vector>
#include <string>
using namespace std;

//https://leetcode.com/problems/word-search/

/*
 * 	A DFS Backtracking problem. We have to basically travel through each cell in the board. Each cell, we call upon a search function recursively, to have
 * 	it see if the board cell character matches the start of word.
 *
 * 	Inside the recursive call, if it doesn't match the character, return false
 * 	If the recursive call index exceeds the length of string itself, that means the previous characters had all been matched. Return true.
 *
 * 	Notice that we can't use the same grid twice. This doesn't boil down to just knowing the previous grid alone. We have to keep track of
 * 	which grid was used previously to match the word. We could actually make a boolean array to mark those visited grid true, so that during
 * 	recursion function, if it detects the current grid's boolean value is true, then it will not use this grid and therefore return false.
 *
 * 	To optimize space, we would just record the used grid in-place using the original board. We mark it with a character that shouldn't be
 * 	in possible values in the board, anything like * % # or space will do.
 *
 * 	-----------------------------
 *
 * 	The pruning is meant to avoid visiting the same grid twice if we already previously already computed the result and with no result.
 * 	Say we try to search for the character at index i in the grid[r][c]. If we previously already established that recursion at grid[r][c]
 * 	with the index i yields no result, then we can pretty much ignore the search already. However recording the result seems to take up extra
 * 	space - Namely O(r * c * i) where r and c is dimensions of board, and i is the length of word
 */

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j)
                if (exist(board, word, i, j, 0)) return true;
        }
        return false;
    }


    bool exist(vector<vector<char>>& board, string& word, int r, int c, int index) {
        if (index == word.length() ) return true;
        if (r == -1 || r == board.size() || c == -1 || c == board[0].size() || board[r][c] != word[index]) return false;

        // Mark as visited
        char prev = board[r][c];
        board[r][c] = ' ';

        if (exist(board, word, r - 1, c, index + 1)) return true;
        if (exist(board, word, r, c - 1, index + 1)) return true;
        if (exist(board, word, r + 1, c, index + 1)) return true;
        if (exist(board, word, r, c + 1, index + 1)) return true;

        // Undo changes
        board[r][c] = prev;
        return false;
    }
};