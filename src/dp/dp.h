#ifndef DP_H
#define DP_H

#include <string>

/*
    Dynamic programming in simple terms is an optimization over recurssion
    store the results of subproblems so you don't compute them again. It's like caching the computation results

    There are two ways to implement DP.
    1. Memoization (Top down) Recursive. Easy to implement
    2. Tabulation (Bottom up) Iterative i.e. loop. Better performance than memoization but difficult to implement.

    Applications:
    1. Bellman Ford Algorithm: used in routing, find the shortest path from source to destination
    2. Floyd Warshall algorithm: find shortest path between every pair of vertices in a graph
    3. Diff Utility e.g. git diff. Based on (LCS Longest Common Subsequence)
    4. Search Close Words. Find the nearest matching word
    5. Resouce allocation (0-1 knapsack)

    Example:
    Consider fibonacci numbers 0, 1, 1, 2, 3, 5 represented as f0, f1, f2, f3, f4, f5
    so a general fn = f(n-2) + f(n-1)
    Here how a recurssive call stack would look like

                                f(5)
                    f(4)                          f(3)
            f(3)            f(2)            f(2)         f(1)
    f(2)        f(1)    f(1)    f(0)    f(1)    f(0)
f(1)    f(0)

    You can see several overlapping computations f(3) -> 2 times, f(2) - > 3 times

    With memoization, it looks like

                                    f(5)
                    f(4)                          f(3)
            f(3)            f(2)
    f(2)        f(1)
f(1)    f(0)

    Total function calls = 2n-1 e.g for n = 5, total 9 function calls. The amount of work done in each call is constant theta(1)
    So time complexity is O(n)

    The toughest part in dynamic programming solution is to come up with a recursive solition with overlapping problems.
*/

int FibonacciMemo(int n); // Top-down
int FibonacciTabulation(int n); // bottom-up, solve subproblems first, kind of iterative, Time O(n), Space O(n)
/*
    What is subsequence?
    Subsequences of "CDA" => "", "C", "D", "A", "CD", "CA", "DA", "CDA"
    Longest common subsequence LCS of
    "ABCDGH" and
    "AEDFHR"
    is ADH i.e. with length 3
    Longest Common Subsequence problem
    Take two strings s1 and s2 with lengths m and n and return the length of
    longest common subsequence

    In a string of length n, there can be 2^n possible subsequences
*/

/*
    Subsequence vs substring
    Substing: contingous characters occuring in some order
    Subsequence: characters (not necessarily contiguous) occuring in a same sequence/order
*/

/*
 Time complexity of naive recursive implementation
 Time O(2^n) image m == n, and no matches
                         (n,n)
            (n - 1, n)                  (n, n - 1)
    (n-2, n)    (n-1, n-1)      (n-1, n-1)        (n, n-2)
    ...

    1,2,4,....,2^n
*/
int LongestCommonSubsequenceRecursive(std::string& s1,  std::string& s2, int m, int n);

// LCS with memoization, s1 and s2 remain same in each recusive call, only m and n change
// so we have two-dimensional memo array
// Time O(mn)
int LongestCommonSubsequenceMemo(std::string& s1,  std::string& s2, int m, int n);
// Time O(mn)
int LongestCommonSubsequenceTabulation(std::string& s1,  std::string& s2, int m, int n);

// Given a string s, find the longest palindromic subsequence inside it
// a palindromic subsequence is a subsequence that reads same in both directions
// i.e. left to right and right to left
// For example s = "geeksforgeeks", the palindromic subsequence is "eeree" or "eeoee"
int LongestPalindromicSubsequence(std::string& s);

// A common supersequence is a string of which both s1 and s2 are subsequences
// A longest common supersuquence could be formed by just attaching s1 and s2
// For shortest, take LCS, and then add characters not common from both s1 and s2
int ShortestCommonSupersequence(std::string& s1, std::string& s2);

// Count maximum combinations of coins that make amount sum
// For example coins = {1, 2, 3}, sum = 4, count = 4
// {1, 1, 1, 1}, {1, 1, 2}, {1, 2, 1}, {1, 3}
int CoinChangeCount(std::vector<int> coins, int sum);
#endif
