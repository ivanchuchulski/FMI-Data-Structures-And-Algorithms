#include <iostream>
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

int NodesCount(Node* root)
{
    if (root == nullptr)
        return 0;
    
    return 1 + NodesCount(root->leftNode) + NodesCount(root->rightNode);
}

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



	void print(Node *root, vector<int>& nodes_count) 
    {
		if (root == nullptr)
            return;
        
        print(root->rightNode, nodes_count);
        print(root->leftNode, nodes_count);
        
        nodes_count.push_back(root->data);
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
    
 //   int nodes_num = NodesCount(root);
    vector<int> nodes;
	myTree.print(root, nodes);
    
    
    for(int i = 0; i < nodes.size(); i++)
    {
        if (i == nodes.size() - 1)
            cout << nodes[i];
        else
            cout << nodes[i] << ';';
    }
    
    return 0;
}
