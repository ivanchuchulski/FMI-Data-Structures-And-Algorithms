  
//height of a binary tree

   int Max(int a, int b)
    {
        return a > b ? a : b;
    }
    int height(Node* root) 
    {
        //if we have no root, then it is -1, but if we have at least one Node, then we should return 0, so we add 1
        if (root == nullptr)
            return -1;
        
        return 1 + Max(height(root->left), height(root->right));
    }