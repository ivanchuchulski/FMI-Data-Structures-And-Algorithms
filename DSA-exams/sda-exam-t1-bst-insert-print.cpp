#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;
};

class BST
{
public:
	Node* _root;

	BST() : _root(nullptr)
	{}

	Node* Insert(Node* node, int val)
	{
		if (node == nullptr)
			return new Node{ val, nullptr };

		if (val < node->data)
			node->left = Insert(node->left, val);
		else if (val > node->data)
			node->right = Insert(node->right, val);
		else
			return node;

		return node;
	}

	void InOrder(Node* node)
	{
		if (node == nullptr)
			return;

		cout << node->data << ' ';

		InOrder(node->left);
		InOrder(node->right);
	}


};



int main() {
	
	ios_base::sync_with_stdio(false);

	int N;

	cin >> N;

	BST tree;

	string op;
	int val;
	for (int i = 0; i < N; i++)
	{
		cin >> op;

		if (op == "add")
		{
			cin >> val;
			tree._root = tree.Insert(tree._root, val);
		}

		if (op == "print")
			tree.InOrder(tree._root);

	}

	return 0;
}
