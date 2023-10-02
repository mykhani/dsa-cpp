#include <gtest/gtest.h>
#include <sorting/sorting.h>

using namespace std;

TEST(Sorting, TestInsertionSort)
{
    vector<int> arr = {54, 26, 93, 17, 77, 31, 44, 55, 20};
    InsertionSort(arr);
    vector<int> expected{17, 20, 26, 31, 44, 54, 55, 77, 93};

    EXPECT_EQ(arr, expected);
}

TEST(Sorting, TestQuickSort)
{
    vector<int> arr = {54, 26, 93, 17, 77, 31, 44, 55, 20};
    QuickSort(arr);
    vector<int> expected{17, 20, 26, 31, 44, 54, 55, 77, 93};

    EXPECT_EQ(arr, expected);
}

TEST(Sorting, TestMergeSort)
{
    vector<int> arr = {54, 26, 93, 17, 77, 31, 44, 55, 20};
    MergeSort(arr);
    vector<int> expected{17, 20, 26, 31, 44, 54, 55, 77, 93};

    EXPECT_EQ(arr, expected);
}