#include <gtest/gtest.h>
#include <binary-segment-tree/binary-segment-tree.h>

using namespace std;

TEST(SegmentTree, SegmentTreeCreationTest)
{
    vector<int> arr{10, 20, 30, 40};
    BinarySegmentTree bst{arr};
    vector<int> result = bst.Tree();
    vector<int> expected{100, 30, 70, 10, 20, 30, 40};
    EXPECT_EQ(result, expected);

    vector<int> arr2 = {10, 20, 30, 40, 50, 60};
    BinarySegmentTree bst2{arr2};
    vector<int> result2 = bst2.Tree();
    vector<int> expected2{
        210, 60, 150, 30, 30,
        90, 60, 10, 20, INT_MAX,
        INT_MAX, 40, 50, INT_MAX, INT_MAX};
    EXPECT_EQ(result2, expected2);
}

TEST(SegmentTree, GetSumTest)
{
    vector<int> arr{10, 20, 30, 40};
    BinarySegmentTree bst{arr};
    EXPECT_EQ(bst.GetSum(3, 3), 40);
    EXPECT_EQ(bst.GetSum(0, 2), 60);
    EXPECT_EQ(bst.GetSum(1, 3), 90);
    EXPECT_EQ(bst.GetSum(0, 4), 100);
}

TEST(SegmentTree, UpdateTest)
{
    vector<int> arr{10, 20, 30, 40};
    BinarySegmentTree bst{arr};
    EXPECT_EQ(bst.GetSum(0, 2), 60);
    EXPECT_EQ(bst.GetSum(1, 3), 90);

    bst.Update(1, 25);

    EXPECT_EQ(bst.GetSum(0, 1), 35);
    EXPECT_EQ(bst.GetSum(1, 1), 25);
    EXPECT_EQ(bst.GetSum(0, 3), 105);
}