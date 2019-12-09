#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

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

	Node* GetMin(Node* node)
	{
		if (node == nullptr)
			return nullptr;

		while (node->left != nullptr)
			node = node->left;
		
		return node;
	}


	Node* Remove(Node* node, int val)
	{
		if (node == nullptr)
			return nullptr;

		if (val < node->data)
			node->left = Remove(node->left, val);
		else if (val > node->data)
			node->right = Remove(node->right, val);
		else
		{
			if (node->left == nullptr)
			{
				Node* temp = node->right;
				delete node;
				return temp;
			}

			else if (node->right == nullptr)
			{
				Node* temp = node->left;
				delete node;
				return temp;
			}
			else
			{
				Node* smallest_right = GetMin(node->right);

				node->data = smallest_right->data;

				node->right = Remove(node->right, smallest_right->data);
			}

		}

		return node;
	}

	void PrintOddLayers(Node* node)
	{
		if (node == nullptr)
			return;

		int level = 0;
		queue<Node*> que;
		que.push(node);

		while (!que.empty())
		{
			int size = que.size();
			level++;

			for (int i = 0; i < size; i++)
			{
				Node* curr = que.front();
				que.pop();

				if (level % 2 != 0)
				{
					cout << curr->data << ' ';
				}

				if (curr->left != nullptr)
					que.push(curr->left);
				if (curr->right != nullptr)
					que.push(curr->right);
			}

		}

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

		if (op == "remove")
		{
			cin >> val;
			tree._root = tree.Remove(tree._root, val);
		}

		if (op == "print_odd_layers")
			tree.PrintOddLayers(tree._root);

	}

	return 0;
}
