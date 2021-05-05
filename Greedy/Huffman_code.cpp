#include <vector>
#include <iostream>
#include <algorithm>
struct Alphabet{
    
    Alphabet(char d='z',int f=0)
        :data{d},frequency{f}{}
    char data;
    int frequency;


    bool operator<=(const Alphabet&rhs){return frequency<=rhs.frequency;}
    bool operator<(const Alphabet&rhs){return frequency<rhs.frequency;}
};




struct TreeNode{

    TreeNode(Alphabet d={'z',0},TreeNode*l = nullptr,TreeNode*r = nullptr)
        :data{d},left{l},right{r}
        {}

    Alphabet data;
    TreeNode*left,*right;
};



class min_Heap{
public:
    min_Heap(int c)
        :capacity{c},n{0}
    {
        heap = new TreeNode* [capacity];
    }
    ~ min_Heap()
    {
        delete [] heap;
    }

    void insert(TreeNode*data);
    TreeNode* extract_min();
    void pop();
    int size(){return n;}
private:
    void heapify(int i);
    TreeNode **heap;
    int capacity;
    int n;
};



void min_Heap::heapify(int i)
{

    TreeNode* node = heap[i];
    while(i*2+1 < n)
    {
        int suc = i*2+1;
        if(suc+1<n && heap[suc+1]->data < heap[suc]->data)
            suc+=1;
        
        if(heap[i]->data<=heap[suc]->data)break;


        heap[i] = heap[suc];
        i = suc;
    }
    heap[i] = node;
}

void min_Heap::insert(TreeNode* insert_node)
{
    if(n==capacity)
    {
        TreeNode** new_heap =  new TreeNode*[capacity*2];
        for(int i = 0;i<capacity;i++)
            new_heap[i] = heap[i];
        delete []heap;
        capacity*=2;
        heap = new_heap;
    }


    int i = n;
    while(i!=0&& insert_node->data < heap[(i-1)/2]->data )
    {
        heap[i] = heap[(i-1)/2];
        i = (i-1)/2;
    }
    heap[i] = insert_node;
    n++;
}


TreeNode* min_Heap::extract_min()
{
    if(n==0)return nullptr;


    TreeNode *min_node = heap[0];
    

    return min_node;
}

void min_Heap::pop()
{
    
    heap[0] = heap[--n];
    
    heapify(0);
}

TreeNode * Huffman(std::vector<Alphabet>&data)
{
    if(data.size()==0)return nullptr;

    min_Heap Q(data.size());

    for(int i = 0;i<data.size();i++)
    {
        Q.insert(new TreeNode (data[i]));
    }

    while(Q.size()>1)
    {
        
        TreeNode * z = new TreeNode();
        TreeNode *l = Q.extract_min();Q.pop();
        TreeNode *r = Q.extract_min();Q.pop();
        z->data.frequency = l->data.frequency+r->data.frequency;
        z->left = l;
        z->right = r;

        Q.insert(z);

    }

    return Q.extract_min();
}



void Inorder(TreeNode*root,std::string str="")
{
    if(root)
    {
        Inorder(root->left,str+"0");
        
        if(root->data.data!='z')
            std::cout<<root->data.data<<" : "<<str<<"\n";
        
        Inorder(root->right,str+"1");
    }
}

void Preorder(TreeNode*root)
{
    if(root)
    {
        std::cout<<root->data.data<<" ";
        Preorder(root->left);
        Preorder(root->right);
    }
}

int main()
{

    std::vector<Alphabet>alphabet = 
    {
        {'a',45},
        {'b',13},
        {'c',12},
        {'d',16},
        {'e',9},
        {'f',5}
    };

    auto ans = Huffman(alphabet);


    Inorder(ans);
    std::cout<<"\n";

   

}
