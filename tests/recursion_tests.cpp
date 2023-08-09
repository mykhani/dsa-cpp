#include <gtest/gtest.h>
#include <recursion/recursion.h>

using namespace std;

TEST(Recursion, PermutationsTest)
{
    string s{"ABC"};
    vector<string> result = permutations(s);
    vector<string> expected{"ABC", "ACB", "BAC", "BCA", "CBA", "CAB"};

    EXPECT_EQ(result, expected);
}