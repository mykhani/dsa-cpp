/*
 * binary-search-tree.cpp
 *
 *  Created on: 16 Jun 2021
 *      Author: ykhan
 */
#include "binary-search-tree.h"
#include <unordered_set>
#include <stack>
#include <map>
#include <queue>
#include <climits>

// find the null node and create a new node at its place
static std::shared_ptr<TreeNode<int>> insertHelper(
		std::shared_ptr<TreeNode<int>> root, int n) {
	if (!root) {
		return std::make_shared<TreeNode<int>>(n);
	}

	if (n < root->key) {
		root->left = insertHelper(root->left, n);
		root->lowerNodes++; // since we add node to its left, increment its lower nodes count
	} else if (n > root->key) {
		root->right = insertHelper(root->right, n);
	}

	return root;
}

void BST::insert(int n) {
	root = insertHelper(root, n);
}

void BST::insertIter(int n) {
	if (!root) {
		root = std::make_shared<TreeNode<int>>(n);
		return;
	}

	std::shared_ptr<TreeNode<int>> curr = root;
	std::shared_ptr<TreeNode<int>> prev{nullptr};

	while (curr) {
		if (n < curr->key) {
			prev = curr;
			curr = curr->left;
		} else if (n > curr->key) {
			prev = curr;
			curr = curr->right;
		}
	}

	if (n < prev->key) {
		prev->left = std::make_shared<TreeNode<int>>(n);
	} else if (n > prev->key) {
		prev->right = std::make_shared<TreeNode<int>>(n);
	}
}

static std::shared_ptr<TreeNode<int>> findMinimum(
		std::shared_ptr<TreeNode<int>> root) {

	if (!root->left) {
		return root;
	}

	return findMinimum(root->left);
}

std::shared_ptr<TreeNode<int>> removeHelper(std::shared_ptr<TreeNode<int>> root,
		int n) {
	if (!root)
		return {nullptr};

	if (root->key < n) {
		root->right = removeHelper(root->right, n);
	} else if (root->key > n) {
		root->left = removeHelper(root->left, n);
	} else {
		// 1. Node is leaf node
		if (!root->left && !root->right) {
			return nullptr;
			// 2. Node has only left child
		} else if (root->left && !root->right) {
			return root->left;
			// 3. Node has only right child
		} else if (root->right && !root->left) {
			return root->right;
			// 4. Node has both left and right child
		} else {
			std::shared_ptr<TreeNode<int>> min = findMinimum(root->right);
			std::swap(root->key, min->key);
			root->right = removeHelper(root->right, n);
		}
	}

	return root;
}

// Time O(h), space O(h)
void BST::remove(int n) {
	/* find the node
	 * cases:
	 * 1. Node is leaf node, set parent's left or right to nullptr
	 * 2. Node has only left child
	 * 		set parent's left to the node's left
	 * 3. Node has has only right child
	 *      set parent's right to the node's right
	 * 4. Node has both left and right childs
	 *      Need to find the node that can replace the removed node, smallest node in the right tree
	 *
	 */
	root = removeHelper(root, n);
}

std::shared_ptr<TreeNode<int>> floorHelper(std::shared_ptr<TreeNode<int>> root,
		std::shared_ptr<TreeNode<int>>& closest, int n) {
	if (!root)
		return {nullptr};

	if (root->key == n) {
		return root;
	}

	if (root->key < n) {
		// possible floor
		closest = root;
		// see if a higher value exists that is close to n
		// since it should be higher than the current, search
		// in the right subtree
		return floorHelper(root->right, closest, n);
	} else if (root->key > n) {
		return floorHelper(root->left, closest, n);
	}
}

static std::shared_ptr<TreeNode<int>> ceilHelper(
		std::shared_ptr<TreeNode<int>> root, int n) {
	std::shared_ptr<TreeNode<int>> result{nullptr};

	while (root) {
		if (root->key == n) {
			result = root;
			break;
		} else if (root->key > n) {
			result = root;
			// see if a smaller value exists that is close to n
			// since it should be lower than the current, search
			// in the left subtree
			root = root->left;
		} else if (root->key < n) {
			root = root->right;
		}
	}

	return result;
}

// Find a value equal to or smallest greater than n
// time O(h), space O(1)
std::shared_ptr<TreeNode<int> > BST::ceil(int n) {
	return ceilHelper(root, n);
}

// return the node with the value equal to n or the largest value smaller than n
// Time O(h), space O(h) (O(1) with iterative solution)
std::shared_ptr<TreeNode<int>> BST::floor(int n) {
	// do the inorder traversal, if value of root becomes greater than or equal to n, return
	std::shared_ptr<TreeNode<int>> closest{nullptr};
	auto result = floorHelper(root, closest, n);

	return result ? result : closest;
}

std::shared_ptr<TreeNode<int> > BST::getRoot() {
	return root;
}

