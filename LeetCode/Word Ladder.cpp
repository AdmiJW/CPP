#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

/*
 * 	This is a Graph and BFS problem.
 *
 * 	What we want to determine is the shortest path from the beginWord, passing through intermediate strings, up until
 * 	the endWord (if any)
 *
 * 	We can model this as a graph. The beginWord is actually a node by itself and we are going to start traversal from
 * 	it.
 * 	Then, what nodes are actually 'neighbors' of it? The neighboring nodes are actually the possible strings that can
 * 	be formed by changing one character of the string.
 * 	Of course, we are not going to include each of the possible transformed strings into the actual graph. We'll only
 * 	put what's useful - The words that are actually in the wordList to be neighboring nodes.
 *
 * 	Now we have set up the path which potentially link beginWord to endWord. The traversal algorithm to use is Breadth
 * 	First Search, as it is always searching layer by layer, and guarantees that once endWord is found, we are at the
 * 	shortest level.
 *
 * 	Lets see time complexity:
 * 		Worst case we'll traverse through all the words in wordList. O(N) for this
 * 		Then, for each word, we need to generate all transformations. O(L) where L is the length of the string
 * 		Each character we need to attempt all possible characters (26 for lowercase alphabets). Consider O(C) or O(1)
 * 		Say each characters result in a valid transformation. Then we need to make a copy of the string for each of them.
 * 		O(L) for that then
 *
 *	Thus time complexity is O(L^2 * N)
 *	Space complexity - We use a Set and Queue to store the words. They are O(NL) in size.
 *
 * 	-----------------------------------------------------------------------------
 *
 * 	A BFS is quite good. However, as the BFS gets deeper and the nodes keep increasing, the 'radius' of the search area
 * 	keeps increasing exponentially (Consider a Binary Tree - Each layer has 2^L nodes)
 *
 * 	We could potentially minimize the radius by applying bidirectional Breadth First Search. The BST will be conducted on
 * 	both sides. Each iteration the one with minimum level nodes will be selected to explore.
 *
 * 	Hopefully, the exploration will intersect at the middle, where the BST of one side meets the nodes explored by the
 * 	other sides. This immmediately shows that there is a valid path from One side to another side, which is also at the
 * 	time, minimum distance.
 *
 * 	At worst case, There is no path from one side to another. This one will result in worst case All the nodes be explored,
 * 	which isn't too bad as well as in normal BST
 *
 * 	Time and space complexity is same. It is purely a optimization method.
 */


class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		const int strlen = beginWord.length();
		queue<string> queue;
		unordered_set<string> words(wordList.begin(), wordList.end());
		int level = 0;

		if (!words.count(endWord)) return 0;

		queue.push(beginWord);
		words.erase(beginWord);

		while (!queue.empty()) {
			int size = queue.size();
			++level;

			while (size-- > 0) {
				string poll = queue.front();
				queue.pop();

				if (!poll.compare(endWord)) return level;

				for (int i = 0; i < strlen; ++i) {
					char c = poll[i];
					for (char j = 'a'; j <= 'z'; ++j) {
						poll[i] = j;
						
						if (words.count(poll)) {
							queue.push(poll);
							words.erase(poll);
						}
					}
					poll[i] = c;
				}
			}
		}
		return 0;
	}



	int ladderLength2(string beginWord, string endWord, vector<string>& wordList) {
		const int strlen = beginWord.length();
		unordered_set<string> words(wordList.begin(), wordList.end());

		if (!words.count(endWord)) return 0;

		int level = 0;
		unordered_set<string> set1Obj;		
		unordered_set<string> set2Obj;
		unordered_set<string> newLayerObj;
		auto* set1 = &set1Obj;			//	The one side of BFS we'll handle first
		auto* set2 = &set2Obj;			//	The other side of BFS
		auto* newLayer = &newLayerObj;
		set1->insert(beginWord);
		set2->insert(endWord);
		words.erase(beginWord);		//	Remove to prevent cycle
		words.erase(endWord);

		while (!set1->empty() && !set2->empty()) {

			//	Prioritize to search the smaller sized layer first.
			if (set1->size() > set2->size()) {
				auto* temp = set1;
				set1 = set2;
				set2 = temp;
			}

			++level;		//	Each iteration we proceed BFS by one level.

			//	Since iteration of set cannot be modified, we would need to use a new Set
			//	The set simply stores nodes of new level, so space isn't quite an issue
			for (auto it = set1->begin(); it != set1->end(); ++it) {
				string s = *it;
				for (int i = 0; i < strlen; ++i) {
					char reset = s[i];
					for (char c = 'a'; c <= 'z'; ++c) {
						s[i] = c;

						//	The same node is met already by other side of BFS. Start and end are connected!
						if (set2->count(s)) return level + 1;

						if (words.count(s)) {
							newLayer->insert(s);
							words.erase(s);
						}
					}
					s[i] = reset;
				}
			}
			auto temp = set1;
			set1 = newLayer;
			temp->clear();
			newLayer = temp;
		}
		return 0;
	}


};