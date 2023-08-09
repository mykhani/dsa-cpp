#include <gtest/gtest.h>
#include <backtracking/backtracking.h>

using namespace std;

TEST(Backtracking, PermutationsExcludingTest)
{
    string s{"ABC"};

    vector<string> result = PermutationsExcluding(s, "AB");
    vector<string> expected{"ACB", "BAC", "BCA", "CBA"};

    EXPECT_EQ(result, expected);
}