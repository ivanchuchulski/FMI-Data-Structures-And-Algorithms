#include <algorithm>

struct Pair
{
    int level;
    int data;
};

void width(Node *root, int &maxi, int &mini, int hd){
    if(root==NULL)
        return;
    
    maxi=max(hd,maxi);
    mini=min(hd,mini);
    
    width(root->left, maxi, mini, hd-1);
    width(root->right, maxi, mini, hd+1);
}

void printTopViewSortedUtil(Node *root, int hd, int currentLevel, Pair *A, int N)
{
    
    if(root==NULL)
        return;
    
    if(currentLevel < A[hd-N].level)
    {
        A[hd-N].level = currentLevel;
        A[hd-N].data = root->data;
    }
    
    printTopViewSortedUtil(root->left, hd-1, currentLevel+1, A, N);
    printTopViewSortedUtil(root->right, hd+1, currentLevel+1, A, N);
    
}

void topView(Node *root)
{
    int max=0, min=0, hd=0;
    width(root, max, min, hd);
    
    int N = max - min + 1;
        
    Pair* A = new Pair[N];
    for(int i=0; i<N; i++)
    {
        A[i].level=A[i].data=INT_MAX;
    }
    printTopViewSortedUtil(root, hd, 0, A, min);

    for(int i=0; i<N; i++)
    {
        cout<<A[i].data<<" ";
    }
   
}