#include <unordered_map>
#include <vector>
#include <cstdlib>
using namespace std;

//https://leetcode.com/problems/insert-delete-getrandom-o1/
/*
 * 	The basic idea is to use an array list and a hash map.
 * 	The hash map stores the value as key for direct look up whilst the value is the position of it in the array list.
 * 	The array list is used for obtaining a random value using its index (since rand() generates from 0 to n-1). It maps from index to the value
 * 	itself
 *
 * 	Initially I used another Set to store deletedIndex every time the delete method is called. However this results in extra space and probably
 * 	result in longer time when getRandom() method is called as it has to keep iterating for the random number which isn't in the Set. Additionally,
 * 	to access the elements in the set I have to use iterator which needs to be updated every time the set is changed.
 *
 * 	Another better idea is to use Overwriting. Every time the delete is called, the element in the array list is overwritten with the last element in
 * 	the array list. Then the array list remove( size - 1) method is called upon the last index, which uses only O(1) time because no shifting is done.
 * 	The only extra thing to do is to update the value to index mapping in the hash map.
 */

class RandomizedSet {
    unordered_map<int, int> mapToIndex;
    vector<int> nums;

public:
    RandomizedSet() {}

    bool insert(int val) {
        if (mapToIndex.count(val)) return false;
        nums.push_back(val);
        mapToIndex[val] = nums.size() - 1;
        return true;
    }

    bool remove(int val) {
        if (!mapToIndex.count(val)) return false;

        // Overwrite the element in arraylist with the last element
        int i = mapToIndex[val];
        nums[i] = nums[nums.size() - 1];
        mapToIndex[nums[i]] = i;
        mapToIndex.erase(val);

        // Remove last element
        nums.pop_back();
        return true;
    }

    int getRandom() {
        int index = rand() % nums.size();
        return nums[index];
    }
};