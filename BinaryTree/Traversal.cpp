
#include <iostream>
#include <stack>
#include <string>
#include <map>
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



//前序
void PreOrder(TreeNode*root)
{
    
    std::stack<TreeNode*>S;
    S.push(root);

    while(!S.empty())
    {
        TreeNode* node = S.top();S.pop();
        if(node){
            std::cout<<node->data<<" ";
            S.push(node->right);
            S.push(node->left);
        }
    }
    std::cout<<std::endl;
}


void Inorder(TreeNode*root)
{
    
    std::map<TreeNode*,bool>record;
    std::stack<TreeNode*>stack;
    stack.push(root);

    while(!stack.empty())
    {
        TreeNode*cur = stack.top();stack.pop();
        if(cur&&record.find(cur)==record.end())
        {
            stack.push(cur->right);
            stack.push(cur);
            stack.push(cur->left);
            record[cur] = true;
        }
        else if (cur)
        {
            std::cout<<cur->data<<" ";
        }
    }
    std::cout<<"\n";

}


//LVR
void Inorder2(TreeNode*root)
{
    
    std::stack<TreeNode*>stack;

    TreeNode *cur = root;
    while(1)
    {
        for(;cur;cur = cur->left)
            stack.push(cur);
        

        if(!stack.empty())
            break;
        
        cur = stack.top();stack.pop();
        std::cout<<cur->data<<" ";
        cur = cur->right;
    }   

    std::cout<<"\n";
}



int main()
{

    std::string Pre = "0136742589";
    std::string Ino = "6371402859";
    TreeNode*root = Construct(0,Pre.size()-1,Pre,Ino);


    PreOrder(root);
    Inorder(root);
    return 0;
}
