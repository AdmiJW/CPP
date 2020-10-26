
#include <cmath>

//https://leetcode.com/problems/champagne-tower/

/*
 * 	This is a array simulation problem.
 *
 * 	We have to ignore the fact that every glass has a fixed capacity which it can contain at most 1 cup capacity.
 * 	For every row, we can look at the previous rows result. Lets see an example:
 *
 * 	Say initially we pour down 5 cup worth of champagne. In the first row, the champagne volume contained in the glass
 *  is 5, we will be ignoring the fact that the glass can contain only 1 cup worth of champagne
 *  Onto row 2, the first glass will depend on the last row (First row's) volume of champagne. We will be taking with formula:
 *  	(Volume of last glass champagne - 1) / 2
 *  We minus by 1 because the last row's glass may contain the 1 glass worth of champagne, if it is overflowed.
 *  We divide by 2 because the overflowed champagne flows equally to the left and right.
 *  Of course, if the last glass actually don't overflow, then the calculated value will be negative. Careful of that
 *
 *  Now, the result will be like this:
 *  ( 5 )
 *  ( 2 )( 2 )		<-  (5 - 1) / 2
 *  (   )(   )(   )
 *
 *  Let's compute row 3 now. Now there is 1 cup that will be dependent on 2 cups instead of one. How do we represent that?
 *  THe middle glass actually depends on half on the glass 0 and glass 1 on row 2. That means for every glass, the volume
 *  that flows into it is dependant on:
 *  	Last row glass N and Last row glass N-1
 *
 * 	If we were to iterate backwards, we can reduce the space complexity to just O(N) without losing information!
 */

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {

        double** champagnes = new double* [query_row + 1];
        champagnes[0] = new double[1];
        champagnes[0][0] = poured;

        for (int row = 1; row <= query_row; row++) {
            champagnes[row] = new double[row + 1];

            for (int prev = 0; prev < row; prev++) {
                double overflowed = std::fmax(0, (champagnes[row - 1][prev] - 1) / 2);

                champagnes[row][prev] += overflowed;
                champagnes[row][prev + 1] += overflowed;
            }
        }
        double res = champagnes[query_row][query_glass];

        for (int i = 0; i < query_row; i++) {
            delete[] champagnes[i];
        }
        delete[] champagnes;

        return std::fmin(1, res);
    }

    double champagneTower2(int poured, int query_row, int query_glass) {

        double* current = new double[query_row + 1];
        double* prev = new double[query_row + 1];
        prev[0] = poured;

        for (int row = 1; row <= query_row; row++) {

            current[0] = 0;

            for (int glass = 0; glass < row; glass++) {
                current[glass + 1] = 0;

                double overflow = std::fmax((prev[glass] - 1) / 2, 0);
                current[glass] += overflow;
                current[glass + 1] += overflow;
            }
            double* temp = current;
            current = prev;
            prev = temp;
        }

        double res = prev[query_glass];
        
        delete[] current;
        delete[] prev;
        return std::fmin(1, res);
    }



    double champagneTower3(int poured, int query_row, int query_glass) {
        double* champagne = new double[query_row + 1];
        champagne[0] = poured;

        for (int row = 1; row <= query_row; row++) {
            for (int col = row; col > 0; col--) {
                champagne[col] = (std::fmax(0, (champagne[col] - 1) / 2)) + (std::fmax(0, (champagne[col - 1] - 1) / 2) );
            }
            champagne[0] = (std::fmax(0, (champagne[0] - 1) / 2));
        }
        return std::fmin(1, champagne[query_glass]);
    }
};