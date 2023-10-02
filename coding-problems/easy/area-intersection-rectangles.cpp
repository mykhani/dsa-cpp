#include <gtest/gtest.h>
#include <utility>
using namespace std;

/*
Given two rectangles on a 2D graph, return the area of their intersection.
If the rectangles don't intersect, return 0.

For example, given the following rectangles:

{
    "top_left": (1, 4),
    "dimensions": (3, 3) # width, height
}
and
{
    "top_left": (0, 5),
    "dimensions": (4, 3) # width, height
}

Return 6
*/

// O(1)
int AreaIntersectionRectangles(pair<int, int> topLeftA, pair<int, int> dimA,
                               pair<int, int> topLeftB, pair<int, int> dimB)
{
    /*
       situations for no intersection (vertical)
       topLeftA + dimA[1] < topLeftB or
       topLeftB + dimB[1] < topLeftA

                                    dimA[1]
             +----------------------+
             |                      |
             |                      |
             +----------------------+
            topLeftA                dimA[0]

                                  dimB[1]
              +-------------------+
              |                   |
              |                   |
              +-------------------+
            topLeftB              dimB[0]
    */
    if (topLeftA.second + dimA.second < topLeftB.second ||
        topLeftB.second + dimB.second < topLeftA.second)
    {
        return 0;
    }

    /*
       situations for no intersection (horizontal)
       topLeftA[0] + dimA[0] < topLeftB[0] or
       topLeftB[0] + dimB[0] < topLeftA[0]

                                dimA[1]                        dimB[1]
             +----------------------+           +--------------+
             |                      |           |              |
             |                      |           |              |
             +----------------------+           +--------------+
     topLeftA[0]                  dimA[0]    topLeftB[0]       dimB[0]


    */
    if (topLeftA.first + dimA.first < topLeftB.first ||
        topLeftB.first + dimB.first < topLeftA.first)
    {
        return 0;
    }

    int h = 0; // horizontal intersection
    int v = 0; // vertical intersection

    int A1 = topLeftA.first;
    int A2 = A1 + dimA.first;
    int B1 = topLeftB.first;
    int B2 = B1 + dimB.first;
    /* A1        A2
            B1        B2

        The intersection of segments A1A2 and B1B2 is B1 - A2 or max(A1, B1) - min(A2, B2)
    */
    h = abs(std::max(A1, B1) - std::min(A2, B2));

    A1 = topLeftA.second;
    A2 = A1 + dimA.second;
    B1 = topLeftB.second;
    B2 = B1 + dimB.second;

    v = abs(std::max(A1, B1) - std::min(A2, B2));

    return h * v;
}

TEST(AreaIntersectionRectangles, TestCase1)
{
    EXPECT_EQ(AreaIntersectionRectangles({1, 4}, {3, 3}, {0, 5}, {4, 3}), 6);
    EXPECT_EQ(AreaIntersectionRectangles({1, 4}, {3, 3}, {1, 4}, {3, 3}), 9); // totally overlapping
    EXPECT_EQ(AreaIntersectionRectangles({1, 4}, {3, 3}, {4, 5}, {4, 3}), 0); // only wall intersecting
    EXPECT_EQ(AreaIntersectionRectangles({1, 4}, {3, 3}, {1, 4}, {4, 3}), 9);
    EXPECT_EQ(AreaIntersectionRectangles({1, 4}, {3, 3}, {4, 5}, {4, 3}), 0);
}