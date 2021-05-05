#include "BST.h"



std::string  BST::Search(int key,TreeNode**parent,TreeNode**cur)
{
    *parent = nullptr;
    *cur = nullptr;

    if(_root==nullptr)
        return "tree is empty";
    
    *cur = _root;
    bool find = false;
    while(*cur&&!find)
    {
        if((*cur)->key==key){
            find = true;
        }
        else if ((*cur)->key > key)
        {
            *parent = *cur;
            *cur = (*cur)->left;
        }
        else {
            *parent = *cur;
            *cur = (*cur)->right;
        }
    }
    //if *cur is nullptr,then not found. 
    if(*cur)
        return (*cur)->data;
    else 
        return "not found";
}

bool BST::InsertNode(int key,std::string data)
{
    TreeNode*parent=nullptr,*target=nullptr;
    Search(key,&parent,&target);

    if(parent==nullptr)//tree is empty
    {    
        _root = new TreeNode(key,data);
        return true;
    }
    if(target)return false;//already in 

    if(key > parent->key)
        parent->right = new TreeNode(key,data);
    else 
        parent->left = new TreeNode(key,data);

    return true;
}

bool BST::DeleteNode(int key)
{
    TreeNode*parent=nullptr,*target=nullptr;
    Search(key,&parent,&target);
    if(target==nullptr)//not found
    {    
        return false;
    }

    TreeNode*replacer=nullptr,*replacer_parent=target;

    if(target->left)
    {
        replacer = target->left;
        search_largest(&replacer_parent,&replacer);
    }
    else if(target->right){//直接用,因為自己也是BST
        replacer = target->right;
    }

    if(replacer==nullptr)//target is leaf node
    {
        if(parent)//target is not root
        {
            if(parent->key < key)
                parent->right = nullptr;
            else 
                parent->left = nullptr;
        }
        else {//delete root
            _root = nullptr;
        }

        delete target;
        return true;
    }


    //step 1 
    if(replacer_parent->key < replacer->key)
    {
        replacer_parent->right = replacer->left;
    }
    else 
    {
        replacer_parent->left = replacer->right;
    }

    //step 2 
    replacer->left = target->left;
    replacer->right = target->right;


    //step3
    if(parent)//target is not root
    {
        if(parent->key < key)
            parent->right = replacer;
        else 
            parent->left = replacer;
    }
    else{//target is root
        _root = replacer;
    }




    return true;
}


void BST::search_largest(TreeNode**parent,TreeNode**cur)
{
    while((*cur)->right)
    {
        *parent = *cur;
        *cur = (*cur)->right;
    }
}
//show 
void inorder(TreeNode* root,std::ostream&os)
{
    if(root)
    {
        inorder(root->left,os);
        os<<root->data<<" ";
        inorder(root->right,os);
    }
}
std::ostream& operator<<(std::ostream&os,const BST&bst)
{
    inorder(bst._root,os);
    return os;
}



int main()
{
    TreeNode*p,*c;
    BST my_BST;
    my_BST.InsertNode(20,"20");
    my_BST.InsertNode(10,"10");
    my_BST.InsertNode(7,"7");
    my_BST.InsertNode(12,"12");
    my_BST.InsertNode(4,"4");
    my_BST.InsertNode(9,"9");
    my_BST.InsertNode(8,"8");

    std::cout <<my_BST<<std::endl;

    my_BST.DeleteNode(20);
    std::cout <<my_BST<<std::endl;

    my_BST.DeleteNode(10);
    std::cout <<my_BST<<std::endl;

    my_BST.DeleteNode(7);
    std::cout <<my_BST<<std::endl;


    my_BST.DeleteNode(4);
    std::cout <<my_BST<<std::endl;


    my_BST.InsertNode(20,"20");
    std::cout <<my_BST<<std::endl;
    my_BST.InsertNode(40,"40");
    std::cout <<my_BST<<std::endl;
    my_BST.InsertNode(10,"10");
    std::cout <<my_BST<<std::endl;
    return 0;
}


