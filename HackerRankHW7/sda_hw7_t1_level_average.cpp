#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

using std::cout;
using std::cin;


struct Node
{
	int _data;
	Node* _left;
	Node* _right;
};

class BinarySearchTree
{
public:
	Node* _root;

	BinarySearchTree() : _root(nullptr)
	{}

	~BinarySearchTree()
	{}

	inline bool Empty() { return _root == nullptr; }

	void Inorder(Node* root)
	{
		if (root == nullptr)
			return;

		Inorder(root->_left);
		cout << root->_data << ' ';
		Inorder(root->_right);
	}

	void Insert(int value)
	{
		if (Empty())
		{
			_root = new Node{ value, nullptr, nullptr };
			return;
		}

		Node* parent = nullptr;
		Node* curr = _root;

		while (curr != nullptr)
		{
			parent = curr;

			if (value < curr->_data)
				curr = curr->_left;
			else
				curr = curr->_right;//here the condition that dublicate elements are put in the right subtree
		}


		if (value < parent->_data)
			parent->_left = new Node{ value, nullptr, nullptr };
		else
			parent->_right = new Node{ value, nullptr, nullptr };
	}

};


int main() {

	std::ios_base::sync_with_stdio(false);

	int nodes_num = 0;
	int elem = 0;
	BinarySearchTree tree;

	cin >> nodes_num;

	for (int i = 0; i < nodes_num; i++)
	{
		cin >> elem;
		tree.Insert(elem);
	}

	tree.Inorder(tree._root);
	cout << '\n';


	Node* temp = nullptr;
	std::queue<Node*> que;
	std::vector<double> mean_values;

	que.push(tree._root);
	double items_count = 1;
	double sum = 0;

	while (!que.empty())
	{
		items_count = que.size();

		for (int i = 0; i < items_count; i++)
		{
			temp = que.front();
			que.pop();

			sum += temp->_data;

			if (temp->_left != nullptr)
				que.push(temp->_left);

			if (temp->_right != nullptr)
				que.push(temp->_right);

		}

		mean_values.push_back(sum / items_count);
		sum = 0;
	}

	//fixing the precision of the stream
	cout << std::fixed << std::setprecision(3);

	//printing means
	for (double& mean : mean_values)
		cout << mean << '\n';

	std::system("pause");
	return 0;
}