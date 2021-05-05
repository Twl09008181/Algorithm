
#include <iostream>
#include <iomanip>

class Stack;
class Stack_node{
    friend class Stack;
    friend std::ostream& operator<<(std::ostream& os, const Stack&S);
public:
    Stack_node(int val,Stack_node*next_node=nullptr)
        :data{val}, link{next_node}
        {}
private:
    int data;
    Stack_node*link;
};

class Stack{
    friend std::ostream& operator<<(std::ostream& os, const Stack&S);
    friend void swap(Stack&s1,Stack&s2);
public:
    Stack()
        : top{nullptr},size{0}
        {}
    //--------------------------------------------copy member------------------------------------------------------------------------
    Stack(Stack&other)
        :size{other.size},top{nullptr}
    {
        std::cout <<"copy constructor\n";
        Stack_node** trav = &top;
      
        for(Stack_node*ptr = other.top;ptr;ptr=ptr->link)
        { 
            *trav = new Stack_node(ptr->data);
            trav = &((*trav)->link);
        }


        //dummy node 方法
        // top = new Stack_node(0);
        // Stack_node*dummy = top;
        // for(Stack_node*ptr = other.top;ptr;ptr=ptr->link)
        // {
        //     top->link = new Stack_node(ptr->data);
        //     top = top->link;
        //     //*trav = new Stack_node(ptr->data);
        //     //trav = &((*trav)->link);
        // }
        // top = dummy->link;
        // delete dummy;
    }

    Stack& operator=(const Stack&other)
    {
        if(&other==this)return *this;

        size = other.size;

        Stack_node** trav = &top;
        for(Stack_node*ptr = other.top;ptr;ptr=ptr->link)
        { 
            *trav = new Stack_node(ptr->data);
            trav = &((*trav)->link);
        }
        return *this;

    }

    ~Stack()
    {
        std::cout <<"destructor \n";
        //跟linked_list一樣
        while(top)
        {
            Stack_node*tmp = top;
            top = top->link;
            delete tmp;
        }
    }
    //--------------------------------------------copy member------------------------------------------------------------------------

    bool IsEmpty()const{return top==nullptr;}
    int Top()const{return top->data;}
    int Size()const{return size;}
    Stack& Push(int val);
    Stack& Pop();
private:
    Stack_node *top;
    int size;
};


Stack& Stack::Pop()
{
    if(IsEmpty())return *this ;
    Stack_node *tmp = top;
    top = top->link;
    delete tmp;
    size--;
    return *this;
}

Stack& Stack::Push(int val)
{
    top = new Stack_node(val,top);
    size++;
    return *this;
}   

 
 

std::ostream& operator<<(std::ostream& os, const Stack&S)
{
    os <<" stack size : " << S.Size() <<" \n"; 
    
    for(Stack_node*ptr = S.top;ptr;ptr=ptr->link)    
    {
        os <<"|"<<std::setw(5)<< ptr->data << std::setw(5)<<"|\n";
    }
    os <<"----------";
    return os ;
}
void swap(Stack&s1,Stack&s2)
{
    std::cout <<"swap!!" << std::endl;
    using std::swap;
    swap(s1.top,s2.top);
    swap(s1.size,s2.size);
}

int main()
{

    Stack S;
    int op = 0;
    while(op!=-1){
        
        
        std::cin >> op;
        switch (op)
        {
            case 0:
            {
                op = -1;
                break;
            }
            case 1:
            {
                int val;
                std::cin >>val;
                S.Push(val);
                break;
            }
            case 2:
            {
                S.Pop();
                break;
            }
            case 3:
            {
                if(!S.IsEmpty())
                    std::cout << "top = " << S.Top()<<"\n";
                else 
                    std::cout <<"Stack is empty" << "\n";
                break;
            }
            case 4:
            {
                std::cout << S << std::endl;
                break;
            }
            default:
                break;
        }
    }

    
    std::cout <<"copy member test \n";
    Stack S1;
    S1.Push(10).Push(20).Push(30);
    Stack S2{S1};

    std::cout << "S1 = " << S1 << "\n";
    std::cout << "S2 = " << S2 << "\n";
    S1.Pop();
    std::cout << "S1 = " << S1 << "\n";
    std::cout << "S2 = " << S2 << "\n";
    S2.Push(100).Push(500);
    std::cout << "S1 = " << S1 << "\n";
    std::cout << "S2 = " << S2 << "\n";
    

    Stack S3;
    S3 = S2;
    std::cout << "S2 = " << S2 << "\n";
    std::cout << "S3 = " << S3 << "\n";
    S3.Push(1000);
    std::cout << "S2 = " << S2 << "\n";
    std::cout << "S3 = " << S3 << "\n";
    

    Stack array1[] = {S1};
    Stack array2[] = {S2};
    std::swap(array1,array2);//call customized swap.
     
    return 0;
}

