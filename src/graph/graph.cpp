/*
 * graph.cpp
 *
 *  Created on: 27 Sep 2021
 *      Author: ykhan
 */

#include "graph.h"
#include <queue>
#include <climits>

using namespace std;

vector<int> breadthFirstSearch(vector<vector<int>> graph, int s) {
	queue<int> q;
	vector<int> result;
	vector<bool> visited(graph.size(), false);

	if (s > graph.size() - 1)
		return {};

	q.push(s);
	visited[s] = true;

	while (!q.empty()) {
		auto node = q.front();
		result.push_back(node);
		q.pop();
		for (int i = 0; i < graph[node].size(); i++) {
			auto neighbour = graph[node][i];
			if (!visited[neighbour]) {
				q.push(graph[node][i]);
				visited[neighbour] = true;
			}
		}
	}

	return result;
}

vector<int> breadthFirstSearchHelper(vector<vector<int>> graph, int s, vector<bool> &visited) {
	queue<int> q;
	vector<int> result;

	q.push(s);
	visited[s] = true;

	while (!q.empty()) {
		auto node = q.front();
		q.pop();
		result.push_back(node);
		for (int j = 0; j < graph[node].size(); j++) {
			auto neighbour = graph[node][j];
			if (!visited[neighbour]) {
				visited[neighbour] = true;
				q.push(neighbour);
			}
		}
	}
	return result;
}

// traverse all nodes, graph can be disconnected
// Time O(V+E)
vector<int> breadthFirstSearchDisconnected(vector<vector<int>> graph) {
	vector<bool> visited(graph.size(), false);

	vector<int> result;

	for (int i = 0; i < graph.size(); i++) {
		if (!visited[i]) {
			auto segment = breadthFirstSearchHelper(graph, i, visited);
			result.insert(result.end(), segment.begin(), segment.end());
		}
	}

	return result;
}

int connectedComponents(std::vector<std::vector<int>> graph) {
	vector<bool> visited(graph.size(), false);
	int result = 0;

	for (int i = 0; i < graph.size(); i++) {
		if (!visited[i]) {
			breadthFirstSearchHelper(graph, i, visited);
			result++;
		}
	}

	return result;
}

void depthFirstHelper(vector<vector<int>> &graph,
			int node, vector<int> &result, vector<bool> &visited) {
	result.push_back(node);
	visited[node] = true;

	for (int i = 0; i < graph[node].size(); i++) {
		auto neighbour = graph[node][i];
		if (!visited[neighbour]) {
			depthFirstHelper(graph, neighbour, result, visited);
		}
	}
}

std::vector<int> depthFirstSearch(std::vector<std::vector<int> > &graph, int s) {
	vector<int> result;
	vector<bool> visited(graph.size(), false);

	depthFirstHelper(graph, s, result, visited);

	return result;
}

std::vector<int> depthFirstSearchDisconnected(
		std::vector<std::vector<int> >& graph) {
	vector<int> result;
	vector<bool> visited(graph.size(), false);

	for (int i = 0; i < graph.size(); i++) {
		if (!visited[i])
			depthFirstHelper(graph, i, result, visited);
	}

	return result;
}

void shortestDistanceUnweightedHelper(vector<vector<int>> &graph, vector<int> &result,
		vector<bool> &visited, int &src) {
	queue<int> q;
	q.push(src);
	visited[src] = true;
	result[src] = 0;

	while (!q.empty()) {
		auto node = q.front();
		q.pop();
		for (int i = 0; i < graph[node].size(); i++) {
			auto neighbour = graph[node][i];
			if (!visited[neighbour]) {
				q.push(neighbour);
				visited[neighbour] = true;
				result[neighbour] = result[node] + 1;
			}
		}
	}
}

vector<int> shortestDistanceUnweightedGraph(vector<vector<int> > graph, int src) {
	// Need to use breadth first search, a path for each neighbour
	vector<int> result(graph.size(), INT_MAX);
	vector<bool> visited(graph.size(), false);

	shortestDistanceUnweightedHelper(graph, result, visited, src);

	return result;

}
