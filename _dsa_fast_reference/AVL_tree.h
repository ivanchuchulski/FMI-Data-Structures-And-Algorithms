
struct Node
{
	int data;
	Node* left;
	Node* right;
	int height;		//height of the node in the tree
};

class AVLTree
{
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

	bool Empty() { return _root == nullptr; }

	Node* Insert(Node* node, int value)
	{
		if (node == nullptr)
			return new Node{ value, nullptr, nullptr, 0 };

		if (value < node->data)
			node->left = Insert(node->left, value);
		else if (value > node->data)
			node->right = Insert(node->right, value);
		else
			return node;			//dublicate found !


		node->height = 1 + std::max(NodeHeight(node->left), NodeHeight(node->right));

		int node_balance = NodeBalance(node);

		if (node_balance > 1)		//node is too left-heavy
		{
			if (NodeHeight(node->left->left) >= NodeHeight(node->left->right))
				node = RightRotate(node);
			else
				node = LeftRight(node);
		}

		if (node_balance < -1)		//node is too right-heavy
		{
			if (NodeHeight(node->right->right) >= NodeHeight(node->right->left))
				node = LeftRotate(node);
			else
				node = RightLeft(node);
		}

		return node;
	}

	Node* GetMin(Node* node)
	{
		if (Empty() || node == nullptr)
			return nullptr;

		while (node->left != nullptr)
			node = node->left;

		return node;
	}

	Node* Delete(Node* node, int value)
	{
		if (node == nullptr)
		{
		//	cout << value << " not found to remove" << endl;
			return nullptr;
		}

		else if (value < node->data)
			node->left = Delete(node->left, value);
		else if (value > node->data)
			node->right = Delete(node->right, value);
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
				node->right = Delete(node->right, smallest_right->data);
			}
		}

		if (node == nullptr)
			return nullptr;

		node->height = 1 + std::max(NodeHeight(node->left), NodeHeight(node->right));

		int node_balance = NodeBalance(node);

		if (node_balance > 1)		//node is too left-heavy
		{
			if (NodeBalance(node->left) >= 0)
				node = RightRotate(node);
			else
				node = LeftRight(node);
		}

		if (node_balance < -1)		//node is too right-heavy
		{
			if (NodeBalance(node->right) <= 0)
				node = LeftRotate(node);
			else
				node = RightLeft(node);
		}

		return node;
	}

	Node* Find(Node* node, int value)
	{
		if (node == nullptr)
			return nullptr;

		if (node->data == value)
			return node;

		if (value < node->data)
			return Find(node->left, value);
		else
			return Find(node->right, value);
	}

};

