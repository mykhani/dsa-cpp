#include "recursion.h"

#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

// print 1 to n. O(n) time, O(n) auxillary space
string print_1_to_n(int n)
{
    std::ostringstream oss;

    std::function<void(int)> helper = [&helper, &oss](int n)
    {
        // base case
        if (n == 0)
            return;

        helper(n - 1);

        oss << n << " ";
    };

    helper(n);

    return oss.str();
}

// print n to 1
string print_n_to_1(int n)
{
    std::ostringstream oss;

    std::function<void(int)> helper = [&helper, &oss](int n)
    {
        // base case
        if (n == 0)
            return;

        oss << n << " ";

        helper(n - 1); // tail recursion, compiler can just say n = n - 1 and goto the start label
                       // created at the start of helper routine. Tail-call elimination optimization
    };

    helper(n);

    return oss.str();
}

// is string a palindrome
bool is_palindrome(string s)
{
    // check two characters
    std::function<bool(string &, int, int)> helper = [&helper](string &s, int p, int q)
    {
        if (p >= q)
            return true;

        if (s[p] != s[q])
            return false;

        return helper(s, p + 1, q - 1);
    };

    return helper(s, 0, s.length() - 1);
}

// factorial calculation using tail-recurssive function
int factorial_rec(int n)
{
    std::function<int(int, int)> helper = [&helper](int n, int result)
    {
        if (n == 0 || n == 1)
            return result;

        return helper(n - 1, result * n);
    };

    return helper(n, 1);
}

// nth_fibonacci
int fibonacci(int n)
{
    // fibonacci is 2 bonnaci, a number is sum of previous 2 numbers
    // 0, 1, 1, 2, 3
    if (n == 0 || n == 1)
        return n;

    /// 0, 1, 1,
    // fib(0) = 0
    // fib(1) = 1
    // fib(2) = fib(1) + fib(0) = 1
    // fib(3) = fib(2) + fib(1) = 2
    // fib(4) = fib(3) + fib(2) = 3

    return fibonacci(n - 1) + fibonacci(n - 2);
}

// sum of first n natural numbers
int sum_natural_numbers(int n)
{
    // sum(1) = 1
    // sum(2) = 2 + sum(1) = 3
    // sum(3) = 3 + sum(2) = 6
    // sum(4) = 4 + sum(3) = 10
    if (n <= 1)
    {
        return n;
    }

    return n + sum_natural_numbers(n - 1);
}

int sum_digits(int n)
{
    // 123
    // 3 + sum(12)
    // 3 + 2 + sum(1)
    if (n == 0)
        return 0;

    int digit = n % 10;

    return digit + sum_digits(n / 10);
}

// cut rope into allowed sizes and find the max slices
int cut_rope(int length, vector<int> sizes)
{
    int max_slices = -1;

    if (length == 0)
        return 0;

    if (length < 0)
        return -1;

    for (auto &&size : sizes)
    {
        // choose one size from the available sizes, cut it and find the maximum slices
        // in the remaining length. If the
        // max slices in remaining length is -1, it means remaining length could not
        // be divided into any valid size and hence our choice is incorrect
        max_slices = std::max(cut_rope(length - size, sizes), max_slices);
    }

    // if none of the sizes slices the length, max_slices == -1
    if (max_slices == -1)
        return -1;

    return max_slices + 1; // add one for the segment cut in this call
    //    return max_slices >= 0 ? (max_slices + 1) : -1; // valid code
}

// generate all possible subsets from a string
vector<string> generate_subsets(string s)
{
    vector<string> result;

    function<void(string, string, int)> helper = [&helper, &result](string s, string curr, int index)
    {
        if (index == s.length())
        {
            result.push_back(curr);
            return;
        }

        helper(s, curr, index + 1);
        helper(s, curr + s[index], index + 1);
    };

    helper(s, "", 0);

    return result;
}

// tower of hanoi
void move(int n, char src, char dst, char aux)
{
    //  1
    //  2
    //  3
    //  -
    //  A    B    C
    // move(3, A, C, B)
    //   move(2, A, B, C)
    //     move(1, A, C, B)
    //       moving disc 1 from a to c
    //     moving disc 2 from a to b
    //     move(1, C, B, A)
    //   move(3) from A to C
    //   move(2) from B to C

    if (n == 1)
    {
        cout << "Move Disc " << n << " from " << src << " to " << dst << endl;
        return;
    }

    move(n - 1, src, aux, dst);
    cout << "Move Disc " << n << " from " << src << " to " << dst << endl;
    move(n - 1, aux, dst, src);
}

// josephus problem
int josephus(int n, int k)
{
    if (n == 1)
        return 0;

    return (k + josephus(n - 1, k)) % n;
}

// find number of subsets with sum
int subsets_with_sum(vector<int> set, int sum)
{
    //
    // if set = {1 2 3}
    // then subsets are
    //                     {}
    //                /             \
//         {}                         1
    //       /     \                  /        \
//    {}         2             1            (1,2)
    //  /    \      /  \          /  \          /     \  
//{}      3    2   (2,3)     1   (1,3)   (1,2)    (1, 2, 3)

    function<int(vector<int>, int, int, int)> helper = [&helper](vector<int> s, int index, int cur_sum, int sum)
    {
        if (index == s.size())
            return (cur_sum == sum) ? 1 : 0;

        return helper(s, index + 1, cur_sum, sum) + helper(s, index + 1, cur_sum + s[index], sum);
    };

    return helper(set, 0, 0, sum);
}
// string permutation
vector<string> permutations(string s)
{
    vector<string> result;
    /* default capture list, all variables used within the lambda
    are captured by reference */
    function<void(int)> permutate_at = [&](int index)
    {
        if (index == s.length() - 1)
        {
            result.push_back(s);
            return;
        }

        for (int i = index; i < s.length(); i++)
        {
            std::swap(s[index], s[i]);
            permutate_at(index + 1);
            std::swap(s[index], s[i]); /* undo swap to recover original string */
        }
    };

    /* start by permutating at index 0 i.e. put all the
    characters at index 0 one by one */
    permutate_at(0);

    return result;
}
