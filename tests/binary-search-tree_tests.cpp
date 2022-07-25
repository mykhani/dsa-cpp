/*
 * binary-search-tree_tests.cpp
 *
 *  Created on: 16 Jul 2021
 *      Author: ykhan
 */

#include "../src/binary-search-tree/binary-search-tree.h"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(BinarySearchTree, BSTInsertTest) {
	BST bst;

	bst.insert(20);
	bst.insert(15);
	bst.insert(30);
	bst.insert(40);
	bst.insert(50);
	bst.insert(12);
	bst.insert(18);
	bst.insert(35);
	bst.insert(80);
	bst.insert(7);

	auto result = inOrderTraversalIter(bst.getRoot());
	vector<int> expected{7, 12, 15, 18, 20, 30, 35, 40, 50, 80};

	EXPECT_EQ(result == expected, true);
}

TEST(BinarySearchTree, BSTInsertIterativeTest) {
	BST bst;

	bst.insertIter(20);
	bst.insertIter(15);
	bst.insertIter(30);
	bst.insertIter(40);
	bst.insertIter(50);
	bst.insertIter(12);
	bst.insertIter(18);
	bst.insertIter(35);
	bst.insertIter(80);
	bst.insertIter(7);

	auto result = inOrderTraversalIter(bst.getRoot());
	vector<int> expected{7, 12, 15, 18, 20, 30, 35, 40, 50, 80};

	EXPECT_EQ(result == expected, true);
}

TEST(BinarySearchTree, BSTSearchTest) {
	BST bst;

	bst.insert(20);
	bst.insert(15);
	bst.insert(30);
	bst.insert(40);
	bst.insert(50);
	bst.insert(12);
	bst.insert(18);
	bst.insert(35);
	bst.insert(80);
	bst.insert(7);

	EXPECT_EQ(bst.search(6), false);
	EXPECT_EQ(bst.search(90), false);
	EXPECT_EQ(bst.search(40), true);
}

TEST(BinarySearchTree, BSTSearchIterativeTest) {
	BST bst;

	bst.insert(20);
	bst.insert(15);
	bst.insert(30);
	bst.insert(40);
	bst.insert(50);
	bst.insert(12);
	bst.insert(18);
	bst.insert(35);
	bst.insert(80);
	bst.insert(7);

	EXPECT_EQ(bst.searchIter(6), false);
	EXPECT_EQ(bst.searchIter(90), false);
	EXPECT_EQ(bst.searchIter(40), true);
}

TEST(BinarySearchTree, BSTRemoveTest) {
	BST bst;

	bst.insert(50);
	bst.insert(20);
	bst.insert(70);
	bst.insert(60);
	bst.insert(80);

	bst.remove(50);

	auto result = inOrderTraversalIter(bst.getRoot());
	vector<int> expected{20, 60, 70, 80};

	EXPECT_EQ(result == expected, true);
}

TEST(BinarySearchTree, BSTRemoveRootTest) {
	BST bst;

	bst.insert(50);
	bst.remove(50);

	auto result = inOrderTraversalIter(bst.getRoot());
	vector<int> expected{};

	EXPECT_EQ(result == expected, true);
}

TEST(BinarySearchTree, BSTFloorTest) {
	BST bst;

	bst.insert(10);
	bst.insert(5);
	bst.insert(15);
	bst.insert(12);
	bst.insert(30);

	auto result = bst.floor(14);
	EXPECT_EQ(result->key, 12);

	result = bst.floor(4);
	EXPECT_EQ(result, nullptr);

	result = bst.floor(30);
	EXPECT_EQ(result->key, 30);

	result = bst.floor(100);
	EXPECT_EQ(result->key, 30);
}

TEST(BinarySearchTree, BSTCeilTest) {
	BST bst;

	bst.insert(10);
	bst.insert(5);
	bst.insert(15);
	bst.insert(12);
	bst.insert(30);

	auto result = bst.ceil(14);
	EXPECT_EQ(result->key, 15);

	result = bst.ceil(3);
	EXPECT_EQ(result->key, 5);

	result = bst.ceil(40);
	EXPECT_EQ(result, nullptr);
}

TEST(BinarySearchTree, BSTCeilingLeftSideTest) {
	vector<int> vec{2, 8, 30, 15, 25, 12};
	auto result = ceilingOnLeftSide(vec);
	vector<int> expected{-1, -1, -1, 30, 30, 15};
	EXPECT_EQ(result == expected, true);

	vec = {30, 20, 10};
	result = ceilingOnLeftSide(vec);
	expected = {-1, 30, 20};
	EXPECT_EQ(result == expected, true);

	vec = {10, 20, 30};
	result = ceilingOnLeftSide(vec);
	expected = {-1, -1, -1};
	EXPECT_EQ(result == expected, true);

	vec = {6, 18, 4, 5};
	result = ceilingOnLeftSide(vec);
	expected = {-1, -1, 6, 6};
	EXPECT_EQ(result == expected, true);

	vec = {20, 20, 20};
	result = ceilingOnLeftSide(vec);
	expected = {-1, 20, 20};
	EXPECT_EQ(result == expected, true);
}

