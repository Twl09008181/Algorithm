#include <iostream>
#include <string>


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


TreeNode* Construct(int l,int r,std::string&pre,std::string&ino,int *cur = nullptr)
{
    if(cur==nullptr)
        cur = new int (-1);
    
    (*cur)++ ;

    char data = pre[*cur];
    TreeNode *root = new TreeNode(data);
    int pos = l;
    for(;pos <= r && ino[pos]!= data;pos++);

    if(pos!=l)
        root->left = Construct(l,pos-1,pre,ino,cur);
    if(pos!=r)
        root->right = Construct(pos+1,r,pre,ino,cur);

    return root;
}


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

int main()
{

    std::string Pre = "0136742589";
    std::string Ino = "6371402859";
    TreeNode*root = Construct(0,Pre.size()-1,Pre,Ino);

    
    Preorder(root);std::cout<<"\n";
    inorder(root);std::cout<<"\n";
    return 0;
}
