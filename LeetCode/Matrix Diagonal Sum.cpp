#include <vector>
using namespace std;


class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        const int len = mat.size();
        int sum = 0;

        for (int i = 0; i < len; ++i) sum += mat[i][i] + mat[i][len - i - 1];

        return (len % 2 == 1)?
               sum - mat[len / 2][len / 2]:
               sum;
    }
};
