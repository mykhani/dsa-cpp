/*
 * binarysearchtree.h
 *
 *  Created on: 16 Jun 2021
 *      Author: ykhan
 */

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include "../tree/tree.h"
#include <set>
#include <utility>
/*
 * Background on Binary Search Tree
 * Time complexities of various operations for different datastructures
 * 					Array (Unsorted)	Array(Sorted)	Linkedlist	BST(balanced)	Hashtable
 * Search			O(n)				O(logn)			O(n)		O(logn)			O(1)
 * Insert			O(1)				O(n)			O(1)		O(logn)			O(1)
 * Delete			O(n)				O(n)			O(n)		O(logn)			O(1)
 * Find closest		O(n)				O(logn)			O(n)		O(logn)			O(n)
 * Sorted traversal O(nlogn)			O(n)			O(nlogn)	O(n)			O(nlogn)
 */

/*
 * Set in STL C++
 * Set datatype in C++ stores data in increasing order by default
 * internally implemented as self-balancing binary tree (Red Black Tree)
 * To store data in decreasing order std::set<int, greater<int>>
 *
 * s.erase(beginIt, endIt) removes elements between beginIt and endIt-1
 * s.lower_bound(n) : returns an iterator to the first element with value greater than or equal to n
 * s.upper_bound(n): returns an iterator to the first element with value greater than n
 *
 * Time complexity for various operations
 * begin(), end(), rbegin(), rend(), cbegin(), cend(), size(), empty() -> O(1)
 *
 * insert(), find(), count(), lower_bound(), upper_bound(), erase(var) -> O(logn)
 *
 * erase(it) : amortized O(1)
 *
 * Applications:
 * 1. Sorted stream of data: data coming in and you want to store them in an order
 * 2. Doubly-ended priority queue (s.begin() returning smallest while s.end()-1 returning largest) Both O(1) ops
 */

/*
 * Map in STL C++
 * Similar to set, implemented as self-balancing Red-Black Tree
 * Elements in map are ordered by key
 * If a a key already exists, map.insert is ignored even if the newly inserted value is different than existing
 *
 * map[key] vs map.at(key): [] add the key with default value if it doesn't exist. at() throws an exception
 * if the key doesn't already exist
 * begin(), end(), rbegin(), rend(), size(). empty() -> O(1)
 * count(), find(), insert(key), erase(key), operator[] -> O(logn)
 *
 * Applications:
 * 1. Sorted stream of data with key-value pairs
 * 2. Doubly ended priority queue with key-value pairs
 */

/*
 * Self-balancing BST
 * The key point regarding the need for self-balancing is: a same set of keys can result in
 * different BSTs or different height of BSTs depending on the order of insertion. One such
 * case occurs one all the keys are inserted in the increasing order, resulting in a
 * skewed BST.
 *
 * If we know all the keys in advance, we can create a balanced BST by sorting the keys in
 * increasing order, then picking the middle element as root, the left elements go to the
 * left subtree and right elements to the right. Repeat the same for the left and right
 * parts.
 *
 * For random insertion/deletion, we need to do extra work to make tree balanced.
 *
 * Two main types of self-balancing trees
 * 1. AVL Tree (strict balancing)
 * 2. Red-Black (loose balancing => less restructuring, more commonly used)
 *
 * AVL Tree:
 * 1. It is a BST (for every node, left subtree is smaller and right greater)
 * 2. It is balanced. For every node, the difference between left and right heights
 *    doesn't exceed 1. This difference is called balance factor
 *    balance_factor = abs(lh - rh)
 *
 *	Insert in AVL BST:
 *	* Perform a normal BST insert.
 *	* Traverse all the ancestors of the newly inserted node (which must be a leaf) from
 *	  the node to the root.
 *	* If we find an unbalanced node U, check for any of the below cases:
 *	  C is the child of the current unbalanced node and G is the grand-child of the U
 *	  1. left-left  => single rotation
 *	  2. right-right => single rotation
 *	  3. left-right => double rotation
 *	  4. right-left => double rotation
 *
 *	  left-left;
 *	  Both C and G are to in the left subtree of U. C becomes left of P. U becomes right child of C
 *
 *	  Right rotate U
 *	     U         ->         C
 *      C                   G   U
 *     G
 *
 *	  right-right:
 *	  U            ->         C
 *	   C                    U   G
 *	    G
 *
 *    left rotate U
 *
 *	  left-right:
 *	     U         ->         U        ->      G
 *	   C                    G                C   U
 *	     G                C
 *
 *	  left rotate C then right rotate U
 *
 *	  right-left:
 *	  U            ->     U            ->      G
 *	     C                  G                U   C
 *	  G                       C
 *
 *    right rotate C, then left rotate U
 *
 *	  In case of insertion, stop after balancing the first unbalanced node.
 *	  It is not the case with delete, where we have to keep traversing event
 *	  after fixing the first unbalanced node encountered.
 */

 /*
  * Red-Black tree rules:
  * 1. Every node has a color either red or black.
  * 2. The root of tree is always black.
  * 3. There are no two adjacent red nodes (A red node cannot have a red parent or red child).
  * 4. Every path from a node (including root) to any of its descendant NULL node has the same number of black nodes.
  */

class BST {
protected:
	std::shared_ptr<TreeNode<int>> root{nullptr};
public:
	BST() = default;
	virtual void insert(int n);
	virtual void remove(int n);
	virtual void insertIter(int n);
	bool search(int n);
	bool searchIter(int n);
	std::shared_ptr<TreeNode<int>> getRoot();
	std::shared_ptr<TreeNode<int>> ceil(int n);
	std::shared_ptr<TreeNode<int>> floor(int n);
};

class AVL: public BST {
private:
	std::shared_ptr<TreeNode<int>> insertHelper(
			std::shared_ptr<TreeNode<int>> root, int val);

	std::shared_ptr<TreeNode<int>> balance(std::shared_ptr<TreeNode<int>> root);
public:
	AVL() = default;
	virtual void insert(int n) override;
	virtual void remove(int n) override;
};

// return an array which contains the next greater items in the array to the left
std::vector<int> ceilingOnLeftSide(std::vector<int> input);
// return true if the tree follows BSTs properties
bool isBST(std::shared_ptr<TreeNode<int>> root);
// Time O(n), space O(n)
bool BSTPairWithSumExists(std::shared_ptr<TreeNode<int>> root, int sum);
std::vector<int> BinaryTreeVerticalSum(std::shared_ptr<TreeNode<int>> root);
std::vector<std::vector<int>> BinaryTreeVerticalTraversal(
		std::shared_ptr<TreeNode<int>> root);
std::vector<int> BinaryTreeTopView(std::shared_ptr<TreeNode<int>> root);
std::vector<int> BinaryTreeBottomView(std::shared_ptr<TreeNode<int>> root);

std::shared_ptr<TreeNode<int>> rotateLeft(std::shared_ptr<TreeNode<int>> curr,
		std::shared_ptr<TreeNode<int>> right);

std::shared_ptr<TreeNode<int>> rotateRight(std::shared_ptr<TreeNode<int>> curr,
		std::shared_ptr<TreeNode<int>> left);

// Time O(n), space O(1)
void fixBSTWithTwoNodesSwapped(std::shared_ptr<TreeNode<int>> root);

std::shared_ptr<TreeNode<int>> kthSmallestElement(std::shared_ptr<TreeNode<int>> root, int k);

#endif /* BINARY_SEARCH_TREE_H_ */
