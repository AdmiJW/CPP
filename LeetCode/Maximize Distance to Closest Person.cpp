

#include <vector>
#include <cmath>

/*
    This is a Array problem.

    The best suitable test case for us to use is the one starting with empty seats, and middle empty seats surrounded by 2 person,
    then ending with empty seats. Like so:

        ( ) ( ) (X) ( ) ( ) (X) ( ) ( )

    By iterating over the array once, we can find out the spaces between 2 person, by keeping track of the frequency of the empty
    seats met so far, and resetting it to 0 once we encounter a non empty seat.

    So in example above, when we iterate from first X to the second X, the empty seat counter shall be 2. Then, to find out the
    maximum distance, we just divide it into 2. In cases like (X) ( ) ( ) ( ) (X), we have to return answer = 2 in this case,
    so :
            (Dist + 1 ) / 2
    should be fine, or
            Ceiling( dist / 2.0 )

    Now, we have to deal with edge seats: The one starting empty and the ending empty seats. 
    For the ending seats, we actually don't have to do much. The counter keep incrementing whenever it met with empty seats.
    Therefore, at the end the counter shall be 2, which is exactly the distance from last seat to the closest occupied seats.

    As for starting empty seats, we can run a initial while loop, while the seat is empty, keep incrementing. That will be our
    starting maximum distance.
*/

class Solution {
public:

    int maxDistToClosest( std::vector<int>& seats) {
        int max = 0, dist = 0;

        std::vector<int>::iterator it = seats.begin();

        //  While the starting seat is empty, keep incrementing
        while (it != seats.end() && !*it) {
            max++;
            it++;
        }

        //  Iterate after meeting first non-empty seat
        while (it != seats.end()) {
            //  Occupied seat
            if (*it) {
                max = std::max(max, static_cast<int>( std::ceil( dist / 2.0 ) ) );
                dist = 0;
            }
            //  Empty seat
            else {
                dist++;
            }
            it++;
        }

        //  Now the dist is the distance from last occupied seat to the ending empty seat, if it is empty
        return std::max(max, dist);
    }

};