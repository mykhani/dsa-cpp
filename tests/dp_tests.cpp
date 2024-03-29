#include <dp/dp.h>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(DynamicProgramming, FibonacciMemoizationTest)
{
    FibonacciMemo f{100};

    auto result = f(0);
    EXPECT_EQ(result, 0);

    result = f(1);
    EXPECT_EQ(result, 1);

    result = f(5);
    EXPECT_EQ(result, 5);

    result = f(6);
    EXPECT_EQ(result, 8);
}

TEST(DynamicProgramming, FibonacciTabulationTest)
{
    FibonacciTabulation f{100};
    auto result = f(0);
    EXPECT_EQ(result, 0);

    result = f(1);
    EXPECT_EQ(result, 1);

    result = f(5);
    EXPECT_EQ(result, 5);

    result = f(6);
    EXPECT_EQ(result, 8);
}

TEST(DynamicProgramming, LCSRecursiveTest)
{
    string s1{"ABCDGH"};
    string s2{"AEDFHR"};

    int result = LongestCommonSubsequenceRecursive(s1, s2, s1.length(), s2.length());

    EXPECT_EQ(result, 3);
}

TEST(DynamicProgramming, LCSMemoTest)
{
    string s1{"ABCDGH"};
    string s2{"AEDFHR"};

    int result = LongestCommonSubsequenceMemo(s1, s2, s1.length(), s2.length());

    EXPECT_EQ(result, 3);
}

TEST(DynamicProgramming, LCSTabulationTest)
{
    string s1{"ABCDGH"};
    string s2{"AEDFHR"};

    int result = LongestCommonSubsequenceTabulation(s1, s2, s1.length(), s2.length());

    EXPECT_EQ(result, 3);
}

TEST(DynamicProgramming, LongestPalindromicSubsequenceTest)
{
    std::string s{"geeksforgeeks"};

    int result = LongestPalindromicSubsequence(s);

    EXPECT_EQ(result, 5);
}

TEST(DynamicProgramming, ShortestCommonSupersequenceTest)
{
    std::string s1{"geek"};
    std::string s2{"gfek"};

    int result = ShortestCommonSupersequence(s1, s2);

    EXPECT_EQ(result, 5);
}
// CoinChangeCount(std::vector<int> coins, int sum) {
TEST(DynamicProgramming, CoinChangeCountTest)
{
    std::vector<int> coins{1, 2, 3};
    int sum = 4;

    int result = CoinChangeCount(coins, sum);

    EXPECT_EQ(result, 4);

    coins = {2, 5, 3, 6};
    sum = 10;

    result = CoinChangeCount(coins, sum);

    EXPECT_EQ(result, 5);
}

TEST(DynamicProgramming, DummyTest)
{
}
