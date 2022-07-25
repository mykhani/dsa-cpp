/*
 * greedy.h
 *
 *  Created on: 30 May 2021
 *      Author: ykhan
 */

#ifndef GREEDY_GREEDY_H_
#define GREEDY_GREEDY_H_

#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <tree/tree.h>
//#include "../tree/tree.h"

using namespace std;

/*
 * Greedy algorithms are suitable to solve optimization problems
 * Optimization problems -> minimize or maximize something
 *
 * Greedy algorithms might not always work.
 * E.g from coins {18, 10, 1} find minimum coins that make
 * 20 returns 3 i.e. 1 coin of 18 and 2 coins of 1 instead
 * of returning 2 for 2 coins of 10
 *
 * General pattern
 * from a list of items:
 *     select an item
 *     check if it is feasible (at this point contributes to optimal solution
 *
 * Greedy algorithm doesn't consider big picture, only the current point in time
 *
 * Applications
 * Finding optimal solutions
 * * Activity Selection
 * * Fractional Knapsack
 * * Job sequencing
 * * Prim's algorithm
 * * Kruskal's algorithm
 * * Dijkstra's algorithm
 * * Huffman coding (optimal loss-less compression)
 *
 * Find close to optimal solutions for NP hard problems like
 * * Traveling salesman problem
 *
 * There are some problems in CS called NP hard problems for which
 * no solution exists with a polynomial time complexity
 */

// find the minium number of coins that makeup a value
int minimumCoins(std::vector<int> coins, int value);

// select maximum activities possible
// time  O(nlogn), space O(1)
int maximumActivities(std::vector<std::pair<int, int>> activities);

// time O(nlogn) space O(1)
int fractionalKnapsack(vector<std::pair<int, int>> items, int capacity);
/* Find the optimal sequence of jobs to return the maximum profit
 * Rules:
 * * Each job takes one unit of time
 * * Only one job can be assigned at a time
 * * time starts with 0
 *
 * The vector jobs is a pair of deadline and profit.
 * Deadline is the time by which a job must finish
 */
int jobSequencing(std::vector<std::pair<int, int>> jobs);

/*
 * Huffman coding is a popular lossless compression technique
 * Lossless: decoding the encoded data results in the original data
 * There are some lossy compression algorithms as well which are used
 * for encoding videos.
 *
 * It is variable length encoding e.g. instead of using fixed 8-bits
 * to represent a character in ASCII, the length of encoding may vary
 *
 * Let say you have 100 characters long string abaabaca
 * Frequencies: a = 70, b = 20, c = 10
 *
 * Greedy (optimization): assign the smallest length code to the character
 * with maximum frequency. For e.g a occurs 70 times. If we assign 2-bit
 * code to represent a, that will optimize the space
 *
 * The important criteria for an encoding to be valid is that none of the
 * code should be a prefix of another code. E.g lets say 1 represents a and 11
 * represents b. Then if we encounter 111 during decompression, it could
 * be read as aaa or ab or ba.
 */
struct Huffman {
	int frequency;
	char code;

	Huffman(char c, int f) :
			code{c}, frequency{f} {
	}
};

std::shared_ptr<TreeNode<Huffman>> buildHuffmanTree(
		std::vector<std::pair<char, int>> frequency);

#endif /* GREEDY_GREEDY_H_ */
