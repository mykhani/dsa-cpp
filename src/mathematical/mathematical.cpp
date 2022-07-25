#include <cmath> // for sqrt
#include "mathematical.h"

// count digits of a number. O(digits)
int count_digits(int n)
{
    int digits = 0;
    
    // convert negative to positive integers
    n = n > 0 ? n : -n;
    
    while (n > 0) {
        n /= 10;
        digits++;
    }
    
    return digits;
}

// check if an integer is a palindrome
bool is_palindrome(int n)
{
    int orig = n;
    int reversed = 0;
    
    while (n > 0) {
        // take the rightmost digit of the input number
        int digit = n % 10;
        // update the reversed number
        reversed = reversed * 10 + digit;
        // reduce the input number
        n /= 10;
    }
    
    // compare the original and reversed integer
    return reversed == orig;
}

// calculate factorial of an integer
int factorial(int n)
{
    int result = 1;
    
    while (n > 1) {
        result *= n;
        n--;
    }
    
    return result;
}

// find the trailing zeroes in the result of a factorial
int trailing_zeroes_in_factorial(int n)
{
    // find the number of pairs of 2 and 5 in the prime factorization of factorial sequence
    // Note that the number of 2 is always greater than number of 5 in prime factors
    // therefore, count only the number of 5's
    // e.g 6*5*4*3*2*1 contains a single 2,5 pair and hence 1 zero in the output of 720
    // in factorial(10), the seq is (2*5)*9*8*7*6*5*4*3*2*1 which contains 2 (2,5) pair
    // so it has 2 zeroes in the output of = 3628800
    // factorial(15), (3*5)*(2*7)*13*(2*6)*11*(2*5)*9*(2*4)*7*(2*3)*5*(2*2)*3*2*1 -> so many 2's but only 3 5's
    // so count only 5 factors i.e. (3*5)*14*13*12*11*(2*5)*9*8*7*6*5*4*3*2*1
    // every 5 element contribte to one pair
    // Now consider number where there are multiple 5 factosr e.g. 25, 50 etc i.e every 25th number in factorial sequence
    // (2*5*5), 49, 48, 47, 46...,
    // so to find the numbers in factorial sequence, that hold a power of 5,5^2, 5^3, we can find the number of 5s, so
    int count = 0;
    
    for (int divisor = 5; divisor <= n; divisor *= 5) {
        count += (n / divisor); // in first iteration find every 5th element, 25th in second and so on
    }
    
    return count;
}

//  Euclidean algorithm O(log(min(x, y)))
int find_gcd(int x, int y)
{
//    The modulus operation takes care of it i.e. if x < y then x % y = x
//    second arg is the smallest
//    if (x < y)
//        return find_gcd(y, x);
//        
    if (y == 0)
        return x;
        
    return find_gcd(y, x % y);
}

int find_lcm(int x, int y)
{
    // product = lcm * gcd
    // lcm = product / gcd;
    int gcd = find_gcd(x, y);
    int product = x * y;
    return product / gcd;
}

// check if an integer is a prime
bool is_prime(int n)
{
    // the naive approach is to return false if any number from n-1 to 2 divides the n O(n)
    int factor = n - 1;
    
    // The optimized approach to check if any number from sqrt(n) to 2 divides the n O(sqrt(n))
    // Rationale: the factors exist in pairs e.g for 36, (1,36), (2,18), (3,12), (4,9), (6,6)
    // for 42 (1,42), (2,21), (3,14), (6,7): factors are 1,2,3,6,7,14,21,42 -> so we need to
    // check only till 6
    factor = sqrt(n);
    
    if (n == 1) {
        return false;
    }
    
    // optimization
    
    if (n == 2 || n == 3) {
        return true;
    }
    /*
     * 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
     * removing special cases 1,2 and 3: 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
     * removing multiples of 2: 3, 5, 7, 9, 11, 13, 15, 17, 19, 21
     * removing multiples of 3: 5, 7, 11, 13, 17, 19, 
     * 5, 7,
     */
    if ((n % 2 == 0) || (n % 3 == 0))
        return false;
   
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    
    return true;
}

