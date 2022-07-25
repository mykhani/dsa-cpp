#ifndef MATHEMATICAL_H
#define MATHEMATICAL_H

#include <vector>

using namespace std;

// count digits of an integer. O(digits)
int count_digits(int n);

// check if an integer is a palindrome
bool is_palindrome(int n);

// calculate factorial of an integer
int factorial(int n);

// find the trailing zeroes in the result of a factorial
int trailing_zeroes_in_factorial(int n);

// Euclidean algorithm for finding gcd. O(log(min(x,y)))
int find_gcd(int x, int y);

// product = lcm * gcd 
int find_lcm(int x, int y);

// check if an integer is a prime
bool is_prime(int n);

// get a vector of prime factors. O(sqrt(n))
vector<int> prime_factors(int n);

// get all factors of a number O(sqrt(n))
vector<int> factors(int n);

// get prime integers less thatn or equal to number, naive O(n * sqrt(n)
// sieve of eratosthenes 
vector<int> range_prime(int n);

// compute power. O(log(n))
int pow(int base, int exponent);
#endif