
#include <iostream>
#include <iomanip>
class Stack{
    friend std::ostream& operator<<(std::ostream& os, const Stack&S);
    friend void swap(Stack&s1,Stack&s2);
public:
    Stack(int cap=1)
        :capacity{cap},top{-1}
    {
        s = new int [capacity];
    }

    //--------------------------------------------copy member------------------------------------------------------------------------
    Stack(const Stack& other)
        :capacity{other.capacity}, top{other.top}
    {
        std::cout<<"copy constructor\n";
        s = new int [capacity];
        for(int i = 0;i <= top; i++)
            s[i] = other.s[i];
    }
    Stack&operator=(const Stack&other)
    {
        std::cout <<"copy assignment\n"; 
        if(&other==this)return *this;

        delete []s;//釋放連續的記憶體需要用到[]
        
        capacity = other.capacity;
        top = other.top;
        s = new int [capacity];
        for(int i = 0;i <= top; i++)
            s[i] = other.s[i];

        return *this;
    }
    ~ Stack()
    {
        std::cout <<"destructor\n"; 
        delete []s;
    }
    //--------------------------------------------copy member------------------------------------------------------------------------


    bool IsEmpty()const{return top==-1;}
    int Top()const{return s[top];}
    int Size()const{return top+1;}

    Stack& Push(int val);
    Stack& Pop();
private:
    int *s;
    int top;//top是目前最上面的元素的index
    int capacity;//s的最大size
};


Stack& Stack::Pop()
{
    if(IsEmpty())return *this ;
    top--;
    return *this;
}

Stack& Stack::Push(int val)
{
    if(top + 1== capacity)
    {
        int *new_s = new int[capacity*2];
        for(int i = 0;i <capacity;i++)
            new_s[i] = s[i];

        delete [] s;
        s = new_s;
        capacity*=2;
    }
    s[++top] = val;
    return *this;
}   



std::ostream& operator<<(std::ostream& os, const Stack&S)
{
    os << "stack capacity : " << S.capacity << " stack size : " << S.Size() <<" \n"; 
    
    for(int i = S.top;i >= 0;i--)    
    {
        os <<"|"<<std::setw(5)<<S.s[i] << std::setw(5)<<"|\n";
    }
    os <<"----------";
    return os ;
}
void swap(Stack&s1,Stack&s2)
{
    std::cout <<"swap!!" << std::endl;
    using std::swap;
    swap(s1.top,s2.top);
    swap(s1.s,s2.s);
    swap(s1.capacity,s2.capacity);
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

