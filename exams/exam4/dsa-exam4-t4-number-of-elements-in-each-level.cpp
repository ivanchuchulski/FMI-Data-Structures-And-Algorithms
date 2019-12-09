#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
    public:
        int data;
        Node *leftNode;
        Node *rightNode;
        Node(int d) {
            data = d;
            leftNode = NULL;
            rightNode = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->leftNode, data);
                    root->leftNode = cur;
                } else {
                    cur = insert(root->rightNode, data);
                    root->rightNode = cur;
               }

               return root;
           }
        }


    void count(Node *root)
    {
        if (root == nullptr)
        {
            cout << 0;
            return;
        }

        vector<int> levels;
        queue<Node*> que;
        Node* temp = nullptr;

        int items = 1;
        que.push(root);

        while (!que.empty())
        {
            items = que.size();

            levels.push_back(items);

            for (int i = 0; i < items; i++)
            {
                temp = que.front();

                que.pop();

                if (temp->leftNode != nullptr)
                {
                    que.push(temp->leftNode);
                }
                if (temp->rightNode != nullptr)
                {
                    que.push(temp->rightNode);
                }
            }

        }

        for (int i = 0; i < levels.size(); i++)
        {
            if (i == levels.size() - 1)
            {
                cout << levels[i];
                break;
            }

            cout << levels[i] << ';';
        }

    }


}; //End of Solution

int main() {
  
    Solution myTree;
    Node* root = NULL;
    
    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
	myTree.count(root);


    return 0;
}