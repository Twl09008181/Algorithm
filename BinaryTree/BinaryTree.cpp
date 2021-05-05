#include <iostream>



struct TreeNode{

public:
    TreeNode(char v,TreeNode *l = nullptr,TreeNode *r = nullptr)
        : left{l},right{r},data{v}
    {
        
    }
    ~TreeNode()
    {
        delete left;
        delete right;
    }

    char data;
    TreeNode *left,*right;
};




void inorder(TreeNode*root)
{
    if(root)
    {
        inorder(root->left);
        std::cout << root->data<<" ";
        inorder(root->right);
    }
}

void Preorder(TreeNode*root)
{
    if(root)
    {
        std::cout <<root->data<<" ";
        Preorder(root->left);
        Preorder(root->right);
    }
}
void PostOrder(TreeNode*root)
{
    if(root)
    {
        
        PostOrder(root->left);
        PostOrder(root->right);
        std::cout <<root->data<<" ";
    }
}

int main()
{

    TreeNode *E = new TreeNode('E');
    TreeNode *D = new TreeNode('D',nullptr,E);
    TreeNode *C = new TreeNode('C');
    TreeNode *B = new TreeNode('B',nullptr,C);
    TreeNode *A = new TreeNode('A',D,B);
    TreeNode *root = new TreeNode('R',A);

    inorder(root);std::cout<<"\n";
    Preorder(root);std::cout<<"\n";
    PostOrder(root);std::cout<<"\n";


    return 0;
}


