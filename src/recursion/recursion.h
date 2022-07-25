#ifndef RECURSION_H
#define RECURSION_H

#include <string>
#include <vector>

using namespace std;

// print 1 to n
string print_1_to_n(int n);

// print n to 1. Performs tail-recurssion
string print_n_to_1(int n);

// is string a palindrome
bool is_palindrome(string s);

// factorial calculation using tail-recurssive function
int factorial_rec(int n);

// nth_fibonacci
int fibonacci(int n);

// sum of first n natural numbers
int sum_natural_numbers(int n);

// return sum of digits recursively
int sum_digits(int n);

// cut rope into allowed sizes and find the max slices. O(len(sizes)^n)
// where n is rope length (upper bound considering in case 3 sizes of length 1)
int cut_rope(int length, vector<int> sizes);

// generate all possible subsets from a string
vector<string> generate_subsets(string s);

// tower of hanoi. O(2^n - 1)
void move(int n, char src, char dst, char aux);

// josephus problem. O(n) time
int josephus(int n, int k);


// find number of subsets with sum
int subsets_with_sum(vector<int> set, int sum);

// string permutation
vector<string> permutations(string s);

#endif

