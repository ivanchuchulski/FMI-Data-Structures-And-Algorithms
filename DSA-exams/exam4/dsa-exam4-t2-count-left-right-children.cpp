#include <iostream>

using namespace std;

struct NodesCount
{
    int left;
    int right;
};

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


	void leftRight(Node *root, NodesCount& nodes) 
    {
        if (root == nullptr)
            return;
        
        leftRight(root->leftNode, nodes);
        
        if (root->leftNode != nullptr)
            nodes.left++;
        
        if (root->rightNode != nullptr)
            nodes.right++;
        

        leftRight(root->rightNode, nodes);
        
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

    NodesCount counts {0, 0};
    
	myTree.leftRight(root, counts);
    
    cout << '[' << counts.left << ',' << counts.right << ']';
    return 0;
}
