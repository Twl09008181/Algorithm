#include <utility>
#include <iostream>
#include <string>
struct TreeNode{
    TreeNode(int k,std::string d,TreeNode *l = nullptr,TreeNode*r =nullptr)
        :key{k}, data{d},left{l}, right{r}{}
    int key;
    TreeNode *left,*right;
    std::string data;
};



class BST{
    friend std::ostream& operator<<(std::ostream&os,const BST&bst);
public:
    BST():_root{nullptr}{}
    BST(TreeNode*root):_root{root}{}

    std::string  Search(int key,TreeNode**parent=nullptr,TreeNode**cur=nullptr);
    bool InsertNode(int key,std::string data);
    bool DeleteNode(int key);
    ~ BST()
    {
        //destructor
    }
private:
    void search_largest(TreeNode**parent,TreeNode**cur);
    std::pair<TreeNode*,bool> helper_search(int key,TreeNode*cur);
    TreeNode *_root;
};




