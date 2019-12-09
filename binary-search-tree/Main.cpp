#include <iostream>
#include <algorithm>
#include <vector>

#include "BinarySearchTree.hpp"

using std::cout;
using std::cin;

void DeleteByGivenNode(Node*& node)
{
	if (node == nullptr)
		return;

	Node* temp = node;

	if (node->_left == nullptr)
		node = node->_right;
	else if (node->_right == nullptr)
		node = node->_left;
	else
	{
		temp = node->_right;
		//find the smallest in the right subtree
		while (temp->_left != nullptr)
			temp = temp->_left;

		temp->_left = node->_right;

		temp = node;
		node = node->_right;
	}

	delete temp;
}

void SumOfLeavesUtil(Node* node, int& sum)	//basicly an inorder traversal
{
	if (node == nullptr)
		return;

	SumOfLeavesUtil(node->_left, sum);

	//leaf check
	if (node->_left == nullptr && node->_right == nullptr)
		sum += node->_data;

	SumOfLeavesUtil(node->_right, sum);
}


int SumOfLeaves(Node* node)
{
	int sum = 0;

	SumOfLeavesUtil(node, sum);

	return sum;
}

void Inorder(Node* node, std::vector<int>& values)
{
	if (node == nullptr)
		return;

	Inorder(node->_left, values);
	values.push_back(node->_data);
	cout << node->_data << ' ';
	Inorder(node->_right, values);
}

bool CheckBST(Node* node)
{
	std::vector<int> values;

	Inorder(node, values);

	for (int i = 1; i < values.size(); i++)
		if (values[i - 1] >= values[i])
			return false;

	return true;
}

int GetNodeLevel(Node* node, int value)	//or depth
{
	int level = 0;

	while (node != nullptr)
	{
		if (value == node->_data)
			return level;

		else if (value < node->_data)
		{
			node = node->_left;
			level++;
		}
		else
		{
			node = node->_right;
			level++;
		}
	}

	return -1;	//if not present
}

int MinimumDepth(Node* node)
{
	if (node == nullptr)
		return -1;

	//leaf node check
	if (node->_left == nullptr && node->_right == nullptr)
		return 0;

	if (node->_left == nullptr)				//left subtree empty
		return 1 + MinimumDepth(node->_right);

	else if (node->_right == nullptr)		//right subtree empty case
		return 1 + MinimumDepth(node->_left);

	else
		return 1 + std::min(MinimumDepth(node->_left), MinimumDepth(node->_right));
}

//levels are counted from 0, method can be used to perform action on certain level
void PrintLevel(Node* root, int level)
{
	if (root == nullptr)
		return;

	if (root != nullptr && level == 0)
		cout << root->_data << ' ';

	PrintLevel(root->_left, level - 1);
	PrintLevel(root->_right, level - 1);
}


int main() {

	std::ios_base::sync_with_stdio(false);


	{
		BinarySearchTree tree;

		//tree.Insert(8);
		//tree.Insert(2);
		//tree.Insert(10);
		//tree.Insert(1);
		//tree.Insert(4);
		//tree.Insert(3);
		//tree.Insert(5);
		//tree.Insert(9);

		//tree.Insert(-5);
		//tree.Insert(16);
		//tree.Insert(18);
		//tree.Insert(-8);
		//tree.Insert(7);
		//tree.Insert(6);
	//	tree.Insert(-5);

		tree.Insert(6);
		tree.Insert(10);
		tree.Insert(2);
		tree.Insert(4);
		tree.Insert(3);
		tree.Insert(5);
		tree.Insert(14);


		PrintLevel(tree._root, 0);
		cout << '\n';
		PrintLevel(tree._root, 1);
		cout << '\n';
		PrintLevel(tree._root, 2);
		cout << '\n';
		PrintLevel(tree._root, 3);
		cout << '\n';

		cout << "minimum depth: " << MinimumDepth(tree._root) << '\n';

		cout << tree.GetSuccessor(tree._root, 5)->_data << '\n';
		cout << tree.GetSuccessor(tree._root, 5)->_data << '\n';
		cout << "sum of leaves : " << SumOfLeaves(tree._root) << '\n';

		cout << "is BST : " << CheckBST(tree._root) << '\n';

		cout << " : " << GetNodeLevel(tree._root, 6) << '\n';
		cout << " : " << GetNodeLevel(tree._root, 10) << '\n';
		cout << " : " << GetNodeLevel(tree._root, 14) << '\n';
		cout << " : " << GetNodeLevel(tree._root, 4) << '\n';
		cout << " : " << GetNodeLevel(tree._root, 5) << '\n';


		tree.InOrderTraversal(tree._root);
		cout << '\n';
		cout << "tree1 height : " << tree.Height(tree._root) << '\n';
		cout << "tree1 number of nodes : " << tree.NumberOfNodes(tree._root) << '\n';

		tree.DeleteItem(tree._root, 4);

		tree.InOrderTraversal(tree._root);
		cout << '\n';
		cout << "tree1 height : " << tree.Height(tree._root) << '\n';
		cout << "tree1 number of nodes : " << tree.NumberOfNodes(tree._root) << '\n';

		//{
		   // BinarySearchTree* tree2 = new BinarySearchTree(tree1);
		   // tree2->InOrderTraversal(tree2->_root);
		   // cout << '\n';
		   // delete tree2;
		//}


		//cout << tree1.GetMax(tree1._root)->_data << '\n';
		//cout << tree1.GetMin(tree1._root)->_data << '\n';

		//cout << tree1.Find(tree1._root, 5)->_data << '\n';

		//cout << "BFS : \n";
		//tree1.BreadthFirstSearch();
		//cout << '\n';

		//cout << "DFS : \n";
		//tree1.DepthFirstSearch();
		//cout << '\n';

		//tree1.PreOrderTraversal(tree1._root);
		//cout << '\n';
	}

	std::system("pause");
	return 0;
}