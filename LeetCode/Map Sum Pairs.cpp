#include <string>
#include <unordered_map>
using namespace std;

//https://leetcode.com/problems/map-sum-pairs/
/*
 * 	This is a Trie problem.
 *
 * 	By brute force, every time we query the sum, we have to traverse through each key in our HashMap, checking if it is matching
 * 	our prefix or not to sum it up.
 * 	Time taken would be O(KL) where K is number of keys inserted and L be the average length of each key
 *
 * 	Another way is to store each possible prefixes into the Hashmap. For example in case 'apple', we will store 'a', 'ap', 'app',
 * 	'appl' and 'apple' into the HashMap.
 * 	Although this does make query speed fast in O(1) - Assuming HashMap and String is constant time, it does hog up some space
 *
 * ==============================================================
 *
 * 	The optimal solution would be to use Trie data structure. Trie saves our prefixes and within each TrieNode, we can store the
 *	sum of the current prefixes.
 *	When one word is replaced, we simply use a HashMap to lookup the previous value, and apply the difference to each of the involved
 *	nodes.
 */

class Node {
public:
    Node* next[26] = {};
    int sum;
    Node() : sum(0) {}
    ~Node() {
        for (int i = 0; i < 26; ++i)
            if (next[i]) delete next[i];
    }
};

class MapSum {
public:
    unordered_map<string, int> map;
    Node* root;

    /** Initialize your data structure here. */
    MapSum() : root(new Node()) {}

    void insert(string key, int val) {
        int diff = (map.count(key)) ? val - map[key] : val;		// The value to add to the nodes
        Node* curr = root;

        // Traverse all the characters of key. Adding delta to it
        for (char c : key) {
            curr->sum += diff;

            if (!(curr->next[c - 'a']))
                curr->next[c - 'a'] = new Node();
            curr = curr->next[c - 'a'];
        }
        curr->sum += diff;

        // Remember to put it into HashMap
        map[key] = val;
    }


    int sum(string prefix) {
        // Simply traverse the trie for sum. Return 0 if not valid prefix
        Node* curr = root;
        for (char c : prefix) {
            if (!(curr->next[c - 'a']))
                return 0;
            curr = curr->next[c - 'a'];
        }
        return curr->sum;
    }

};