static bool searchHelper(std::shared_ptr<TreeNode<int>> root, int n) {
	if (!root)
		return false;

	if (root->key == n) {
		return true;
	} else if (n < root->key) {
		return searchHelper(root->left, n);
	} else if (n > root->key) {
		return searchHelper(root->right, n);
	}
}

// Time O(logn) space O(height)
bool BST::search(int n) {
	return searchHelper(root, n);
}

// Time O(logn) space O(1)
bool BST::searchIter(int n) {
	auto curr = root;

	while (curr) {
		if (curr->key == n)
			return true;
		else if (n < curr->key) {
			curr = curr->left;
		} else if (n > curr->key) {
			curr = curr->right;
		}
	}

	return false;
}

// Time, O(nlogn) space O(n)
std::vector<int> ceilingOnLeftSide(std::vector<int> input) {
	std::vector<int> result;
	std::set<int> s;

	// O(n)
	for (int i = 0; i < input.size(); i++) {
		auto it = s.lower_bound(input[i]); // O(logn)
		if (it != s.end()) {
			result.push_back(*it);
		} else {
			result.push_back(-1);
		}
		s.insert(input[i]);
	}

	return result;
}

// another method is to check if inorder traversal of tree is sorted in increasing order
static bool isBSTHelper(std::shared_ptr<TreeNode<int>> root, int min, int max) {
	if (!root) {
		return true;
	}

	if (root->key < min || root->key > max)
		return false;

	return isBSTHelper(root->left, min, root->key)
			&& isBSTHelper(root->right, root->key, max);
}

// time O(n), space O(h)
bool isBST(std::shared_ptr<TreeNode<int> > root) {
	return isBSTHelper(root, INT_MIN, INT_MAX);
}

static bool pairWithSumHelper(std::shared_ptr<TreeNode<int>> root,
		std::unordered_set<int>& s, int sum) {
	if (!root)
		return false;

	if (pairWithSumHelper(root->left, s, sum))
		return true;

	int diff = sum - root->key;
	if (s.find(diff) != s.end())
		return true;

	s.insert(root->key);

	return pairWithSumHelper(root->right, s, sum);
}

bool BSTPairWithSumExists(std::shared_ptr<TreeNode<int>> root, int sum) {
	/*
	 * Two approached
	 * 1. Traverse BST inorder and create an array
	 * 2. Find the pair using two-pointer method
	 * Time theta(n), space theta(n)
	 *
	 * Better:
	 * 1. Traverse BST inorder, for each current node find if previously traversed
	 * value exists that makes the sum in a hash table.
	 * 2. Put the current node in the hash table
	 * Time O(n), space O(n) // worst case, could be less if we find the pair eariler
	 */
	std::unordered_set<int> traversed;
	return pairWithSumHelper(root, traversed, sum);
}

static void verticalSumHelper(std::shared_ptr<TreeNode<int>> root,
		std::map<int, int>& m, int dist) {

	if (!root)
		return;

	// preorder traversal (can use any traversal)
	m[dist] += root->key; // O(logk) where k is number of entries in map
	verticalSumHelper(root->left, m, dist - 1);
	verticalSumHelper(root->right, m, dist + 1);
}

// Vertical sum is the sum of node that have the same horizontal distance from root which starts at 0
// Time O(nlogk) where k is number of entries in map (horizontal distances), space O(max(h,k))
std::vector<int> BinaryTreeVerticalSum(std::shared_ptr<TreeNode<int> > root) {
	std::map<int, int> m;
	std::vector<int> result;

	verticalSumHelper(root, m, 0);

	for (auto &[dist, sum] : m) {
		result.push_back(sum);
	}

	return result;
}

void verticalTraversalHelper(std::shared_ptr<TreeNode<int>> root,
		std::map<int, std::vector<int>>& m) {

	// do level order travesal so for two items on same vertical line, the left-most is printe
	// inorder traversal doesn't work in all cases

	std::queue<std::pair<std::shared_ptr<TreeNode<int>>, int>> q;
	q.push({root, 0});

	while (!q.empty()) {
		auto &[node, dist] = q.front();
		q.pop();

		m[dist].push_back(node->key);

		if (node->left)
			q.push({node->left, dist - 1});
		if (node->right)
			q.push({node->right, dist + 1});
	}
}

std::vector<std::vector<int> > BinaryTreeVerticalTraversal(
		std::shared_ptr<TreeNode<int> > root) {
	std::vector<std::vector<int>> result;
	std::map<int, std::vector<int>> m;

	verticalTraversalHelper(root, m);

	for (auto &[dist, vec] : m) {
		result.push_back(vec);
	}

	return result;
}