TEST(BinarySearchTree, BSTCheckBSTTest) {
	std::shared_ptr<TreeNode<int>> root = std::make_shared<TreeNode<int>>(20);
	root->left = std::make_shared<TreeNode<int>>(8);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = make_shared<TreeNode<int>>(18);
	root->right->right = make_shared<TreeNode<int>>(35);

	auto result = isBST(root);

	EXPECT_EQ(result, false);
}

TEST(BinarySearchTree, BSTPairWithSumTest) {
	BST bst;

	bst.insert(10);
	bst.insert(8);
	bst.insert(4);
	bst.insert(9);
	bst.insert(20);
	bst.insert(11);
	bst.insert(30);
	bst.insert(25);

	auto result = BSTPairWithSumExists(bst.getRoot(), 33);
	EXPECT_EQ(result, true);

	BST bst2;
	bst2.insert(20);
	bst2.insert(8);
	bst2.insert(40);
	bst2.insert(35);

	result = BSTPairWithSumExists(bst2.getRoot(), 49);
	EXPECT_EQ(result, false);

}

TEST(BinarySearchTree, BinaryTreeVerticalSumTest) {
	std::shared_ptr<TreeNode<int>> root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(15);
	root->right = std::make_shared<TreeNode<int>>(25);
	root->left->left = make_shared<TreeNode<int>>(35);
	root->left->right = make_shared<TreeNode<int>>(20);
	root->left->left->left = make_shared<TreeNode<int>>(40);
	root->left->right->right = make_shared<TreeNode<int>>(75);
	root->left->right->right->right = make_shared<TreeNode<int>>(80);

	auto result = BinaryTreeVerticalSum(root);
	vector<int> expected{40, 35, 15, 30, 100, 80};

	EXPECT_EQ(result == expected, true);
}

TEST(BinarySearchTree, BinaryTreeVerticalTraversalTest) {
	std::shared_ptr<TreeNode<int>> root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = make_shared<TreeNode<int>>(40);
	root->right->right = make_shared<TreeNode<int>>(50);

	auto result = BinaryTreeVerticalTraversal(root);
	std::vector<std::vector<int>> expected{{20}, {10, 40}, {30}, {50}};

	EXPECT_EQ(result, expected);
}

TEST(BinarySearchTree, BinaryTreeTopViewTest) {
	std::shared_ptr<TreeNode<int>> root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(50);
	root->left->left = make_shared<TreeNode<int>>(30);
	root->left->right = make_shared<TreeNode<int>>(40);
	root->right->left = make_shared<TreeNode<int>>(60);
	root->right->right = make_shared<TreeNode<int>>(70);

	auto result = BinaryTreeTopView(root);
	std::vector<int> expected{30, 20, 10, 50, 70};
	EXPECT_EQ(result, expected);

	root = std::make_shared<TreeNode<int>>(10);

	result = BinaryTreeTopView(root);
	expected = {10};
	EXPECT_EQ(result, expected);

	root = std::make_shared<TreeNode<int>>(1);
	root->left = std::make_shared<TreeNode<int>>(2);
	root->right = std::make_shared<TreeNode<int>>(3);
	root->left->right = std::make_shared<TreeNode<int>>(4);
	root->left->right->right = std::make_shared<TreeNode<int>>(5);

	result = BinaryTreeTopView(root);
	expected = {2, 1, 3};
	EXPECT_EQ(result, expected);
}

TEST(BinarySearchTree, BinaryTreeBottomViewTest) {
	std::shared_ptr<TreeNode<int>> root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->left->left = make_shared<TreeNode<int>>(40);
	root->left->right = make_shared<TreeNode<int>>(50);

	auto result = BinaryTreeBottomView(root);

	std::vector<int> expected{40, 20, 50, 30};
	EXPECT_EQ(result, expected);

	root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->left->right = std::make_shared<TreeNode<int>>(50);
	root->left->right->right = std::make_shared<TreeNode<int>>(60);

	result = BinaryTreeBottomView(root);
	expected = {20, 50, 60};
	EXPECT_EQ(result, expected);

	root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->left->left = std::make_shared<TreeNode<int>>(40);
	root->left->right = std::make_shared<TreeNode<int>>(50);
	root->right->left = std::make_shared<TreeNode<int>>(60);
	root->right->right = std::make_shared<TreeNode<int>>(70);

	result = BinaryTreeBottomView(root);
	expected = {40, 20, 60, 30, 70};
	EXPECT_EQ(result, expected);
}

