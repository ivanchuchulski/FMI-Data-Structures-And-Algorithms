#pragma once

#include <iostream>
#include <queue>
#include <stack>

int Max(int a, int b)
{
	return a > b ? a : b;
}


struct Node
{
	int _data;
	Node* _left;
	Node* _right;
};

class BinarySearchTree
{
private:
	Node* CopyFrom(Node* other_root);

public:
	Node* _root;

	BinarySearchTree();
	~BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& other);
	BinarySearchTree& operator=(const BinarySearchTree& other);

	inline bool Empty() const
	{
		return _root == nullptr;
	}

	void Create(int value)
	{
		if (Empty())
			_root = new Node{ value, nullptr, nullptr };
		else
			return;
	}

	void ClearTree(Node* root);

	// [left, root, right]
	void InOrderTraversal(Node* root);

	// [root, left, right], use this to copy a binary search tree
	void PreOrderTraversal(Node* root);

	// [left, right, root], use this to delete a binary seach tree
	void PostOrderTraversal(Node* root);

	Node* InsertItem(Node* node, int value);		//recursively
	void Insert(int value);							//iteratively

	Node* DeleteItem(Node* node, int value);

	int Height(Node* root) const;
	int NumberOfNodes(Node* root) const;

	Node* GetMin(Node* root);
	Node* GetMax(Node* root);

	Node* Find(Node* node, int value);

	void BreadthFirstSearch();

	//equiv to PreOrderTraversal [root, left, right]
	void DepthFirstSearch();

	Node* GetSuccessor(Node* root, int value);

};


BinarySearchTree::BinarySearchTree()
	: _root(nullptr)
{}

inline BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
	: _root(nullptr)
{
	_root = CopyFrom(other._root);
}


BinarySearchTree::~BinarySearchTree()
{
	ClearTree(_root);
}

inline BinarySearchTree & BinarySearchTree::operator=(const BinarySearchTree& other)
{
	if (this != &other)
	{
		ClearTree(_root);
		_root = CopyFrom(other._root);
	}

	return *this;		// TODO: insert return statement here
}


Node* BinarySearchTree::CopyFrom(Node* other_root)
{
	if (other_root == nullptr)
		return nullptr;

	Node* entry = new Node{ other_root->_data, nullptr, nullptr };

	entry->_left = CopyFrom(other_root->_left);

	entry->_right = CopyFrom(other_root->_right);

	return entry;
}

void BinarySearchTree::ClearTree(Node* root)
{
	if (root == nullptr)
		return;

	ClearTree(root->_left);
	ClearTree(root->_right);

//	std::cout << "deleting " << root->_data << '\n';
	delete root;
}


void BinarySearchTree::InOrderTraversal(Node* root)
{
	if (root == nullptr)
		return;

	InOrderTraversal(root->_left);

	std::cout << root->_data << ' ';

	InOrderTraversal(root->_right);
}

void BinarySearchTree::PreOrderTraversal(Node* root)
{
	if (root == nullptr)
		return;

	std::cout << root->_data << ' ';

	PreOrderTraversal(root->_left);

	PreOrderTraversal(root->_right);
}

void BinarySearchTree::PostOrderTraversal(Node* root)
{
	if (root == nullptr)
		return;

	PostOrderTraversal(root->_left);

	PostOrderTraversal(root->_right);

	std::cout << root->_data << ' ';//action performed
}

Node* BinarySearchTree::InsertItem(Node* node, int value)
{
	if (node == nullptr)
		return new Node{ value, nullptr, nullptr };

	if (value < node->_data)
		node->_left = InsertItem(node->_left, value);

	else if (value > node->_data)
		node->_right = InsertItem(node->_right, value);

	else
	{
		std::cout << "item already in tree!\n";
		return node;
	}

	return node;	//! return the unchanged current node for the previous recursion call

}

void BinarySearchTree::Insert(int value)
{
	if (Empty())
	{
		_root = new Node{ value, nullptr, nullptr };
		return;
	}

	Node* parent = nullptr;
	Node* current = _root;

	while (current != nullptr)
	{
		parent = current;

		if (value < current->_data)
			current = current->_left;

		else if (value > current->_data)
			current = current->_right;

		else
			return;   //dublicate found!
	}

	Node* entry = new Node{ value, nullptr, nullptr };

	if (value < parent->_data)
		parent->_left = entry;
	else
		parent->_right = entry;
}

Node* BinarySearchTree::DeleteItem(Node* node, int value)
{
	if (node == nullptr)
		return nullptr;

	if (value < node->_data)
		node->_left = DeleteItem(node->_left, value);

	else if (value > node->_data)
		node->_right = DeleteItem(node->_right, value);

	else
	{
		if (node->_left == nullptr)
		{
			Node* temp = node->_right;
			delete node;
			return temp;
		}
		else if (node->_right == nullptr)
		{
			Node* temp = node->_left;
			delete node;
			return temp;
		}
		//at this point the node has 2 children
		Node* smallest_right = GetMin(node->_right);

		node->_data = smallest_right->_data;
		
		node->_right = DeleteItem(node->_right, smallest_right->_data);
	}

	return node;
}




int BinarySearchTree::Height(Node * root) const
{
	if (root == nullptr)
		return -1;

	return 1 + Max(Height(root->_left), Height(root->_right));
}

int BinarySearchTree::NumberOfNodes(Node * root) const
{
	if (root == nullptr)
		return 0;

	return 1 + NumberOfNodes(root->_left) + NumberOfNodes(root->_right);
}


Node* BinarySearchTree::GetMin(Node* node)
{
	if (Empty()|| node == nullptr)
		return nullptr;

	while (node->_left != nullptr)
		node = node->_left;

	return node;
}

Node* BinarySearchTree::GetMax(Node* node)
{
	if (Empty() || node == nullptr)
		return nullptr;

	while (node->_right != nullptr)
		node = node->_right;

	return node;
}

Node* BinarySearchTree::Find(Node* node, int value)
{
	if (node == nullptr)
		return nullptr;

	while (node != nullptr && node->_data != value)
	{
		if (value < node->_data)
			node = node->_left;
		else
			node = node->_right;
	}

	return node;//node would be nullptr if the element if not found
}

void BinarySearchTree::BreadthFirstSearch()
{
	if (Empty())
		return;

	std::queue<Node*> que;

	if (_root != nullptr)
		que.push(_root);

	while (!que.empty())
	{
		Node* current = que.front();

		que.pop();

		std::cout << current->_data << ' ';		//action with the data

		if (current->_left != nullptr)
			que.push(current->_left);

		if (current->_right != nullptr)
			que.push(current->_right);
	}
}

void BinarySearchTree::DepthFirstSearch()
{
	if (Empty())
		return;

	std::stack<Node*> st;
	Node* temp = nullptr;

	if (_root != nullptr)
		st.push(_root);

	while (!st.empty())
	{
		temp = st.top();

		st.pop();

		std::cout << temp->_data << ' ';

		if (temp->_right != nullptr)
			st.push(temp->_right);

		if (temp->_left != nullptr)
			st.push(temp->_left);
	}
}


Node* BinarySearchTree::GetSuccessor(Node* root, int value)
{
	Node* element = Find(root, value);

	if (element == nullptr)
		return nullptr; //no such element with the value

	if (element->_right != nullptr)     //if the element has a non-empty right subtree
		return GetMin(element->_right);

	Node* successor = nullptr;
	Node* ancestor = root;

	while (ancestor != element)
	{
		if (element->_data < ancestor->_data)
		{
			successor = ancestor;
			ancestor = ancestor->_left;
		}
		else
			ancestor = ancestor->_right;
	}
	return successor;
}