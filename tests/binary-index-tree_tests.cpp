#include <gtest/gtest.h>
#include <binary-index-tree/binary-index-tree.h>

using namespace std;

TEST(BinaryIndexTree, GetParentTest)
{
    vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    BinaryIndexTree tree{arr};

    EXPECT_EQ(tree.Parent(1), 0); //
    EXPECT_EQ(tree.Parent(2), 0); //
    EXPECT_EQ(tree.Parent(3), 2);
    EXPECT_EQ(tree.Parent(4), 0); //
    EXPECT_EQ(tree.Parent(5), 4);
    EXPECT_EQ(tree.Parent(6), 4);
    EXPECT_EQ(tree.Parent(7), 6);
    EXPECT_EQ(tree.Parent(8), 0); //
    EXPECT_EQ(tree.Parent(9), 8);
    EXPECT_EQ(tree.Parent(10), 8);
    EXPECT_EQ(tree.Parent(11), 10);
    EXPECT_EQ(tree.Parent(12), 8);
}

TEST(BinaryIndexTree, GetSumTest)
{
    vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    BinaryIndexTree tree{arr};

    EXPECT_EQ(tree.GetSum(1), 3); // sum of element from index 0 to 1 i.e. 2 elements
    EXPECT_EQ(tree.GetSum(2), 6);

    tree.Update(0, 10);
    EXPECT_EQ(tree.GetSum(0), 10);
    EXPECT_EQ(tree.GetSum(1), 12);
}