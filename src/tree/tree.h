/*
 * tree.h
 *
 *  Created on: 25 Apr 2021
 *      Author: ykhan
 */

#ifndef TREE_TREE_H_
#define TREE_TREE_H_

#include <stdexcept>
#include <vector>
#include <map>
#include <deque>
#include <unordered_map>
#include <unordered_set>

/*
 *  Tree datastructure is used to organize data in a hierarchical manner
 *
 *  Terminology:
 *  Node
 *  Root
 *  Leaf: has no children. Node with degree 0
 *  Child
 *  Parent
 *  Subtree: left subtree/right subtree when the left/right child is a tree itself
 *  Descendants (of a node): all nodes that lie in a subtree with the node as root node
 *  Ancestors
 *  Degree of a node: Number of children a node has
 *  Internal Nodes: non-leaf nodes are called internal nodes
 *
 *  Applications:
 *
 *  1. To represent hierarchical data
 *     *  Organization structure
 *     *  Folder structure
 *     *  XML/HTML content (DOM and JSON Objects)
 *     *  In OOP (inheritance)
 *  2. Binary Search Trees O(logn) search
 *  3. Binary Heap (used to represent priority queue)
 *  4. B and B+ trees in DBMS (indexing)
 *  5. Spanning and shortest path trees in computer networks. Spanning trees are used
 *  by bridges to forward packets while shortest path trees are used by routers to route
 *  packets. Every router considers itself as the root of the tree and tries to find the
 *  shortest path to any other node.
 *  6. Parse tree, expression tree in compilers
 *  7. Trie: use to represent dictionaries and support prefix search
 *  8. Suffix tree: do fast searches in a string. You want to search different patterns in
 *  a big piece of text. Preprocess the text and create a suffix tree out of it. Then patterns
 *  can be searched efficiently. The time taken by search is proportional to the length of the
 *  pattern and not the whole text.
 *  9. Binary Index tree: used for range query searches
 *  10. Segment tree: similar to Binary Indexed tree.
 *
 *  Binary Tree:
 *  Nodes have max degree 2 i.e. each node can have 0, 1 or 2 child nodes.
 *
 */

#include <memory>
#include <functional>
#include <optional>
#include <stack> // for depth-first
#include <queue> // for breadth-first
#include <vector>
#include <iostream>
#include <cmath>

template <typename T>
class TreeNode {
	template <typename T2>
	friend std::ostream& operator<<(std::ostream& os, const TreeNode<T2>& node);
public:
	T key; //
	std::shared_ptr<TreeNode> left{nullptr};
	std::shared_ptr<TreeNode> right{nullptr};
	int lowerNodes{0};

	TreeNode() = default;
	TreeNode(const T& _key) :
			key{_key} {
	}