TEST(BinarySearchTree, BinaryTreeLeftRotateTest) {
	std::shared_ptr<TreeNode<int>> root = std::make_shared<TreeNode<int>>(10);
	root->right = std::make_shared<TreeNode<int>>(20);
	root->right->right = std::make_shared<TreeNode<int>>(40);
	root->right->right->left = make_shared<TreeNode<int>>(30);
	root->right->right->right = make_shared<TreeNode<int>>(50);

	root = rotateLeft(root, root->right);

	EXPECT_EQ(root->key, 20);
	EXPECT_EQ(root->left->key, 10);
	EXPECT_EQ(root->right->key, 40);
	EXPECT_EQ(root->right->left->key, 30);
	EXPECT_EQ(root->right->right->key, 50);

	root = std::make_shared<TreeNode<int>>(10);
	root->right = std::make_shared<TreeNode<int>>(20);
	root->right->right = std::make_shared<TreeNode<int>>(40);
	root->right->right->left = make_shared<TreeNode<int>>(30);
	root->right->right->right = make_shared<TreeNode<int>>(50);

	root->right = rotateLeft(root->right, root->right->right);

	EXPECT_EQ(root->key, 10);
	EXPECT_EQ(root->right->key, 40);
	EXPECT_EQ(root->right->left->key, 20);
	EXPECT_EQ(root->right->right->key, 50);
	EXPECT_EQ(root->right->left->right->key, 30);
}

TEST(BinarySearchTree, BinaryTreeRightRotateTest) {
	std::shared_ptr<TreeNode<int>> root = std::make_shared<TreeNode<int>>(50);
	root->left = std::make_shared<TreeNode<int>>(40);
	root->left->left = std::make_shared<TreeNode<int>>(20);
	root->left->left->left = make_shared<TreeNode<int>>(10);
	root->left->left->right = make_shared<TreeNode<int>>(30);

	root = rotateRight(root, root->left);

	EXPECT_EQ(root->key, 40);
	EXPECT_EQ(root->left->key, 20);
	EXPECT_EQ(root->right->key, 50);
	EXPECT_EQ(root->left->left->key, 10);
	EXPECT_EQ(root->left->right->key, 30);

	root = std::make_shared<TreeNode<int>>(50);
	root->left = std::make_shared<TreeNode<int>>(40);
	root->left->left = std::make_shared<TreeNode<int>>(20);
	root->left->left->left = make_shared<TreeNode<int>>(10);
	root->left->left->right = make_shared<TreeNode<int>>(30);

	root->left = rotateRight(root->left, root->left->left);

	EXPECT_EQ(root->key, 50);
	EXPECT_EQ(root->left->key, 20);
	EXPECT_EQ(root->left->left->key, 10);
	EXPECT_EQ(root->left->right->key, 40);
	EXPECT_EQ(root->left->right->left->key, 30);
}

TEST(BinarySearchTree, BinaryAVLTreeTest) {
	AVL avl;
	avl.insert(4);
	avl.insert(3);
	avl.insert(12);
	avl.insert(10);
	avl.insert(13);
	avl.insert(9);
	avl.insert(11);

	bool balanced = isTreeBalanced(avl.getRoot());

	EXPECT_EQ(balanced, true);
}

TEST(BinarySearchTree, BSTFixSwappedNodesTest) {
	auto root = std::make_shared<TreeNode<int>>(20);
	root->left = std::make_shared<TreeNode<int>>(60);
	root->left->left = std::make_shared<TreeNode<int>>(4);
	root->left->right = std::make_shared<TreeNode<int>>(10);
	root->right = std::make_shared<TreeNode<int>>(80);
	root->right->left = std::make_shared<TreeNode<int>>(8);
	root->right->right = std::make_shared<TreeNode<int>>(100);

	fixBSTWithTwoNodesSwapped(root);

	auto result = inOrderTraversalIter(root);
	vector<int> expected{4, 8, 10, 20, 60, 80, 100};

	EXPECT_EQ(result, expected);
}

TEST(BinarySearchTree, kthSmallestElementTest) {

	std::vector<int> keys{25, 7, 10, 15, 20};

	BST bst;

	for (auto &k : keys) {
		bst.insert(k);
	}

	auto result = kthSmallestElement(bst.getRoot(), 3);

	EXPECT_EQ(result->key, 15);
}
