#include <stack>
#include <string>
#include <cctype>
using namespace std;


//https://leetcode.com/problems/decoded-string-at-index/
/*
 * 	This may not seem like it, but it is a Stack problem.
 *
 * 	Even though the problem has the string at most size 100, in the worst case, the string may start with one alphabet
 * 	character, followed by 99 '9' digits. This means the decoded string would actually be of length 9^99,
 * 	taking forever to compute and good luck storing that much of information
 *
 * 	Since we just have to find out the Kth character, we could 'virtually' decode it. Keep a pointer and a variable which
 * 	keep track of whether this character is at which position in the string
 *
 * 	>	If we met with a alphabet character, just add 1 to the counter. Then, check if the counter hits K, then return
 * 		this character.
 *
 * 	>	If met with a digit, it means WHATEVER behind will be repeated by this digit D times. Therefore, the counter
 * 		needs to be multiplied by D times.
 *
 * 	After multiply by D, check if the counter had exceeded or equal K or not. If yes, it means we have gone past the
 * 	character we are searching already. We already have enough information to find out the character, it is in previous
 * 	'virtually' decoded string.
 *
 * 	First, we have to deduce a formula which is able to find out among the repeated strings, which position of the
 * 	character we are actually looking for. Consider the following case:
 *
 * 			ABC3
 *
 * 	When repeated, it is ABCABCABC
 * 	Now, K = 1, K = 4 and K = 7 should yield the same character 'A'. Our job is to simplify K such that when K=4 or k=7,
 * 	it is reduced to K=1, since it is a cycle in nature and exceeding it will make us return to beginning of string
 *
 * 	The formula actually goes as follows:
 *
 * 			To get index     (Eg ABC, length is 3)      (We get answer in index, convert back to position)
 * 			( K - 1 )    %   Length before multiplier    + 1
 *
 * 	You can see the formula working in above case:
 * 			K = 4, (4-1) % 3 + 1 = 		1st character
 * 			K = 7, (7-1) % 3 + 1 = 		1st character
 *
 * 	-------------------------------------------------------------------------
 *
 * 	Now that is definitely reduced to a valid K that is not pointing to a character that is pointing to a character in
 * 	repeated string, but in base string.
 * 	However, recall that the string may have multiple multiplications. After reducing one multiplication, the K might still
 * 	pointing to a character in repeated string in previous multiplications!
 *
 * 	By recording the records of multiplication, we can easily keep reducing K until it is ensured that K is positioned
 * 	not in a repeated string but the base string. We will record two things:
 *
 * 			Length of string before multiplication
 * 			Multiplication Factor
 *
 * 	Recall that length * multi is the length of the multiplicated string. If K is less than that length of multiplicated
 * 	string, it means that there's a chance that K is pointing in a repeated string and something has to be done with it.
 * 	Otherwise, K lies outside of the multiplicated string so we cannot do anything.
 *
 * 	Therefore comes the algo:
 *
 * 			If (counter >= K)				//	Overshot. Time to reduce
 *
 * 				while ( stackLength.peek * stackMulti.peek >= K )	//	K lies within the repeated string. Reduce
 *
 * 					K = (K-1) % stackLength.peek + 1
 * 					stackLength.pop
 * 					stackMulti.pop								//	After reduced, this multiplication is resolved
 *
 *
 * 	Then, after K is successfully reduced, it is now ensured that K can be found easily in the base String S given,
 * 	which is less than length 100. Call the function again, and rest assured it can find the character.
 */

typedef long long int LONG;


class Solution {
public:
	string decodeAtIndex(string S, int K) {
		stack<LONG> storeLen;
		stack<int> storeMulti;

		LONG currLen = 0;

		for (char c : S) {
			if (isalpha(c)) {
				if (++currLen == K) return string(1, c);
			}
			else {
				storeLen.push(currLen);
				storeMulti.push(c - '0');
				currLen *= (c - '0');		//	Previous recorded strng will be repeated this factor times
			
				//	We've progressed over the character. Now we should find where exactly is the character already
				//	by redefining K to point to the exact character in original string, not the virtually repeated ones
				if (currLen >= K) {

					while (!storeLen.empty() && K <= storeLen.top() * storeMulti.top()) {
						int idx = (K - 1) % storeLen.top();
						K = idx + 1;
						storeLen.pop(); storeMulti.pop();
					}
					return decodeAtIndex(S, K);
				}
			}
		}
		return "";
	}
};