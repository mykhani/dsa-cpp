#ifndef BIT_MAGIC_H
#define BIT_MAGIC_H

#include <vector>
#include <string>
#include <queue>

using namespace std;

// check wether the kth bit is set. O(1)
bool check_bit(int n, int k);

// count the set bits of an integer. O(1) using lookup table
int count_set_bits(int n);

// check if an integer is a power of 2. O(1)
bool isPow2(int n);

// find odd occurring integer i.e. the integer occuring odd times. 1, 3, 5 etc
int find_odd_occurring(vector<int> vec);

// Given an array of n number that has values in range [1..n+1]. Every number appears
// exactly once. Hence one number is missing. Find the missing number.
// e.g arr[] = {1, 4, 3}, result = 2
int find_missing_number(vector<int> vec);

// find two odd occurring
vector<int> find_two_odd_occurring(vector<int> vec);


vector<std::string> create_powerset(string vec);

// align a number
int align(int n, int alignment);

// align power of two
int align_pow2(int n, int pow2);

// count of the longest sequence of zeros in the binary representation of the integer
// Time O(logn), space O(1)
int countLongestSequenceZeroes(int n);

#endif
