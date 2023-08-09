#include <gtest/gtest.h>

#include <disjoint-set/disjoint-set.h>
#include <climits>

using namespace std;

TEST(DisjointSet, UnionTest)
{
    DisjointSet s{5};

    s.Union(3, 4); // make 3 represent 4
    EXPECT_EQ(s.Find(3), 3);
    EXPECT_EQ(s.Find(4), 3);
    EXPECT_EQ(s.Rank(3), 1);

    s.Union(2, 3); // make 2 represent 3,4
    EXPECT_EQ(s.Find(2), 2);
    EXPECT_EQ(s.Find(3), 2);
    EXPECT_EQ(s.Find(4), 2);
    EXPECT_EQ(s.Rank(2), 2);

    s.Union(1, 2); // make 1 represent 2,3,4
    EXPECT_EQ(s.Find(1), 1);
    EXPECT_EQ(s.Find(2), 1);
    EXPECT_EQ(s.Find(3), 1);
    EXPECT_EQ(s.Find(4), 1);
    EXPECT_EQ(s.Rank(1), 3);

    s.Union(0, 1); // make 0 represent 1, 2, 3, 4
    EXPECT_EQ(s.Find(0), 0);
    EXPECT_EQ(s.Find(1), 0);
    EXPECT_EQ(s.Find(2), 0);
    EXPECT_EQ(s.Find(3), 0);
    EXPECT_EQ(s.Find(4), 0);
    EXPECT_EQ(s.Rank(0), 4);

    s.FindWithPathCompression(4);
}

TEST(DisjointSet, UnionByRankTest)
{
    DisjointSet s{5};

    s.UnionByRank(3, 4); // make 3 represent 4 rank=1
    EXPECT_EQ(s.Find(3), 3);
    EXPECT_EQ(s.Find(4), 3);
    EXPECT_EQ(s.Rank(3), 1);

    s.UnionByRank(2, 3); // make 3 represent 2,4 with rank=1
    EXPECT_EQ(s.Find(2), 3);
    EXPECT_EQ(s.Find(3), 3);
    EXPECT_EQ(s.Find(4), 3);
    EXPECT_EQ(s.Rank(3), 1);

    s.UnionByRank(1, 2); // make 3 represent 1,2,4 rank=1
    EXPECT_EQ(s.Find(1), 3);
    EXPECT_EQ(s.Find(2), 3);
    EXPECT_EQ(s.Find(3), 3);
    EXPECT_EQ(s.Find(4), 3);
    EXPECT_EQ(s.Rank(3), 1);

    s.UnionByRank(0, 1); // make 3 represent 0,1,2,4 rank=1
    EXPECT_EQ(s.Find(0), 3);
    EXPECT_EQ(s.Find(1), 3);
    EXPECT_EQ(s.Find(2), 3);
    EXPECT_EQ(s.Find(3), 3);
    EXPECT_EQ(s.Find(4), 3);
    EXPECT_EQ(s.Rank(3), 1);
}

TEST(DisjointSet, KruskalsAlgorithm)
{
    vector<Edge> graph = {
        Edge{0, 1, 9},  // AB 9
        Edge{0, 2, 5},  // AC 5
        Edge{0, 3, 10}, // AD 10
        Edge{1, 3, 8},  // BD 8
        Edge{2, 3, 7}   // CD 7
    };

    EXPECT_EQ(KruskalAlgorithm(graph, 4), 20);

    graph = {
        // add edge 0-1
        Edge{0, 1, 10},
        // add edge 0-2
        Edge{0, 2, 8},
        // add edge 0-3
        Edge{1, 2, 5},
        // add edge 1-3
        Edge{1, 3, 3},
        // add edge 2-3
        Edge{2, 3, 4},
        // add egde 2-4
        Edge{2, 4, 12},
        // add edge 3-4
        Edge{3, 4, 15}};

    EXPECT_EQ(KruskalAlgorithm(graph, 5), 27);
}