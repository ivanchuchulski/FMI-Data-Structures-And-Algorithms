#pragma once

#include <algorithm>

using std::max;



struct Node
{
	int data;
	Node* left;
	Node* right;
	int height;

	//the height of a leaf is 0
	Node(int value, Node* l = nullptr, Node* r = nullptr, int h = 0) : data(value), left(l), right(r), height(h)
	{}
};

class AVLTree
{
protected:
	int GetNodeHeight(Node* node);
	int BalanceFactor(Node* node);
	void AdjustHeight(Node* node);

	void RightRotation(Node*& root);
	void LeftRotation(Node*& root);

	void RightLeft(Node*& root);
	void LeftRight(Node*& root);

	void RestoreBalance(Node*& root);


public:
	Node* _root;

	AVLTree() : _root(nullptr)
	{}

	~AVLTree()
	{}

	bool Empty() { return _root == nullptr; }

	Node* GetMin(Node* node);
	Node* GetMax(Node* node);

	void Insert(Node*& root, int value);
	void Delete(Node*& root, int value);

	void Preorder(Node* root);
	
};


int AVLTree::GetNodeHeight(Node* node)
{
	return node == nullptr ? -1 : node->height;
}

int AVLTree::BalanceFactor(Node* node)
{
	return node == nullptr ? 0 :( GetNodeHeight(node->left) - GetNodeHeight(node->right) );
}

void AVLTree::AdjustHeight(Node* node)
{
	node->height = 1 + max(GetNodeHeight(node->left), GetNodeHeight(node->right));
}

void AVLTree::RightRotation(Node*& root)
{
	Node* future_root = root->left;

	root->left = future_root->right;
	future_root->right = root;

	AdjustHeight(root);
	AdjustHeight(future_root);

	//root->height = 1 + std::max(GetNodeHeight(root->left), GetNodeHeight(root->right));
	//future_root->height = 1 + std::max(GetNodeHeight(future_root->left), GetNodeHeight(future_root->right));

	root = future_root;	
}

void AVLTree::LeftRotation(Node *& root)
{
	Node* future_root = root->right;

	root->right = future_root->left;
	future_root->left = root;

	AdjustHeight(root);
	AdjustHeight(future_root);

//	root->height = 1 + max(GetNodeHeight(root->left), GetNodeHeight(root->right));
//	future_root->height = 1 + max(GetNodeHeight(future_root->left), GetNodeHeight(future_root->right));

	root = future_root;
}

void AVLTree::RightLeft(Node *& root)
{
	RightRotation(root->right);
	LeftRotation(root);
}

void AVLTree::LeftRight(Node *& root)
{
	LeftRotation(root->left);
	RightRotation(root);
}

void AVLTree::RestoreBalance(Node *& root)
{
	if (root == nullptr)
		return;

	if (BalanceFactor(root) > 1)		//node is left-heavy
	{
		if (GetNodeHeight(root->left->left) >= GetNodeHeight(root->left->right))
			RightRotation(root);
		else
			LeftRight(root);
	}

	if (BalanceFactor(root) < -1)		//node is right-heavy
	{
		if (GetNodeHeight(root->right->right) >= GetNodeHeight(root->right->left))
			LeftRotation(root);
		else
			RightLeft(root);
	}

//	root->height = 1 + max(GetNodeHeight(root->left), GetNodeHeight(root->right));
	AdjustHeight(root);
}

void AVLTree::Insert(Node *& root, int value)
{
	if (root == nullptr)
	{
		root = new Node{ value, nullptr, nullptr, 0 };
		return;
	}

	if (value < root->data)
		Insert(root->left, value);
	else if (value > root->data)
		Insert(root->right, value);
	else
		return;			//dublicate found !

	RestoreBalance(root);
}

Node* AVLTree::GetMin(Node* node)
{
	if (Empty() || node == nullptr)
		return nullptr;

	while (node->left != nullptr)
		node = node->left;

	return node;
}

Node* AVLTree::GetMax(Node* node)
{
	if (Empty() || node == nullptr)
		return nullptr;

	while (node->right != nullptr)
		node = node->right;

	return node;
}

void AVLTree::Delete(Node *& root, int value)
{
	if (root == nullptr)
		return;			//item not in tree
	
	if (value < root->data)
		Delete(root->left, value);
	else if (value > root->data)
		Delete(root->right, value);
	else if (root->left != nullptr && root->right != nullptr)	//case with 2 children
	{
		root->data = GetMin(root->right)->data;
		Delete(root->right, root->data);
	}
	else//either left or right child is null
	{
		Node* to_remove = root;
		root = root->left == nullptr ? root->right : root->left;
		delete to_remove;
	}

	RestoreBalance(root);
}


void AVLTree::Preorder(Node* root)
{
	if (root == nullptr)
		return;

	std::cout << root->data << ' ';

	Preorder(root->left);
	Preorder(root->right);
}