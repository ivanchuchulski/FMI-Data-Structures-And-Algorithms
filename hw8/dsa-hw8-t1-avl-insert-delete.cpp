#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Node
{
	double data;
	Node* left;
	Node* right;
	int height;		//height of the node in the tree
};

class AVLTree
{
private:
	bool containsRecursive(Node *current, double value)
	{
		if (current == nullptr)
			return false;

		if (current->data == value)
			return true;

		if (value < current->data)
			return containsRecursive(current->left, value);
		else
			return containsRecursive(current->right, value);
	}

	void printRecursive(Node *current)
	{
		if (current == nullptr)
			return;

		printRecursive(current->left);
		cout << current->data << ' ';
		printRecursive(current->right);
	}

protected:
	int NodeHeight(Node* node)
	{
		return node == nullptr ? -1 : node->height;
	}

	int NodeBalance(Node* node)
	{
		return node == nullptr ? 0 : NodeHeight(node->left) - NodeHeight(node->right);
	}

	Node* RightRotate(Node* root)
	{
		Node* future_root = root->left;

		root->left = future_root->right;

		future_root->right = root;

		//updating heights
		root->height = 1 + std::max(NodeHeight(root->left), NodeHeight(root->right));
		future_root->height = 1 + std::max(NodeHeight(future_root->left), NodeHeight(future_root->right));

		return future_root;
	}

	Node* LeftRotate(Node* root)
	{
		Node* future_root = root->right;

		root->right = future_root->left;
		future_root->left = root;

		root->height = 1 + std::max(NodeHeight(root->left), NodeHeight(root->right));
		future_root->height = 1 + std::max(NodeHeight(future_root->left), NodeHeight(future_root->right));

		return future_root;
	}

	Node* RightLeft(Node* root)
	{
		root->right = RightRotate(root->right);
		return LeftRotate(root);
	}

	Node* LeftRight(Node* root)
	{
		root->left = LeftRotate(root->left);
		return RightRotate(root);
	}


public:
	Node* _root;

	AVLTree() : _root(nullptr)
 	{}
	
	~AVLTree()
	{}

	bool Empty() { return _root == nullptr; }

	Node* Insert(Node* root, double value)
	{
		if (root == nullptr)
			return new Node{ value, nullptr, nullptr, 0 };

		if (value < root->data)
			root->left = Insert(root->left, value);
		else if (value > root->data)
			root->right = Insert(root->right, value);
		else
		{	
			//dublicate found !
			cout << value << " already added" << endl;
			return root;	
		}

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
			if (NodeHeight(root->right->right) >= NodeHeight(root->right->left))
				root = LeftRotate(root);
			else
				root = RightLeft(root);
		}

		return root;
	}

	Node* GetMin(Node* node)
	{
		if (Empty() || node == nullptr)
			return nullptr;

		while (node->left != nullptr)
			node = node->left;

		return node;
	}

	Node* Delete(Node* root, double value)
	{
		if (root == nullptr)
		{
			cout << value << " not found to remove" << endl;
			return nullptr;
		}

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
			return nullptr;

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

	bool contains(double value)
	{
		if (Empty())
			return false;

		return containsRecursive(_root, value);
	}

	void print()
	{
		if (Empty())
			return;

		printRecursive(_root);
		cout << endl;
	}

};

int main()
{
	ios_base::sync_with_stdio(false);

	AVLTree tree;
	string operation;
	double number;
	int N;

	cin >> N;
	cout << fixed;

	for (size_t i = 0; i < N; i++)
	{
		cin >> operation;
		if (operation != "print")
		{
			cin >> number;
		}

		if (operation == "add")
		{
			tree._root = tree.Insert(tree._root, number);
		}
		else if (operation == "remove")
		{
			tree._root = tree.Delete(tree._root, number);
		}
		else if (operation == "contains")
		{
			if (tree.contains(number))
			{
				cout << "yes" << endl;
			}
			else
			{
				cout << "no" << endl;
			}
		}
		else if (operation == "print")
		{
			tree.print();
		}
	}

	return 0;
}