#include <vector>
using namespace std;

//https://leetcode.com/problems/count-primes/
/*
 * This is a prime number finding problem, which one best approach is to use
 * Sieve of Eratosthenes, given the input size is not too big (5 x 10^6)
 *
 * We modify the sieve of Eratosthenes. Instead of simply marking a flag of true and
 * false, we put a running sum there. For marking off numbers as not prime, we put -1.
 * Therefore when we encounter -1, we know it is not prime and thus not adding to running sum.
 * Else uninitialized value? Add 1 to running sum.
 *
 * For more information on Sieve of Eratosthenes, visit Topics > Misc > Sieve of Eratosthenes
 *
 * ---------------------
 *
 * If you follow the official solution which separates into 2 loop, one for marking and one for
 * counting primes, then in the first loop, you could only do until sqrt(n)
 * (in my solution, this cannot be done because i am doing a running sum)
 *
 * This is because: Recall that a prime number is divisible by only 1 and itself. And when determining
 * this property, we only do until sqrt(n).
 * Say we have a number i larger than sqrt(n). If it is not prime, it surely should've marked off by
 * a prime number smaller than sqrt(n) due to the elimination loop, which iterates as long as smaller
 * than n!
 * Therefore, the worst case would be sqrt(n) * sqrt(n) = n itself, loop terminated
 */

typedef long long int LONG;
class Solution {
public:
	int countPrimes(int n) {
		if (!n) return 0;
		vector<int> runningSum(n, 0);

		for (int i = 2; i < n; ++i) {
			//	Not a prime number as marked previously
			if (runningSum[i] == -1)
				runningSum[i] = runningSum[i - 1];
			//	Is a prime
			else {
				//	Add 1 to running sum
				runningSum[i] = runningSum[i - 1] + 1;
				//	Eliminate multiples of this prime
				for (LONG f = (LONG)i * i; f < n; f += i)
					runningSum[(int)f] = -1;
			}
		}
		return runningSum[n - 1];
	}
};