/*
 * graph.h
 *
 *  Created on: 27 Sep 2021
 *      Author: ykhan
 */

#ifndef GRAPH_GRAPH_H_
#define GRAPH_GRAPH_H_

/*
 * Graph vs Tree:
 * Tree is used to represent a hierarchy (parent-child relationship)
 * Graph represents friendship relationships where anybody can be a friend of anybody (peer-to-peer)
 * i.e. random connections
 *
 * Graph is represented as a pair of two sets vertices and edges
 * G = (V, E)
 * V = set of graph nodes
 * E = set of graph edges (connections between nodes). An edge is represented as a pair of two vertices (nodes)
 *
 * Two Types:
 * 1. Undirected Graph
 * In an undirected graph, the pair of vertices (edge) is unordered i.e. (v1, v2) = (v2, v1). Example, social network
 *
 * 2. Directed Graph
 * Edges have directions i.e. a pair (v1, v2) is ordered. Example web page links.
 *
 * Characteristics:
 * 1. Degree: The number of edges going through a vertex.
 *
 * In case of directed graph, further classified as:
 * a. In degree: number of edges coming towards a vertex
 *
 * b. Out degree: number of edges coming out of a vertex
 *
 * Directed Graph:
 * 1. In a directed graph, if you sum all of the in degrees (or out degrees), it will give to the number of
 * total edges in the graph i.e.
 * Sum of in degrees = |E| -> number of edges
 * Sum of out degrees = |E|
 *
 * Maximum number of edges = |V| * (|V|- 1) -> complete graph (all possible permutations)
 *
 * Undirected Graph:
 * Sum of all degrees = 2 * |E|
 * Maximum number of edges = 0.5 * (|V| * (|V| - 1)) (combinations) -> complete graph
 *
 * More terms:
 *
 * 1. Walk: A sequence of vertices that we get by following edges
 * 2. Path: A path is a special walk with no repetition of a vertex
 * 3. Cyclic: A graph is called cyclic if there exists a walk that begins and ends with a same vertex
 * i.   Directed Cyclic Graph
 * ii.  Directed Acyclic Graph
 * iii. Undirected Cyclic Graph
 * iv.  Undirected Acyclic Graph
 *
 * Weighted Graph:
 * A directed or undirected graph with weights assigned to edges. Network of roads where weight is the length of the road
 *
 * Graph Representation:
 * 1. Adjacency Matrix (|V| x |V| elements in a matrix, a 1 represents connection from vertex i to j. For undirected graph,
 * it is a symmetric matrix.
 * 2. Adjacency List
 *
 * Adjacency Matrix:
 * 1. size O(|V| x |V|)
 * 2. check if u and v are adjacent
 *
 * Adjacency List:
 * Array of linked list or vector, where array index represents a node and the linked list/vector the connected nodes
 * Space required: O(V+E) for directed and O(v + 2E) for undirected
 *
 * Operations cost of Adjacency list vs Adjacency matrix
 * 1. Space. Matrix O(V*V), list O(V + E)
 * 2. Check if there is an edge from u to v. Matrix O(1), List O(V) (worst case all edges formed with node u). Also
 *    number of V is always greater than edges formed
 * 3. Find all adjacent of u. Matrix O(v), List O(degree(u))
 * 4. Add an edge. Matrix O(1) List O(1)
 * 5. Remove an edge. Matrix O(1), List O(v) -> need to visit the adjacency list to find the node to remove
 *
 * Generally, adjacency list representation of graph is efficient for common graph algorithms
 */

#include <vector>

/*
 * Breadth-first search
 * Given an undirected graph and a source vertex s, print BFS from the given source
 * Breadth-first means you visit the immediate neighbours (adjacent nodes first)
 *
 * Applications:
 * 1. Shortest path in an unweighted (every edge has same weight) graph
 *  (immediate neighbours (one edge-away) are traversed first, then the nodes 2 edges away
 * 2. Crawlers in Search Engine
 * 3. Peer to Peer Networks (torrents)
 * 4. Social Networking Search
 * 5. Garbage Collection (Cheney's algorithm) identify which memory locations are not reachable
 * memory reachable by current set of variables, memory reachable by reachable memory
 * 6. Cycle Detection (DFS can also be used)
 * 7. Ford Fulkerson
 * 8. Broadcasting (send to neighbour first, then neighbours send to their neighbours)
 */
std::vector<int> breadthFirstSearch(std::vector<std::vector<int>> graph, int s);
std::vector<int> breadthFirstSearchDisconnected(std::vector<std::vector<int>> graph);

// Connected components: a group of connected vertices where each vertex is reachable from
// any of the vertex in that group
int connectedComponents(std::vector<std::vector<int>> group);

/*
 *   DFS
 *   Visit neighbour, then neighbour's neighbour
 *
 *   Applications:
 *   1. Cycle Detection
 *   2. Topological sorting (dependency between jobs, and you want to schedule jobs e.g Makefile)
 *   3. Strongly Connected Components
 *   4. Solving maze and similar puzzles
 *   5. Path finding from src to dst. (If we use BFS, the queue might contain nodes not on the path)
 */


std::vector<int> depthFirstSearch(std::vector<std::vector<int>> &graph, int s);
std::vector<int> depthFirstSearchDisconnected(std::vector<std::vector<int>> &graph);

// return a vector of shortest distances from source to all other vertices
std::vector<int> shortestDistanceUnweightedGraph(std::vector<std::vector<int>> graph, int src);


#endif /* GRAPH_GRAPH_H_ */
