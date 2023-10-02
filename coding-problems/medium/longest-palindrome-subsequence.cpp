#include <gtest/gtest.h>

using namespace std;

string LCS(const string &a, const string &b, int ia, int ib)
{
    string result = "";

    if (ia >= a.length() || ib >= b.length())
        return "";

    string s1;
    string s2;

    if (a[ia] == b[ib])
    {
        result += a[ia];
        result += LCS(a, b, ia + 1, ib + 1);
    }
    else
    {
        s1 = LCS(a, b, ia + 1, ib);
        s2 = LCS(a, b, ia, ib + 1);

        int l1 = s1.length();
        int l2 = s2.length();
        if (l1 > 0 && l1 > l2)
        {
            result += s1;
        }
        else if (l2 > 0 && l2 >= l1)
        {
            result += s2;
        }
    }

    return result;
}

string longestPalindromeSubsequence(string s)
{
    // babad
    // dabab
    string reversed;
    int last = s.length() - 1;

    for (int i = 0; i < s.length(); i++)
    {
        reversed += s[last - i];
    }

    // longest common subsequence between s and reversed
    return LCS(s, reversed, 0, 0);
}

TEST(longestPalindromeSubsequence, TestCase1)
{
    string s{"babad"};
    // rev=    dabab

    EXPECT_EQ(longestPalindromeSubsequence(s), "bab"); // aba is valid too

    s = "aacabdkacaa";
    // r= aacakdbacaa
    EXPECT_EQ(longestPalindromeSubsequence(s), "aacabacaa");
    //   aacabacaa
}