static void topViewHelper(std::shared_ptr<TreeNode<int>> root,
		std::vector<int>& out) {

	std::queue<std::pair<std::shared_ptr<TreeNode<int>>, int>> q;
	std::map<int, int> m;

	q.push({root, 0});

	while (!q.empty()) {
		auto &[node, dist] = q.front();
		q.pop();
		// insert the first item with this distance
		if (m.find(dist) == m.end()) {
			m[dist] = node->key;
		}
		if (node->left)
			q.push({node->left, dist - 1});
		if (node->right)
			q.push({node->right, dist + 1});
	}

	for (auto &[dist, val] : m) {
		out.push_back(val);
	}
}

std::vector<int> BinaryTreeTopView(std::shared_ptr<TreeNode<int> > root) {
	std::vector<int> result;
	topViewHelper(root, result);

	return result;
}

static void bottomViewHelper(std::shared_ptr<TreeNode<int>> root,
		std::vector<int>& out) {
	std::queue<std::pair<std::shared_ptr<TreeNode<int>>, int>> q;
	std::map<int, int> m;

	q.push({root, 0});

	while (!q.empty()) {
		auto &[node, dist] = q.front();
		q.pop();
		// insert the last item with this distance
		m[dist] = node->key;

		if (node->left)
			q.push({node->left, dist - 1});
		if (node->right)
			q.push({node->right, dist + 1});
	}

	for (auto &[dist, val] : m) {
		out.push_back(val);
	}
}

std::vector<int> BinaryTreeBottomView(std::shared_ptr<TreeNode<int> > root) {
	std::vector<int> result;
	bottomViewHelper(root, result);

	return result;
}

std::shared_ptr<TreeNode<int>> rotateLeft(std::shared_ptr<TreeNode<int>> curr,
		std::shared_ptr<TreeNode<int>> right) {
	curr->right = right->left;
	right->left = curr;

	return right;
}

std::shared_ptr<TreeNode<int>> rotateRight(std::shared_ptr<TreeNode<int>> curr,
		std::shared_ptr<TreeNode<int>> left) {
	curr->left = left->right;
	left->right = curr;

	return left;
}

void AVL::remove(int n) {
}

std::shared_ptr<TreeNode<int> > AVL::balance(
		std::shared_ptr<TreeNode<int> > root) {

	int lh = heightOfTree(root->left);
	int rh = heightOfTree(root->right);

	std::shared_ptr<TreeNode<int>> u, c, g;

	// left-left or left-right cases
	if (lh - rh > 1) {
		// left-left case
		u = root;
		c = root->left;

		if (heightOfTree(c->left) > heightOfTree(c->right)) {
			// left-left case
			return rotateRight(u, c);
		} else {
			// left-right case
			g = c->right;
			c = rotateLeft(c, g);
			return rotateRight(u, c);
		}
	} else if (rh - lh > 1) {
		// right-right case
		u = root;
		c = root->right;
		if (heightOfTree(c->right) > heightOfTree(c->left)) {
			// right-right case
			return rotateLeft(u, c);
		} else {
			// right-left case
			g = c->left;
			c = rotateRight(c, g);
			return rotateLeft(u, c);
		}
	}

	return root;
}

std::shared_ptr<TreeNode<int>> AVL::insertHelper(
		std::shared_ptr<TreeNode<int> > root, int val) {
	if (!root) {
		return std::make_shared<TreeNode<int>>(val);
	}

	if (val < root->key)
		root->left = insertHelper(root->left, val);

	if (val > root->key)
		root->right = insertHelper(root->right, val);

	// balance all the nodes encountered on the path (ancestors)
	// TODO: balance function finds the height of the ancestor nodes
	// There could be O(logn) ancestors.
	// Finding height is O(logn) operation
	// so looks like balance function has O(logn * logn)
	root = balance(root);

	return root;
}

void AVL::insert(int n) {
	root = this->insertHelper(root, n);
}

void fixBSTWithTwoNodesSwapped(
		std::shared_ptr<TreeNode<int> > root) {
	std::shared_ptr<TreeNode<int>> prev{nullptr};
	std::shared_ptr<TreeNode<int>> first{nullptr};
	std::shared_ptr<TreeNode<int>> second{nullptr};

	std::stack<std::shared_ptr<TreeNode<int>>> s;


	while (root || !s.empty()) {
		while (root) {
			s.push(root);
			root = root->left;
		}
		root = s.top();
		s.pop();

		if (prev && root->key < prev->key) {
			if (!first)
				first = prev;

			second = root;
		}

		prev = root;
		root = root->right;
	}

	std::swap(first->key, second->key);
}

std::shared_ptr<TreeNode<int>> kthSmallestElement(std::shared_ptr<TreeNode<int> > root, int k) {
	if (!root)
		return {nullptr};

	int n = 1 + root->lowerNodes; // root is nth lower node where n is 1 + nodes to root's left
	if (n == k)
		return root;

	// if cannot be found in the current tree, search for higher nodes
	if (k > n) {
		return kthSmallestElement(root->right, k - n);
	}

	return kthSmallestElement(root->left, k);
}
