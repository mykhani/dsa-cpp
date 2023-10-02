#include <gtest/gtest.h>
#include <utility>

using namespace std;

// O(n^3)
string longestPalindromeSubstringBrute(string s)
{
    function<bool(const string &, int, int)> isPalindrome = [&isPalindrome](const string &s, int start, int end) -> bool
    {
        while (start < end)
        {
            if (s[start] != s[end])
                return false;

            start++;
            end--;
        }

        return true;
    };

    int maxLen = 0;
    int start = 0;
    // O(n^2) form all substrings starting with index i
    for (int i = 0; i < s.length(); i++)
    {
        for (int j = i; j < s.length(); j++)
        {
            if (isPalindrome(s, i, j)) // O(n)
            {
                if (j - i + 1 > maxLen)
                {
                    maxLen = j - i + 1;
                    start = i;
                }
            }
        }
    }
    // longest common subsequence between s and reversed
    return s.substr(start, maxLen);
}
/*
   The total number of subarrays in an array of size N is N * (N + 1) / 2
   For example, for s="abcd" with N = 4, the total number of substrings is (4*5)/2 =10
   "a", "ab", "abc", "abcd", "b", "bc", "bcd", "c", "cd", "d"

   When you select the starting element, you can make 4 or n substrings
   With second element, you can make n-1 substrings
   With nth element, 1 substring
   If you sum all substrings together, it forms AP i.e. total sum = N + N-1 + N-2 + 1 = (N(N+1))/2

   See https://www.youtube.com/watch?v=WpYHNHofwjc for explanation
*/
// Time O(n^2), space O(n^2)
// TODO: try doing a recusive approach based on the same idea
// IsPalindrome(s, 0, n)
// IsPalindrome(s, 0, 0) => 1

string longestPalindromeSubstringDP(const string &s)
{
    int n = s.length();

    vector<vector<bool>> m(n, vector<bool>(n, false)); // create a matrix of nxn

    /*
            For example string is abcd
          | b | a | b | a | d |   -> ending index 0, 1, 2, 3, 4
        --+---+---+---+---+---+
        b | T | F | T | F | F |
        --+---+---+---+---+---+
        a | X | T | F | T | F |
        --+---+---+---+---+---+
        b | X | X | T | F | F |
        --+---+---+---+---+---+
        a | X | X | X | T | F |
        --+---+---+---+---+---+
        d | X | X | X | X | T |
        --+---+---+---+---+---+
        ^
        starting index 0, 1, 2, 3, 4

    where X marks don't care. For example m[2][1] = X because there is no
    substring thats starts with c and ends at b
    T represents palindrome, all single character substrings are palindromes

    To check if a string with start index i and end index j is palindrome,
    IsPalindrome(s, i, j) {
        if (s[i] == s[j] && IsPalindrome(s, i+1, j-1))
            return true;
        return false;
    }
    */

    int start = 0;
    int maxLen = 0;
    // Fill the matrix diagonally instead of row-wise
    // 00, 11, 22, 33, 44, 55 for offset=0
    // 01, 12, 23, 34, 45     for offset=1
    // 02, 13, 24, 35,        for offset=2 or length of size 3
    // 03, 14, 25             for offset=3;
    // 04, 15
    for (int offset = 0; offset < n; offset++)
    {
        for (int i = 0, j = offset; j < n; i++, j++)
        {
            if (offset == 0)
            {
                // single char is always palindrome
                m[i][j] = true;
            }
            else if (offset == 1)
            {
                // substring of length 2, checking endpoint chars
                m[i][j] = (s[i] == s[j]);
            }
            else
            {
                // substring of length 3 and more
                m[i][j] = (s[i] == s[j]) && m[i + 1][j - 1];
            }

            if (m[i][j])
            {
                // as offset is increasing every time we encounter m[i][j] true
                // length will be maximum
                start = i;
                maxLen = j - i + 1;
            }
        }
    }
    return s.substr(start, maxLen);
}

// babad
/*
                    0,1 1,2 2,3, 3,4
                    0,2 1,3, 2,4
                    0,3 1,4
                    0,4


*/
string longestPalindromeSubstringRecursive(const string &s)
{
    int start = 0;
    int maxLen = 0;

    function<bool(int, int)> isPalindrome = [&](int i, int j) -> bool
    {
        if (i == j)
        {
            // in case the string s has only one character
            if (maxLen == 0)
            {
                maxLen = 1;
                start = i;
            }
            return true;
        }

        if (s[i] == s[j])
        {
            if ((j - i == 1) || isPalindrome(i + 1, j - 1))
            {
                if (j - i + 1 > maxLen)
                {
                    maxLen = j - i + 1;
                    start = i;
                }
                return true;
            }
        }

        isPalindrome(i + 1, j);
        isPalindrome(i, j - 1);
        return false;
    };

    isPalindrome(0, s.length() - 1);

    return s.substr(start, maxLen);
}

TEST(longestPalindromeSubstringBrute, TestCase1)
{
    string s{"babad"};
    // rev=    dababs

    EXPECT_EQ(longestPalindromeSubstringBrute(s), "bab"); // aba is valid too

    s = "aacabdkacaa";
    // r= aacakdbacaa
    EXPECT_EQ(longestPalindromeSubstringBrute(s), "aca");
    //   aacabacaa
}

TEST(longestPalindromeSubstringDP, TestCase1)
{
    string s{"babad"};
    // rev=    dababs

    EXPECT_EQ(longestPalindromeSubstringDP(s), "aba"); // aba is valid too

    s = "aacabdkacaa";
    // r= aacakdbacaa
    EXPECT_EQ(longestPalindromeSubstringDP(s), "aca");
    //   aacabacaa
}

TEST(longestPalindromeSubstringRecursive, TestCase1)
{
    string s = "aacabdkacaa";
    // r= aacakdbacaa
    EXPECT_EQ(longestPalindromeSubstringRecursive(s), "aca");

    s = "aa";
    EXPECT_EQ(longestPalindromeSubstringRecursive(s), "aa");

    s = "a";
    EXPECT_EQ(longestPalindromeSubstringRecursive(s), "a");
}