	bool operator<(const TreeNode& rhs) const {
		return this->key < rhs.key;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const TreeNode<T>& node) {
	os << node.key;
	return os;
}

/*
 * Two types of tree traversals possible
 * * Breadth-first (or level order)
 * * Depth-first
 *   * Inorder
 *   * PreOrder
 *   * PostOrder
 *
 *   Depth-first:
 *   Consider a tree consiting of root, left-subtree and right subtree
 *   Then depth tree traversal consists of three steps
 *   * Processing the root
 *   * Process the left subtree recursively
 *   * Process the right subtree recursively
 *
 *   The different order of the above three steps results in different traversals (3! total)
 *   Out of these 3! traversals, the inorder, preorder and postorder are most popular
 *   In all these three traversal, left-subtree is processed first i.e. the below orders
 *   left - root - right (Inorder)
 *   left - right - root (Postorder)
 *   root - left - right (PreOrder)
 */
template <typename T>
void breadthFirstTraversal(std::shared_ptr<TreeNode<T>> root,
		std::function<void(TreeNode<T>&)> fn) {
	if (!root)
		return;

	std::queue<TreeNode<T>> q;

	q.push(*root);

	while (!q.empty()) {
		auto p = q.front();
		q.pop();

		if (p.left)
			q.push(*(p.left));

		if (p.right)
			q.push(*(p.right));

		fn(p);
	}
}

// Time O(n), space O(n) -> for queue (ideally space is O(width-of-tree)
template <typename T, typename F>
void breadthFirstTraversal(std::shared_ptr<TreeNode<T>> root, F fn) {
	auto f = std::function<void(TreeNode<T>&)>(fn);
	breadthFirstTraversal(root, f);
}

template <typename T>
void levelOrderTraversalLineByLine(std::shared_ptr<TreeNode<T>> root) {
	std::queue<std::shared_ptr<TreeNode<T>>> q;

	q.push(root);
	// mark the end of this level
	q.push(nullptr);

	while (q.size() > 1) {
		auto p = q.front();
		q.pop();
		// level end marker
		if (!p) {
			q.push(nullptr);
			std::cout << std::endl;
			continue;
		}

		std::cout << *p << " -> ";

		if (p->left)
			q.push(p->left);

		if (p->right)
			q.push(p->right);
	}
}

// left - root - right
// Time O(n) space O(h) h -> height of tree (at most function call frames present)
template <typename T>
void inOrderTraversal(std::shared_ptr<TreeNode<T>> root,
		std::function<void(const TreeNode<T>&)> fn) {
	if (!root)
		return;

	// check if left subtree exists
	//if (root->left)
	inOrderTraversal(root->left, fn);

	fn(*root);

	//if (root->right)
	inOrderTraversal(root->right, fn);
}

// this aids in template type deduction when lambdas are used
// lamdas are unnamed function objects and are not converted to std::function
// during template argument deduction thus failing the automatic template
// argument deduction to std::function type
template <typename T, typename F>
void inOrderTraversal(std::shared_ptr<TreeNode<T>> root, F fn) {
	// explicitly convert to std::function and make sure the Callable
	// has the required signature
	std::function f = std::forward<F>(fn); // copy initialization
	inOrderTraversal(root, f);
}

// root - left- right
template <typename T>
void preOrderTraversal(std::shared_ptr<TreeNode<T>> root,
		std::function<void(const TreeNode<T>&)> fn) {
	if (!root)
		return;

	fn(*root);
	// check if left subtree exists
	//if (root->left)
	preOrderTraversal(root->left, fn);

	//if (root->right)
	preOrderTraversal(root->right, fn);
}

// explcitly converted to std::function
// Time O(n), space O(n)
template <typename T>
void preOrderTraversalIterative(std::shared_ptr<TreeNode<T>> root,
		std::function<void(const TreeNode<T>&)> fn) {
	// root -> left -> (left -> right) -> right
	std::stack<std::shared_ptr<TreeNode<T>>> s; // stack to keep track

	s.push(root);

	while (s.size()) {
		auto top = s.top();
		// remove
		s.pop();

		auto left = top->left;
		auto right = top->right;

		fn(*top);

		if (right)
			s.push(right);

		if (left)
			s.push(left);
	}
}

// receive any type of function object F
// Time O(n), space O(n)
template <typename T, typename F>
void preOrderTraversalIterative(std::shared_ptr<TreeNode<T>> root, F fn) {
	// explcitly converted to std::function
	std::function f = std::forward<F>(fn);
	preOrderTraversalIterative(root, f);
}

template <typename T, typename F>
void preOrderTraversal(std::shared_ptr<TreeNode<T>> root, F&& fn) {
	std::function f = std::forward<F>(fn); // copy initialization
	preOrderTraversal(root, f);
}

// left- right - root
template <typename T>
void postOrderTraversal(std::shared_ptr<TreeNode<T>> root,
		std::function<void(const TreeNode<T>&)> fn) {
	if (!root)
		return;

	// check if left subtree exists
	if (root->left)
		postOrderTraversal(root->left, fn);

	if (root->right)
		postOrderTraversal(root->right, fn);

	fn(*root);
}

template <typename T, typename F>
void postOrderTraversal(std::shared_ptr<TreeNode<T>> root, F fn) {
	std::function f = std::forward<F>(fn); // copy initialization
	postOrderTraversal(root, f);
}

/*
 * Height of Binary Tree is the number of nodes between the longest path from root
 * to leaf node(including the root and leaf node). Another convention is height
 * is the number of edges between root and leaf nodes. Confirm the convention
 * before solving problems involving tree height
 */

// Time O(1), space O(h)
template <typename T>
inline int heightOfTree(std::shared_ptr<TreeNode<T> > root) {
	// idea recursively traverse the tree depth wise till leaf-nodes are encountered
	if (!root) {
		return 0;
	}

	return 1 + std::max(heightOfTree(root->left), heightOfTree(root->right));
}

/*
 * Nodes at distance k from the root are basically the nodes at
 * (k+1)th level of the Binary Tree.
 */

template <typename T>
void nodesAtDistanceHelper(std::shared_ptr<TreeNode<T>> root, int distance,
		std::vector<TreeNode<T>>& nodes) {

	if (!root)
		return;

	if (distance == 0)
		nodes.emplace_back(*root);

	nodesAtDistanceHelper(root->left, distance - 1, nodes);
	nodesAtDistanceHelper(root->right, distance - 1, nodes);
}

// Time O(n) Space O(h) -> worst cast distance = height of tree
template <typename T>
std::vector<TreeNode<T>> nodesAtDistance(std::shared_ptr<TreeNode<T>> root,
		int distance) {
	std::vector<TreeNode<T>> result;

	nodesAtDistanceHelper(root, distance, result);

	return result;
}

// time O(n), space O(h) h: height of tree
template <typename T>
int sizeOfTree(std::shared_ptr<TreeNode<T>> root) {
	if (!root)
		return 0;

	return 1 + sizeOfTree(root->left) + sizeOfTree(root->right);
}

// time O(n) space O(h)
// a queue based (level order) solution would have time O(n) and space O(width)
// a queue based solution also won't have recursion overhead
template <typename T>
T maxBinaryTree(std::shared_ptr<TreeNode<T>> root) {

	// maxLeft maxRight root
	if (!root)
		return T{}; // default value

	T maxLeft = maxBinaryTree(root->left);
	T maxRight = maxBinaryTree(root->right);

	T maxSubtree = std::max(maxLeft, maxRight);

	return std::max(maxSubtree, root->key);
}

template <typename T>
void getLeft(std::shared_ptr<TreeNode<T>> root, int level, int& count,
		std::vector<TreeNode<T>>& result) {
	if (!root)
		return;

	if (count < level) {
		result.push_back(*root);
		count++;
	}

	getLeft(root->left, level + 1, count, result);
	getLeft(root->right, level + 1, count, result);
}

// get left view of a binary tree.
// left view consists of left most values at each level
// it is preorder traversal
// recursive time O(n), space O(h)
template <typename T>
std::vector<TreeNode<T>> getLeftView(std::shared_ptr<TreeNode<T>> root) {
	std::vector<TreeNode<T>> result;
	int count = 0;
	getLeft(root, 1, count, result);

	return result;
}

// time O(n), space O(w)
template <typename T>
std::vector<TreeNode<T>> getLeftViewIter(std::shared_ptr<TreeNode<T>> root) {
	std::vector<TreeNode<T>> result;
	std::queue<TreeNode<T>> q;

	q.push(*root);

	while (!q.empty()) {
		int levelSize = q.size();

		for (int i = 0; i < levelSize; i++) {
			auto curr = q.front();
			q.pop();

			if (i == 0) {
				result.push_back(curr);
			}

			if (curr.left) {
				q.push(*curr.left);
			}

			if (curr.right) {
				q.push(*curr.right);
			}
		}
	}

	return result;
}

// Children Sum property CSP
// A binary tree is set to hold a CSP if
// 1. It contains zero nodes
// 2. It contains only single node (root node)
// 3. If the sum of left child and right child is equal to the value of root node
// If any of the subtree doesn't hold CSP, the whole tree doesn't hold CSP
// time O(n) space O(h)
template <typename T>
bool childrenSumProperty(std::shared_ptr<TreeNode<T>> root) {
	bool result;

	// if root is null return true
	if (!root)
		return true;

	// if both left and right children are present
	if (root->left && root->right)
		result = root->left->key + root->right->key == root->key;
	// if only left child is present
	else if (root->left)
		result = root->left->key == root->key;
	// if only right child is present
	else if (root->right)
		result = root->right->key == root->key;
	// if not children
	else
		return true;

	return result && childrenSumProperty(root->left)
			&& childrenSumProperty(root->right);
}

// return -1 if the tree is not balanced, otherwise return tree height
template <typename T>
int isTreeBalancedHelper(std::shared_ptr<TreeNode<T>> root) {
	if (!root)
		return 0;

	auto leftHeight = isTreeBalancedHelper(root->left);
	// -1 indicates the subtree itself is not balanced
	// no need to check further
	if (leftHeight < 0)
		return -1;

	auto rightHeight = isTreeBalancedHelper(root->right);
	if (rightHeight < 0)
		return -1;

	int heightDiff = abs(leftHeight - rightHeight);

	if (heightDiff > 1)
		return -1;

	return std::max(leftHeight, rightHeight) + 1;
}

// return whether the binary tree is balanced or not
// a tree is balanced if the difference in height of left and right subtrees is <= 1
// time O(n), space O(h)
template <typename T>
bool isTreeBalanced(std::shared_ptr<TreeNode<T>> root) {

	// naive time O(n^2)
//	if (!root)
//		return true;
//
//	int leftHeight = heightOfTree(root->left);
//	int rightHeight = heightOfTree(root->right);
//
//	int heightDiff = abs(rightHeight - leftHeight);
//
//	auto leftBalanced = isTreeBalanced(root->left);
//	auto rightBalanced = isTreeBalanced(root->right);
//
//	return  (heightDiff <= 1) && leftBalanced && rightBalanced;

	// instead of calculating height for each node. Keep track
	// of max height difference

	return isTreeBalancedHelper(root) >= 0 ? true : false;
}

// Find the maximum width of a binary tree
// Time O(n) space O(w)
template <typename T>
int maxTreeWidth(std::shared_ptr<TreeNode<T>> root) {
	// put maxWidthTreeeach level in a queue, the size of the queue is the width
	// track maximum queue size
	std::queue<std::shared_ptr<TreeNode<T>>> q;
	int maxWidth = 0;
	q.push(root);
	int count = 0;

	while (!q.empty()) {
		count = q.size();
		maxWidth = std::max(count, maxWidth);

		for (int i = 0; i < count; i++) {
			auto r = q.front();
			q.pop();

			if (r->left)
				q.push(r->left);

			if (r->right)
				q.push(r->right);
		}
	}

	return maxWidth;
}

template <typename T>
void printBinaryDLL(std::shared_ptr<TreeNode<T>> root) {
	using namespace std;

	std::shared_ptr<TreeNode<T>> curr = root;
	std::shared_ptr<TreeNode<T>> prev;

	cout << "Forward dir: ";

	while (curr) {
		cout << *curr << " -> ";
		prev = curr;
		curr = curr->right;
	}
	cout << endl;

	cout << "Reverse dir: ";
	curr = prev;
	while (curr) {
		cout << *curr << " -> ";
		curr = curr->left;
	}
	cout << endl;
}

template <typename T>
std::shared_ptr<TreeNode<T>> convertBinaryToDLLHelper(
		std::shared_ptr<TreeNode<T>> curr, std::shared_ptr<TreeNode<T>>& prev) {

	std::shared_ptr<TreeNode<T>> head{nullptr};

	if (!curr)
		return head;

	// the head of the DLL is either root or towards its left.
	// It cannot be in the right subtree
	head = convertBinaryToDLLHelper(curr->left, prev);

	// if head still not found
	if (!prev) {
		head = curr;
	} else {
		prev->right = curr;
		curr->left = prev;
	}

	prev = curr;

	convertBinaryToDLLHelper(curr->right, prev);

	return head;
}

// convert a binary tree to a doubly linked list
// next => right
// prev => left
// Note: inorder conversion
// Time O(n), space O(h)
template <typename T>
std::shared_ptr<TreeNode<T>> convertBinaryToDLL(
		std::shared_ptr<TreeNode<T>> root) {
	// left - root - right
	std::shared_ptr<TreeNode<T>> prev{nullptr};

	return convertBinaryToDLLHelper(root, prev);
}

template <typename T>
static std::shared_ptr<TreeNode<T>> createTreeHelper(
		std::unordered_map<T, int> indexMap, std::vector<T> preorder,
		int startIdx, int endIdx, int& preIdx) {

	if (endIdx < startIdx)
		return {nullptr};

	// create root from the item pointed to by the preIdx index, increment preIdx
	// preIdx points to the next root index from the preorder array
	// a preorder array: root -> root of left subtree -> root of left-left subtree
	// -> root of left-right subtree -> root of right subtree -> root of right-left subtree
	// -> root of right-right subtree....
	std::shared_ptr<TreeNode<T>> root = std::make_shared<TreeNode<T>>(
			preorder[preIdx++]);

	// an inorder traversal is left - root - right
	// so to find the left vs right subtree, we need to make use of the inorder traversal
	// one we select the current root from preorder array

//	int inIdx = startIdx;

//	for (int i = startIdx; i <= endIdx; i++) {
//		if (inorder[i] == preorder[preIdx - 1]) {
//			inIdx = i;
//			break;
//		}
//	}

	int inIdx = indexMap[preorder[preIdx - 1]];

	int leftSubtreeStart = startIdx;
	int leftSubtreeEnd = inIdx - 1;
	int rightSubtreeStart = inIdx + 1;
	int rightSubtreeEnd = endIdx;

	root->left = createTreeHelper(indexMap, preorder, leftSubtreeStart,
			leftSubtreeEnd, preIdx);
	root->right = createTreeHelper(indexMap, preorder, rightSubtreeStart,
			rightSubtreeEnd, preIdx);

	return root;
}

// create a binary tree from inorder and preorder traversal array
// inorder left - root - right
// preorder root - left - right
// cannot recreate with just one traversal, need at least 2
// consider the case of inorder traversal
// the left after root could be the immediate child of root
// or could be the left of the left subtree
// Time O(n), space O(n)
template <typename T>
std::shared_ptr<TreeNode<T>> createTree(std::vector<T> inorder,
		std::vector<T> preorder) {
	int size_i = inorder.size();
	int size_p = preorder.size();
	int preIdx = 0;

	if (size_i != size_p) {
		throw std::runtime_error(
				"Lengths of inorder and preorder traversal arrays must be same!");
	}

	std::unordered_map<T, int> indexMap;

	for (int i = 0; i < size_i; i++) {
		indexMap.insert({inorder[i], i});
	}

	return createTreeHelper(indexMap, preorder, 0, size_i - 1, preIdx);
}

// spiral traversal is level-by-level traversal where
// after traversing root, it traverses a level right to left
// and then next one, from left to right
// maybe use deque ?
template <typename T>
void spiralTraversal(std::shared_ptr<TreeNode<T>> root,
		std::function<void(const T& n)> cb) {
	std::deque<std::shared_ptr<TreeNode<T>>> dq;

	bool direction = true; // left to right

	dq.push_back(root);
	dq.push_back(nullptr);

	std::shared_ptr<TreeNode<T>> p;

	while (dq.size() > 1) {
		if (direction) {
			p = dq.front();
			dq.pop_front();
		} else {
			p = dq.back();
			dq.pop_back();
		}

		if (!p) {
			if (direction)
				dq.push_front(nullptr);
			else
				dq.push_back(nullptr);

			direction = !direction;

			continue;
		}

		cb(p->key);

		if (direction) {
			if (p->left)
				dq.push_back(p->left);
			if (p->right)
				dq.push_back(p->right);
		} else {
			if (p->right)
				dq.push_front(p->right);
			if (p->left)
				dq.push_front(p->left);
		}
	}
}

template <typename T, typename F>
void spiralTraversal(std::shared_ptr<TreeNode<T>> root, F f) {
	std::function<void(const T& n)> cb = std::forward<F>(f);
	spiralTraversal(root, cb);
}

// return height of the tree, also sets if the current root makes the largest diameter
template <typename T>
int diameterOfTreeHelper(std::shared_ptr<TreeNode<T>> root, int& maxDiameter) {

	if (!root)
		return 0;

	int leftHeight = diameterOfTreeHelper(root->left, maxDiameter);
	int rightHeight = diameterOfTreeHelper(root->right, maxDiameter);

	int height = 1 + std::max(leftHeight, rightHeight);
	int diameter = leftHeight + rightHeight + 1;
	maxDiameter = std::max(maxDiameter, diameter);

	return height;
}

// Time O(n), space O(1)
template <typename T>
int diameterOfTree(std::shared_ptr<TreeNode<T>> root) {
	int maxDiameter = 0;

	diameterOfTreeHelper(root, maxDiameter);

	return maxDiameter;
}

template <typename T>
bool findPath(std::shared_ptr<TreeNode<T>> root, std::vector<T>& path, T n) {
	bool result;

	if (!root) {
		return false;
	}

	path.push_back((*root).key);

	if ((*root).key == n) {
		return true;
	}

	if (findPath(root->left, path, n) || findPath(root->right, path, n))
		return true;

	// not found in this tree or any of its subtrees, remove from path
	path.pop_back();

	return false;
}

// Time O(n), space O(n)
template <typename T>
T lowestCommonAncestor(std::shared_ptr<TreeNode<T>> root, T n1, T n2) {
	std::vector<T> path1;
	std::vector<T> path2;

	if (!findPath(root, path1, n1) || !findPath(root, path2, n2))
		return {};

	T result{};
	int size1 = path1.size();
	int size2 = path2.size();

	int size = std::min(size1, size2);

	for (int i = 0; i < size; i++) {
		if (path1[i] != path2[i]) {
			break;
		}

		result = path1[i];
	}

	return result;
}

// Time O(n), space O(1)
template <typename T>
std::shared_ptr<TreeNode<T>> lowestCommonAncestorBetter(
		std::shared_ptr<TreeNode<T>> root, T n1, T n2) {
	/*
	 * Assumption: both n1 and n2 exist in tree
	 * Cases:
	 * root's key is either n1 or n2: return root
	 */

	if (!root)
		return {nullptr};

	if (root->key == n1 || root->key == n2) {
		return root;
	}

	// check in left subtree
	auto left_lca = lowestCommonAncestorBetter(root->left, n1, n2);
	// check in right
	auto right_lca = lowestCommonAncestorBetter(root->right, n1, n2);

	// case: one of the node exists in left subtree while other in right subtree
	if (left_lca && right_lca) {
		return root;
	} else if (left_lca) {
		// both n1 and n2 exists in left subtree (valid if assumption that both n1 and n2 exist is true)
		return left_lca;
	} else if (right_lca) {
		// both n1 and n2 exists in right subtree (valid if assumption that both n1 and n2 exist is true)
		return right_lca;
	}

	return {nullptr};
}

/*
 *  Complete binary tree:
 *  All the levels are filled except the last one.
 *  last one is filled left to right
 */
template <typename T>
int countNodesCompleteTree(std::shared_ptr<TreeNode<T>> root) {
	if (!root)
		return 0;
}

// Count Nodes in a binary tree
// time O(n), space O(1)
template <typename T>
int countNodes(std::shared_ptr<TreeNode<T>> root) {
	if (!root)
		return 0;

	return countNodes(root->left) + countNodes(root->right) + 1;
}

template <typename T>
void serializeTreeHelper(std::shared_ptr<TreeNode<T>> root,
		std::vector<T>& out) {
	// using root - left - right traversal (preorder)
	if (!root) {
		// push default value for null node
		out.push_back(T{});
		return;
	}

	out.push_back(root->key);
	serializeTreeHelper(root->left, out);
	serializeTreeHelper(root->right, out);
}

// Time O(n), space O(n)
// for n tree nodes, we need n + 1 nodes to represent null nodes
// therefore total space required for n nodes is n + (n + 1) = 2n + 1 ~ O(n)

template <typename T>
std::vector<T> serializeTree(std::shared_ptr<TreeNode<T>> root) {
	std::vector<T> result;
	serializeTreeHelper(root, result);

	return result;
}

template <typename T>
std::shared_ptr<TreeNode<T>> deserializeTreeHelper(std::vector<T> vec, int& i) {
	if (i == vec.size())
		return {nullptr};

	if (vec[i] == T{}) {
		i++;
		return {nullptr};
	}

	std::shared_ptr<TreeNode<T>> root = std::make_shared<TreeNode<T>>(vec[i]);
	i++;
	root->left = deserializeTreeHelper(vec, i);
	root->right = deserializeTreeHelper(vec, i);

	return root;
}

// Time O(n), space O(n)
template <typename T>
std::shared_ptr<TreeNode<T>> deserializeTree(std::vector<T> vec) {
	int index = 0;
	std::shared_ptr<TreeNode<T>> root = deserializeTreeHelper(vec, index);
	return root;
}

template <typename T>
void inOrderTraversalIterHelper(std::shared_ptr<TreeNode<T>> root,
		std::vector<T>& out) {
	// left - root - right
	std::shared_ptr<TreeNode<T>> curr = root;
	std::stack<std::shared_ptr<TreeNode<T>>> s;

	while (curr || s.size() > 0) {
		while (curr) {
			s.push(curr);
			curr = curr->left;
		}

		curr = s.top();
		s.pop();
		out.push_back(curr->key);

		curr = curr->right;
	}
}

// time O(n), space O(h)
template <typename T>
std::vector<T> inOrderTraversalIter(std::shared_ptr<TreeNode<T>> root) {
	std::vector<T> result;

	inOrderTraversalIterHelper(root, result);

	return result;
}

template <typename T>
std::pair<int, int> burnTreeFromLeafHelper(std::shared_ptr<TreeNode<T>> root,
		T leaf, int& maxDistance) {
	// first see if the leaf occurs in left subtree or right subtree
	// write a function that return height as well as distance to the leaf exists in that tree
	if (!root)
		return {0, -1};

	if (root->key == leaf) {
		return {1, 0}; // height, distance
	}

	auto[lh, ld] = burnTreeFromLeafHelper(root->left, leaf, maxDistance);
	auto[rh, rd] = burnTreeFromLeafHelper(root->right, leaf, maxDistance);

	int _lh = lh;
	int _ld = ld;
	int _rh = rh;
	int _rd = rd;

	int distance = -1;

	// leaf exists in left tree
	if (ld != -1) {
		distance = ld + 1;
		maxDistance = std::max(maxDistance, distance + rh);
	}

	if (rd != -1) {
		distance = rd + 1;
		maxDistance = std::max(maxDistance, distance + lh);
	}

	return {std::max(rh, lh) + 1, distance};
}

// Find the time it takes to burn the whole tree, starting from the leaf
// the leaf is burned at time T = 0
// At each time step, a node's adjacent nodes are burnt
// In other words, to find the burn time, find the farthest
// node through the leaf's ancestor
// farthest node = height of root node + distance of root node from leaf
template <typename T>
int burnTreeFromLeaf(std::shared_ptr<TreeNode<T>> root, T leaf) {
	int result = -1;

	(void) burnTreeFromLeafHelper(root, leaf, result);

	return result;
}

#endif /* TREE_TREE_H_ */
