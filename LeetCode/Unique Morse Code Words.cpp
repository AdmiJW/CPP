
#include <vector>
#include <unordered_set>
#include <string>
#include <iostream>

#include <memory>

//https://leetcode.com/problems/unique-morse-code-words/

/*
 * 	This is a Set problem.
 *
 * 	Given strings, we can parse them into the respective morse code. How do we know if similar morse code
 * 	had occurred before? We record it. Is there O(1) time of checking? using HashSet to hash the string
 *
 * 	========================================================================================
 *
 * 	We can also try to perform the hashing ourselves. Since every length of word cannot exceed 12, and
 * 	each morse code length is maximum 4, and morse code has 2 states only: . and - . We can actually
 * 	represent them in binary form.
 * 		>	.	Represent 0
 * 		>	-	Represent 1
 *
 * 	Using bitwise shifting, we can easily represent each character. The bits that we need are 48 bits.
 * 	A long will suffice.
 *
 * 	Be careful not to start with 0 but with 1. Since when 0 gets left shifted it is still 0. This will cause
 * 	collision cases like
 * 		>	....-
 * 		>	..-
 * 	They will be same!
 *
 * 	=======================================================================================
 *
 * 	Also, we could use Trie to check if it exists before. If it does exist, there must be a corresponding
 * 	matching node in the Trie already.
 * 	If it exists, continue
 * 	Else, add 1 to the unique words counter
 *
 */

class Solution {
public:
	const static std::vector< std::string> codes;

	int uniqueMorseRepresentations( std::vector< std::string>& words) {
		std::unordered_set< std::string> unique;

		for (auto s : words) {
			std::string sb;
			
			for (char c : s) 
				sb.append( codes[c - 'a']);

			unique.insert(sb);
		}
		return unique.size();
	}

	int uniqueMorseRepresentations2(std::vector< std::string>& words) {
		std::unordered_set< long long int> unique;

		for (auto s : words) {
			long long int l = 1l;

			for (char c : s) {
				std::string code = codes[c - 'a'];
				for (char codeC : code) {
					l <<= 1;
					l += codeC == '.' ? 0 : 1;
				}
			}
			unique.insert(l);
		}

		return unique.size();
	}



	struct TrieNode {
		TrieNode* dot;
		TrieNode* dash;
		bool isWord;
		TrieNode() : dot(nullptr), dash(nullptr), isWord(false) {}
		~TrieNode() {
			delete dot;		//	Recursively clear memory
			delete dash;
		}
	};
	TrieNode* createOrTraverse(TrieNode* node, std::string charToInsert) {
		for (char c : charToInsert) {
			if (c == '.') {
				if (!node->dot) node->dot = new TrieNode();
				node = node->dot;
			}
			else {
				if (!node->dash) node->dash = new TrieNode();
				node = node->dash;
			}
		}
		return node;
	}
	int uniqueMorseRepresentations3(std::vector<std::string> words) {
		TrieNode* root = &TrieNode();
		int res = 0;

		for (auto s : words) {
			TrieNode* node = root;
			for (char c : s) {
				node = createOrTraverse(node, codes[c - 'a']);
			}

			if (!node->isWord) res++;
			node->isWord = true;
		}
		return res;
	}
};

const std::vector< std::string> Solution::codes = { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",
													".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",
													".--","-..-","-.--","--.." };