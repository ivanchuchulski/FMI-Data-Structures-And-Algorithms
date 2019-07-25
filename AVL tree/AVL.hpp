#pragma once

#include <iostream>
#include <algorithm>

struct Node
{
	int data;
	Node* left;
	Node* right;
	int height;		//height of the node in the tree
};


class AVL
{
protected:
	int NodeHeight(Node* node);
	int NodeBalance(Node* node);

	Node* RightRotate(Node* root);
	Node* LeftRotate(Node* root);

	Node* RightLeft(Node* root);
	Node* LeftRight(Node* root);

public:
	Node* _root;

	AVL() : _root(nullptr) 
	{}

	~AVL()
	{}

	bool Empty() { return _root == nullptr; }

	Node* GetMin(Node* node);
	Node* GetMax(Node* node);

	Node* Insert(Node* root,int value);

	Node* Delete(Node* root, int value);

	void Preorder(Node* root);

};

int AVL::NodeHeight(Node* node)
{
	return node == nullptr ? -1 : node->height;
}

int AVL::NodeBalance(Node* node)
{
	return node == nullptr ? 0 : NodeHeight(node->left) - NodeHeight(node->right);
}


Node* AVL::RightRotate(Node* root)		//in the book rotateWithLeftChild
{
	Node* future_root = root->left;

	root->left = future_root->right;

	future_root->right = root;

	//updating heights
	root->height = 1 + std::max(NodeHeight(root->left), NodeHeight(root->right));
	future_root->height = 1 + std::max(NodeHeight(future_root->left), NodeHeight(future_root->right));

	return future_root;
}

Node* AVL::LeftRotate(Node * root)
{
	Node* future_root = root->right;

	root->right = future_root->left;
	future_root->left = root;

	root->height = 1 + std::max(NodeHeight(root->left), NodeHeight(root->right));
	future_root->height = 1 + std::max(NodeHeight(future_root->left), NodeHeight(future_root->right));

	return future_root; 
}

Node* AVL::RightLeft(Node * root)
{
	root->right = RightRotate(root->right);
	return LeftRotate(root);
}

Node* AVL::LeftRight(Node * root)
{
	root->left = LeftRotate(root->left);
	return RightRotate(root);
}


Node* AVL::Insert(Node* root, int value)
{
	if (root == nullptr)
		return new Node{ value, nullptr, nullptr, 0 };

	if (value < root->data)
		root->left = Insert(root->left, value);
	else if (value > root->data)
		root->right = Insert(root->right, value);
	else
		return root;		//dublicate found !

	root->height = 1 + std::max(NodeHeight(root->left), NodeHeight(root->right));

	int root_balance = NodeBalance(root);

	if (root_balance > 1)		//node is too left-heavy
	{
		if (NodeHeight(root->left->left) >= NodeHeight(root->left->right))
			root = RightRotate(root);
		else
			root = LeftRight(root);
	}

	if (root_balance < -1)		//node is too right-heavy
	{
		if (value > root->right->data)
			root = LeftRotate(root);
		else
			root = RightLeft(root);
	}

	return root;
}


Node* AVL::GetMin(Node* node)
{
	if (Empty() || node == nullptr)
		return nullptr;
	
	while (node->left != nullptr)
		node = node->left;

	return node;
}

Node* AVL::GetMax(Node* node)
{
	if (Empty() || node == nullptr)
		return nullptr;

	while (node->right != nullptr)
		node = node->right;

	return node;
}

Node* AVL::Delete(Node* root, int value)
{
	if (root == nullptr)
		return nullptr;

	else if (value < root->data)
		root->left = Delete(root->left, value);

	else if (value > root->data)
		root->right = Delete(root->right, value);

	else
	{
		if (root->left == nullptr)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == nullptr)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		else 
		{
			Node* smallest_right = GetMin(root->right);
			root->data = smallest_right->data;
			root->right = Delete(root->right, smallest_right->data);
		}
	}

	if (root == nullptr)
		return root;

	root->height = 1 + std::max(NodeHeight(root->left), NodeHeight(root->right));

	int root_balance = NodeBalance(root);

	if (root_balance > 1)		//node is too left-heavy
	{
		if (NodeBalance(root->left) >= 0)
			root = RightRotate(root);
		else
			root = LeftRight(root);
	}

	if (root_balance < -1)		//node is too right-heavy
	{
		if (NodeBalance(root->right) <= 0)
			root = LeftRotate(root);
		else
			root = RightLeft(root);
	}

	return root;
}

void AVL::Preorder(Node * root)
{
	if (root == nullptr)
		return;

	std::cout << root->data << ' ';

	Preorder(root->left);
	Preorder(root->right);
}