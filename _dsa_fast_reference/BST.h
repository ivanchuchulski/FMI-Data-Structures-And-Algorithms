
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

    bool Empty() { return _root == nullptr; }

    void InOrderDFS(Node* node)
    {
        if (node == nullptr)
            return;

        InOrderDFS(node->left);

        std::cout << node->data << ' ';

        InOrderDFS(node->right); 

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


    Node* Insert(Node* node, int value)
    {
		if (node == nullptr)
			return new Node{ value, nullptr, nullptr };

		if (value < node->data)
			node->left = Insert(node->left, value);
		else if (value > node->data)
			node->right = Insert(node->right, value);
		else
			return node;	//dublicate item

		return node;
    }

    Node* DeleteItem(Node* node, int value)
    {      
        if (node == nullptr)
            return nullptr;

        if (value < node->data)
            node->left = DeleteItem(node->left, value);
        else if (value > node->data)
            node->right = DeleteItem(node->right, value);
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

                node->right = DeleteItem(node->right, smallest_right->data);
            }
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

    Node* GetMax(Node* node)
    {
        if (Empty() || node == nullptr)  
			return nullptr;

        while (node->right != nullptr)
            node = node->right;

        return node;
    }

    int Height(Node* node)
    {
        if (node == nullptr)
            return -1;

        return 1 + Max(Height(node->left), Height(node->right));
    }

    int NumberOfNodes(Node* node)
    {
        if (node == nullptr)
            return 0;

        return 1 + NumberOfNodes(node->left) + NumberOfNodes(node->right);
    }


    Node* GetSuccessor(Node* root, int value)
    {
        Node* element = Find(root, value);

        if (element == nullptr)
            return nullptr; //no such element with the value

        if (element->right != nullptr)     //if the element has a non-empty right subtree
            return GetMin(element->right);

        Node* successor = nullptr;
        Node* ancestor = root;

        while (ancestor != element)
        {
            if (element->data < ancestor->data)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }
        return successor;
    }

};


void PrintLevel(Node* root, int level)
{
    if (root == nullptr)
        return;

    if (root != nullptr && level == 0)
        cout << root->data << ' ';

    else
    {
        PrintLevel(root->left, level - 1);
        PrintLevel(root->right, level - 1);
    }

    return;
}
