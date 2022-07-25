/*
 * tree_tests.cpp
 *
 *  Created on: 16 Jul 2021
 *      Author: ykhan
 */

#include "../src/tree/tree.h"
#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(Tree, BuildTreeInPreOrderTest) {
	vector<int> inorder{40, 20, 60, 50, 70, 10, 80, 100, 30};
	vector<int> preorder{10, 20, 40, 50, 60, 70, 30, 80, 100};

	auto root = createTree(inorder, preorder);

	vector<int> res_inorder;
	vector<int> res_preorder;

	//inOrderTraversal(root, std::function<void(const TreeNode<T>&)> fn)
	inOrderTraversal(root, [&res_inorder](const TreeNode<int>& n) {
		res_inorder.push_back(n.key);
	});

	//preOrderTraversal(root, std::function<void(const TreeNode<T>&)> fn)
	preOrderTraversal(root, [&res_preorder](const TreeNode<int>& n) {
		res_preorder.push_back(n.key);
	});

	EXPECT_EQ(std::equal(inorder.begin(), inorder.end(), res_inorder.begin()),
			true);
	EXPECT_EQ(
			std::equal(preorder.begin(), preorder.end(), res_preorder.begin()),
			true);
}

TEST(Tree, SpiralTreeTraversalTest) {
	auto root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = std::make_shared<TreeNode<int>>(40);
	root->right->right = std::make_shared<TreeNode<int>>(50);
	root->right->left->left = std::make_shared<TreeNode<int>>(60);
	root->right->left->right = std::make_shared<TreeNode<int>>(70);
	root->right->right->right = std::make_shared<TreeNode<int>>(80);

	vector<int> result;
	spiralTraversal(root, [&result](const int& n) {
		result.push_back(n);
	});

	vector<int> expected{10, 30, 20, 40, 50, 80, 70, 60};

	EXPECT_EQ(result == expected, true);
}

TEST(Tree, TreeDiameterTest) {
	auto root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = std::make_shared<TreeNode<int>>(40);
	root->right->right = std::make_shared<TreeNode<int>>(50);
	root->right->left->left = std::make_shared<TreeNode<int>>(60);

	int result = diameterOfTree(root);

	EXPECT_EQ(5, result);
}

TEST(Tree, LowestCommonAncestorTest) {
	auto root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = std::make_shared<TreeNode<int>>(40);
	root->right->right = std::make_shared<TreeNode<int>>(50);

	EXPECT_EQ(10, lowestCommonAncestor(root, 20, 50));
}

TEST(Tree, LowestCommonAncestorBetterTest) {
	auto root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = std::make_shared<TreeNode<int>>(40);
	root->right->right = std::make_shared<TreeNode<int>>(50);

	auto result = lowestCommonAncestorBetter(root, 20, 50);
	EXPECT_EQ(10, root->key);
}

TEST(Tree, CountNodesTest) {
	auto root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = std::make_shared<TreeNode<int>>(40);
	root->right->right = std::make_shared<TreeNode<int>>(50);

	EXPECT_EQ(5, countNodes(root));

}
// countNodesCompleteTree(std::shared_ptr<TreeNode<T>> root)
TEST(Tree, BurnTreeFromLeafTest) {
	auto root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->left->left = std::make_shared<TreeNode<int>>(40);
	root->left->right = std::make_shared<TreeNode<int>>(50);
	root->left->left->left = std::make_shared<TreeNode<int>>(60);
	root->left->left->left->left = std::make_shared<TreeNode<int>>(70);

	int result = burnTreeFromLeaf(root, 50);

	EXPECT_EQ(result, 4);
}

TEST(Tree, TreeSerializeTest) {

	auto root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = std::make_shared<TreeNode<int>>(40);
	root->right->right = std::make_shared<TreeNode<int>>(50);

	auto result = serializeTree(root);

	vector<int> expected{10, 20, 0, 0, 30, 40, 0, 0, 50, 0, 0};

	EXPECT_EQ(expected == result, true);
}

TEST(Tree, TreeDeserializeTest) {

	vector<int> input{10, 20, 0, 0, 30, 40, 0, 0, 50, 0, 0};

	auto root = deserializeTree(input);

	auto output = serializeTree(root);

	EXPECT_EQ(input == output, true);
}

TEST(Tree, InOrderTraversalIterativeTest) {
	auto root = std::make_shared<TreeNode<int>>(10);
	root->left = std::make_shared<TreeNode<int>>(20);
	root->right = std::make_shared<TreeNode<int>>(30);
	root->right->left = std::make_shared<TreeNode<int>>(40);
	root->right->right = std::make_shared<TreeNode<int>>(50);

	vector<int> expected{20, 10, 40, 30, 50};

	auto result = inOrderTraversalIter(root);

	EXPECT_EQ(result == expected, true);
}


