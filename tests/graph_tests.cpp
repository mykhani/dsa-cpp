/*
 * graph_tests.cpp
 *
 *  Created on: 9 Oct 2021
 *      Author: ykhan
 */

#include "../src/graph/graph.h"
#include <gtest/gtest.h>

using namespace std;

TEST(Graph, BFSTest) {
	vector<vector<int>> g = {
			{1, 2},
			{},
			{0, 3, 4},
			{2},
			{2}
	};

	vector<int> expected{0, 1, 2, 3 ,4};
	vector<int> result = breadthFirstSearch(g, 0);

	EXPECT_EQ(result, expected);

	g = {
		{1, 2},
		{0, 2, 3},
		{0, 1, 3},
		{1, 2},
	};

	expected = {0, 1, 2, 3};
	result = breadthFirstSearch(g, 0);

	EXPECT_EQ(result, expected);

	g = {
		{1, 2, 5},
		{0, 3},
		{0, 4},
		{1, 5},
		{2, 5},
		{0, 3, 4}
	};

	expected = {0, 1, 2, 5, 3, 4};
	result = breadthFirstSearch(g, 0);

	EXPECT_EQ(result, expected);
}

TEST(Graph, BFSDisconnectedTest) {
	vector<vector<int>> g = {
			{1, 2},
			{0, 3},
			{0, 3},
			{},
			{5, 6},
			{4, 6},
			{4, 5}
	};

	vector<int> expected{0, 1, 2, 3 ,4, 5, 6};
	vector<int> result = breadthFirstSearchDisconnected(g);

	EXPECT_EQ(result, expected);
}

TEST(Graph, BFSConnectedComponentsTest) {
	vector<vector<int>> g = {
			{1, 2},
			{0, 2},
			{0, 1},
			{4},
			{3},
			{6, 7},
			{5},
			{5, 8},
			{7}
	};

	EXPECT_EQ(3, connectedComponents(g));
}

TEST(Graph, DFSTest) {
	vector<vector<int>> g = {
			{1, 4},
			{0, 2},
			{1, 3},
			{},
			{0, 5, 6},
			{4, 6},
			{4, 5}
	};

	vector<int> expected{0, 1, 2, 3 ,4, 5, 6};
	vector<int> result = depthFirstSearch(g, 0);

	EXPECT_EQ(result, expected);

	g = {
		{1, 2},
		{0, 3, 4},
		{0, 3},
		{1, 2},
		{1, 5},
		{4}
	};

	expected = {0, 1, 3, 2 ,4, 5};
	result = depthFirstSearch(g, 0);

	EXPECT_EQ(result, expected);
}

TEST(Graph, DFSDisconnectedTest) {
	vector<vector<int>> g = {
		{1, 2},
		{0, 2},
		{0, 1},
		{4},
		{3},
	};

	vector<int> expected = {0, 1, 2 ,3, 4};
	vector<int> result = depthFirstSearchDisconnected(g);

	EXPECT_EQ(result, expected);
}

TEST(Graph, ShortestDistanceUnweightedGraphTest) {
	vector<vector<int>> g = {
			{1, 2},
			{0, 2, 3},
			{0, 1, 3},
			{1, 2}
	};

	vector<int> expected{0, 1, 1, 2};
	vector<int> result = shortestDistanceUnweightedGraph(g, 0);

	EXPECT_EQ(result, expected);

	g = {
		{1, 2, 4},
		{0, 3},
		{0, 3, 4},
		{1, 2, 5},
		{0, 2, 5},
		{3, 4}
	};

	expected = {0, 1, 1, 2, 1, 2};
	result = shortestDistanceUnweightedGraph(g, 0);

	EXPECT_EQ(result, expected);
}
