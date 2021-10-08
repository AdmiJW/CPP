#include <string>
using namespace std;

//https://leetcode.com/problems/implement-trie-prefix-tree/
// For more details, look Topics/src/Data_Structures/Trie.java

class Trie {
public:
    struct TrieNode {
        TrieNode* next[26];
        bool isWord = false;
    };

    TrieNode* root;


    Trie(): root(new TrieNode()) {}

    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->next[c - 'a'])
                curr->next[c - 'a'] = new TrieNode();
            curr = curr->next[c - 'a'];
        }
        curr->isWord = true;
    }

    bool search(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->next[c - 'a'])
                return false;
            curr = curr->next[c - 'a'];
        }
        return curr->isWord;
    }

    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            if (!curr->next[c - 'a'])
                return false;
            curr = curr->next[c - 'a'];
        }
        return true;
    }
};