// get a vector of prime factors. O(sqrt(n))
vector<int> prime_factors(int n)
{
    vector<int> factors;
    
    // 36: (1,36), (2,18), (3,12), (4,9) ,(6,6)
    // search for a factor from 2 to sqrt(n), if none found, the number itself is prime
    // find the prime factor's power
    // reduce the number by prime factor's power
    // repeat
    // 84: (2,42),(2,21), (3, 7) 
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            // prime factor
            factors.push_back(i);
            n /= i;
        }
    }
    
    // last prime factor
    if (n > 1) {
        factors.push_back(n);
    }
    
    return factors;
}

// get all factors of a number. O(sqrt(n))
vector<int> factors(int n)
{
    vector<int> factors;
    
    factors.push_back(1);
    
    // add 1 and number itself as factor
    // go from 2 to sqrt(n)
    int i;
    
    // first take the left factors of the pair
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
        }
    }
    
    for (; i > 1; i--) {
        if (n % i == 0 and i != n / i) {
            factors.push_back(n / i);
        }
    }
    
    // add the number itself
    factors.push_back(n);
    
    return factors;
}

// get prime integers less thatn or equal to number, naive O(n * sqrt(n)
// efficient: sieve of eratosthenes O(n)
vector<int> range_prime(int n)
{
    //sieve of eratosthenes: create a boolean array, the index of which represents the number
    // and boolean value represent if it is prime
    vector<bool> isPrime(n+1, true); // size is n+1 so the last index n represent the value n
    vector<int> result;
    
//    // naive implementation O(n * sqrt(n))
//    vector<int> primes;
//    for (int i = 2; i <= n; i++) {
//        if (is_prime(i))
//            primes.push_back(i);
//    }
//    return primes;

    
//    // Even bettern than taking modulo, the indices represent a number, so just mark indices that are multiple of 2 as false
//    for (int i = 6; i < isPrime.size(); i++) {
//        // mark the multiples of 2, 3 and 5 as false
//        if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0)
//            isPrime[i] = false;
//    }
    // 2, 4, 6 , 8
    // 6,
    // 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30
    // remove multiples of 2 (excluding 2 itself)
    // 2, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29
    // remove multiples of 3 (exc. itself)
    // 2, 3, 5, 7, 11, 13, 17, 19, 23, 25, 29
    // remove multiples of 5
    // 2, 3, 5, 7, 11, 13, 17, 19, 23, 29
    // remove mutiples of 7 (for n = 50) and so on
    
    // The maximum prime factor inside number can be sqrt(n) e.g 7 in 50
    for (int i = 2; i * i <= n; i++) {
        // for prime numbers, i.e. 2, 3, 5, 7, ...
        if (isPrime[i]) {
            // mark all multiples as not prime
            for (int j = 2 * i; j <=n ; j += i) {
                    isPrime[j] = false;
            }
        }
    }
    
    for (int i = 2; i < isPrime.size(); i++) {
        if (isPrime[i])
            result.push_back(i);
    }
    
    return result;
}

// compute power
int pow(int base, int exponent)
{
    int result = 1;
    
//    // naive O(n) solution
//    while (exponent > 0) {
//        result *= base;
//        exponent--;
//    }
    // divide and conquer
    // base case

      // recursive O(logn) time and O(logn) space complexity
//    if (exponent == 0)
//        return 1;
//        
//    int tmp = pow(base, exponent / 2);
//    int temp = tmp * tmp;
//    
//    if (exponent % 2 == 0) {
//        return temp;
//    } else {
//        return temp * base;
//    }

    // iterative solution, time O(logn) and space O(1)
    int curr_power = base;
    
    // e.g 3^19 = 3^16 * 3^2 * 3^1 = 0b10011 
    // 2^3 = 2^2 * 2*1
    while (exponent > 0) {
        if (exponent & 1) //if (exponent % 2 != 0)
            result *= curr_power;
        exponent >>= 1; //exponent /= 2;
        curr_power = curr_power * curr_power;
    }
    
    return result;
}
