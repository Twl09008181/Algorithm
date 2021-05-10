#include <iostream>
#include <string>
#include <utility>

struct data{
    data(std::string k,int v)//用string當作key,int 當作value 例如:名子:分數
        :key{k},val{v}{}
    std::string key;
    int val;
    bool operator==(const data&other)const{return key==other.key;}
    bool operator<(const data&other)const{return key<other.key;}
    bool operator>(const data&other)const{return key>other.key;}
};

std::ostream & operator<<(std::ostream&os,const data&d)
{
    os<<"key = "<<d.key<<" val = "<<d.val<<" ";
    return os;
}


struct AVL_node{
    
    AVL_node(data val)
        :value{val},height{0},bf{0},left{nullptr},right{nullptr}{}
    data value;
    int height;
    int bf;
    AVL_node *left,*right;
};


class AVL{
public:
    AVL()
    :root{nullptr}{}
    AVL&Insert(data val){std::cout<<"insert "<<val<<"\n";root = help_insert(root,val);return *this;}
    AVL&Delete(std::string key){std::cout<<"delete "<<key<<"\n";root = help_delete(root,key);return *this;}
    std::pair<bool,int> search(std::string key){return help_search(root,key);} //回傳bool:是否找到,int:val值

    void INORDER(){inorder(root);}
    void PREORDER(){preorder(root);}
private:
    void inorder(AVL_node*root);
    void preorder(AVL_node*root);

    std::pair<bool,int> help_search(AVL_node*cur,std::string key);
    AVL_node* help_delete(AVL_node*cur,std::string key);
    AVL_node* help_insert(AVL_node*cur,data val);
    AVL_node* RR(AVL_node*node);
    AVL_node* LL(AVL_node*node);
    AVL_node* adjust(AVL_node*node);
    AVL_node* remove_right_most(AVL_node*node,AVL_node**target);
    bool restate(AVL_node*node);
    bool imblance(AVL_node*node)const{return node->bf==-2||node->bf==2;}
    
    AVL_node* root;
};

AVL_node* AVL::remove_right_most(AVL_node*node,AVL_node**target)
{
    if(node->right)
    {
        node->right = remove_right_most(node->right,target);
        return node;
    }
    else{
        *target = node;
        return node->left;
    }
}
AVL_node* AVL::help_delete(AVL_node*cur,std::string key)
{
    if(!cur)
    {
        return nullptr;
    }
    else 
    {
        if(cur->value.key==key)
        {
            if(cur->left&&cur->right)//左子右子皆存在
            {
                AVL_node* replacer;
                remove_right_most(cur->left,&replacer);
                cur->value = replacer->value;
                delete replacer;
            }
            else if (cur->left)
            {
                AVL_node*tmp = cur;
                cur = cur->left;
                delete tmp;
            }
            else if(cur->right) 
            {
                AVL_node*tmp = cur;
                cur = cur->right;
                delete tmp;
            }
            else 
            {
                delete cur;
                cur = nullptr;
            }
        }
        else if(cur->value.key < key)
        {
            cur->right = help_delete(cur->right,key);
            if(restate(cur)&&imblance(cur))
                cur = adjust(cur);
        }
        else
        {
            cur->left = help_delete(cur->left,key);
            if(restate(cur)&&imblance(cur))
                cur = adjust(cur);
        }
        return cur;
    }
}
std::pair<bool,int> AVL::help_search(AVL_node*cur,std::string key)
{
    if(!cur)
    {
        return {false,-1};
    }
    else{
        if(cur->value.key==key)
            return {true,cur->value.val};
        else if(cur->value.key < key)
            return help_search(cur->right,key);
        else 
            return help_search(cur->left,key);
    }

}
AVL_node* AVL::help_insert(AVL_node*cur,data val)
{
    if(!cur)
    {
        return new AVL_node(val);
    }
    else{
        if(cur->value == val)return cur;

        else if (cur->value < val)
            cur->right = help_insert(cur->right,val);
        else 
            cur->left = help_insert(cur->left,val);
        
        if(restate(cur)&&imblance(cur))
            cur = adjust(cur);

        return cur;
    }
}

bool AVL::restate(AVL_node*node)
{
    int left_height = (node->left)? node->left->height : -1;
    int right_height = (node->right)? node->right->height : -1;
    node->height = std::max(left_height,right_height) + 1;
    node->bf = left_height - right_height;
    return true;
}
AVL_node* AVL::adjust(AVL_node*node)
{
    if(node->bf==-2)//右邊過重
    {
        if(node->right->bf==-1||node->right->bf==0)//RR  , 0 是由於刪除而產生的,這種情況用RR跟RL都可以,但RR比較有效率 
        {
            std::cout<<node->value.key<<" do a RR rotation! \n";
            node = RR(node);
        }
        else{//RL
            std::cout<<node->value.key<<" do a RL rotation! \n";
            node->right = (node->right);//先對node->right LL變成RR型
            node = RR(node);
        }
    }
    else if(node->bf==2)//左邊過重
    {
        if(node->left->bf==1||node->left->bf==0)
        {
            std::cout<<node->value.key<<" do a LL rotation! \n";
            node = LL(node);
        }
        else{
            std::cout<<node->value.key<<" do a LR rotation! \n";
            node->left = RR(node->left);//先對node->left RR變成LL型
            node = LL(node);
        }
    }
    return node;
}
AVL_node* AVL::RR(AVL_node*node)
{

    AVL_node *right = node->right;
    node->right = right->left;
    right->left = node;
    restate(node);
    restate(right);
    return right;
}
AVL_node* AVL::LL(AVL_node*node)
{
   
    AVL_node *left = node->left;
    node->left = left->right;
    left->right = node;
    restate(node);
    restate(left);
    return left;
}

void AVL::inorder(AVL_node*root)
{
    if(root)
    {
        inorder(root->left);
        std::cout<<root->value<<" ";
        inorder(root->right);
    }
}
void AVL::preorder(AVL_node*root)
{
    if(root)
    {
        std::cout<<root->value<<" ";
        preorder(root->left);
        preorder(root->right);
    }
}


void show_order( AVL&avl)
{
    avl.INORDER();std::cout<<"\n";
    avl.PREORDER();std::cout<<"\n";
}

int main()
{

    AVL avl;
    avl.Insert({"a",100}).Insert({"b",90}).Insert({"c",100}).Insert({"d",85}).Insert({"e",99}).Insert({"f",80});

    show_order(avl);
    
    avl.Delete("e").Delete("f");
    show_order(avl);

    

   
    

    return 0;
}
