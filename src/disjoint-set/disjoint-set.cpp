#include "disjoint-set.h"
#include <stack>
#include <algorithm>

using namespace std;

DisjointSet::DisjointSet(int n)
{
    for (int i = 0; i < n; i++)
    {
        parent.push_back(i);
        rank.push_back(0);
    }
}

void DisjointSet::Union(int a, int b)
{
    // find the representative of a
    int rep_a = Find(a);
    // find the representative of b
    int rep_b = Find(b);

    while (parent[rep_b] != rep_b)
    {
        rep_b = parent[rep_b];
    }

    // subsets already joined, nothing to do
    if (rep_a == rep_b)
        return;

    parent[rep_b] = rep_a;
    // update rank i.e. rank_a = rank_b + 1
    rank[rep_a] += rank[rep_b] + 1;
}

void DisjointSet::UnionByRank(int a, int b)
{
    int rep_a = Find(a);
    int rep_b = Find(b);

    // subsets already joined, nothing to do
    if (rep_a == rep_b)
        return;

    if (rank[rep_a] > rank[rep_b])
    {
        // make a represent b, rank remains unchanged as it is greater
        parent[rep_b] = rep_a;
        // update a's rank
        // rank[rep_a] = std::max(rank[rep_a], 1 + rank[rep_b]);
    }
    else if (rank[rep_a] < rank[rep_b])
    {
        // make b represent a, rank of b remains unchanged as it is greater
        parent[rep_a] = rep_b;
        // rank[rep_b] = std::max(rank[rep_b], 1 + rank[rep_a]);
    }
    else
    {
        // default cause, make a represent b and increase its rank
        parent[rep_b] = rep_a;
        rank[rep_a]++;
    }
}

// Find representative of item k
int DisjointSet::Find(int k)
{
    // recursive
    if (parent[k] == k)
        return k;

    return Find(parent[k]);

    // Iterative
    // int rep_k = k;
    // while (parent[rep_k] != rep_k)
    // {
    //     rep_k = parent[rep_k];
    // }

    // return rep_k;
}

int DisjointSet::FindWithPathCompression(int k)
{
    if (parent[k] == k)
        return k;

    parent[k] = Find(parent[k]);

    return parent[k];

    // // Iterative
    // int rep_k = k;
    // stack<int> traversed;

    // while (parent[rep_k] != rep_k)
    // {
    //     traversed.push(rep_k);
    //     rep_k = parent[rep_k];
    // }

    // // update the representative of all the elements traversed
    // // while finding the representative
    // while (!traversed.empty())
    // {
    //     int i = traversed.top();
    //     traversed.pop();
    //     parent[i] = rep_k;
    // }

    // return rep_k;
}

int DisjointSet::Rank(int k)
{
    return rank[k];
}

// Time O(ElogE), Space O(v)
int KruskalAlgorithm(vector<Edge> graph, int v)
{
    // Greedy algorithm

    // sort edges by weight
    // std::sort(graph.begin(), graph.end(), EdgeComp{});
    std::sort(graph.begin(), graph.end()); // O(ElogE) where E is edges

    // let A, B, C, D represented by 0, 1, 2, 3 respectively
    DisjointSet set{v}; // Time O(v), Space O(v)

    int total_distance = 0;

    // a minimum spanning tree consists of v - 1 edges e.g. 3 edges connect 4 nodes
    for (int i = 0, s = 0; s < v - 1; i++) // O(E)
    {
        auto &[src, dst, w] = graph[i];

        // if vertices not already spanned/joined
        if (set.Find(src) != set.Find(dst)) // O(1) for disjoint set with union by rank & path compression
        {
            total_distance += w;
            set.Union(src, dst);
            s++;
        }
    }

    return total_distance;
}
