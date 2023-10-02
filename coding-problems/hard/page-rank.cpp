#include <gtest/gtest.h>

using namespace std;

/*

PageRank (PR) is an algorithm used by Google Search to rank websites in
their search engine results. PageRank was named after Larry Page, one of
the founders of Google. PageRank is a way of measuring the importance of
website pages. According to Google:

PageRank works by counting the number and quality of links to a page to
determine a rough estimate of how important the website is. The underlying
assumption is that more important websites are likely to receive more links
from other websites.

See https://www.geeksforgeeks.org/page-rank-algorithm-implementation/
for nice explanation.

Now the problem:

While there have been changes over the years, the central idea is to assign
each site a score based on the importance of other pages that link to that page.

More mathematically, suppose there are N sites, and each site i has a certain
count Ci of outgoing links. Then the score for a particular site Sj is defined as :

score(Sj) = (1 - d) / N + d * (score(Sx) / Cx+ score(Sy) / Cy+ ... + score(Sz) / Cz))

Here, Sx, Sy, ..., Sz denote the scores of all the other sites that have outgoing links
to Sj, and d is a damping factor, usually set to around 0.85, used to model the probability
that a user will stop searching.

Given a directed graph of links between various websites, write a program that
calculates each site's page rank.


See this https://medium.com/@rellasriram/googles-page-rank-algorithm-3917ca78b18e
to learn the algorithm. It involves doing linear algebra.
Here is one such relevant solution https://www.cs.usfca.edu/~cruse/math202s11/pagerank.cpp

Read this for similar simulation based algorithm of detecting a frog's position in a maze
https://leetcode.com/discuss/interview-question/1088968/graph-question-please-help-google-microsoft-apple

The key take away is that it's about the probability so you have to run a simulation
as the score of any page depends on which one a user visited first. For example,
in case of 4 pages A, B, C and D, in the first iteration or initially, they all have
probability/score 1/4.

I think I will come back to this later after practicing some basic graph traversal problems
and learning the maths described in medium article.

*/

/*
    How to represent a directed graph?
    adjacency list and adjacency matrix?

*/

vector<float> PageRank(const vector<vector<int>> pages)
{
    int N = pages.size();

    vector<float> scores(N, 0.0f);
    float d = 0.85f;

    // O(N)
    auto is_linked = [&](int src, int dst) -> bool
    {
        for (int i = 0; i < pages[src].size(); i++)
        {
            if (pages[src][i] == dst)
                return true;
        }
        return false;
    };

    for (int i = 0; i < N; i++)
    {
        float score = (1 - d) / N;
        for (int j = 0; j < N; j++)
        {
            if (j != i && is_linked(j, i))
            {
                int c_link = pages[j].size();
                score += scores[j];
            }
        }
        scores[i] = d * score;
    }

    return scores;
}

TEST(PageRank, TestCase1)
{
    // suppose 4 pages A, B, C, D are represented as 0, 1,2, 3
    /*
        Here are the links:
        A: B
        B: A, C
        C: A, D
        D, A, B

        i.e. 3 page link to A, 2 pages link to B, 1 page link to C and D
    */
    vector<vector<int>> pages = {
        {1},
        {0, 2},
        {0, 3},
        {0, 1}};

    vector<float> expected;

    // EXPECT_EQ(PageRank(pages), expected);
}