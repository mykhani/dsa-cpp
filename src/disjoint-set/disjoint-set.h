#ifndef DISJOINT_SET_H_
#define DISJOINT_SET_H_

#include <vector>
#include <utility>

/*
 In mathematics, two sets are said to be disjoint sets if they have no element in common

 Disjoint set data structure is suitable for problems where we have one big universal
 set and multiple subsets of it as disjoint subsets i.e. a single element cannot be
 part of two separate subsets. If it is added to a subset, it creates one single
 bigger subset

 Without union by rank, we get a chained tree hence O(n) for find
    0  1  2  3  4

 union(3, 4)            unionbyrank(3,4)
 0  1 2 3               0 1 2 3
          \                    \
           4                    4

 union(2, 3)            0 1  3
 0  1 2                     / \
       \                   2   4
        3
         \
          4

 union(1, 2)           0    3
 0  1                     / \ \
     \                   1   2  4
      2
       \
        3
         \
          4

 union(0, 1)               3
 0                      / /  \ \
  \                    0  1  2  4
   1
    \
     2
      \
       3
        \
         4
*/

class DisjointSet
{
private:
    /*rep, rank */
    std::vector<int> parent; // each array item represent root of the tree (arr is tree forrest)
    std::vector<int> rank;   // rank is the height of tree beginning from a certain root

public:
    explicit DisjointSet(int n);
    void Union(int a, int b);       // make representative of 'a' the representative of b's representative
    void UnionByRank(int a, int b); // make the higher ranked element representative of other
    int Find(int k);                // Time O(n) without union by rank. O(logn) with union by rank, O(1)
                                    // with union by rank and path compression
    int FindWithPathCompression(int k);
    int Rank(int k);
};

// Kruskal's algorithm for minimum spanning tree inside connected, undirected,
// and weighted graph (represented as array of edges instead of adjacency matrix or list)

struct Edge
{
    int src;
    int dst;
    int weight;

    Edge(int s, int d, int w) : src{s}, dst{d}, weight{w} {}

    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

int KruskalAlgorithm(std::vector<Edge> graph, int v);

#endif