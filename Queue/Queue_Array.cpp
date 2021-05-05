#include <iostream>
#include <iomanip>



class queue{
    friend std::ostream &operator<<(std::ostream&os,const queue&Q);
public:
    queue()
        :back{0},front{0},capacity(1)
        {
            Q = new int[capacity];
        }

    bool IsEmpty()const{return back==front;}
    bool IsFull()const{return (back+1)%capacity==front;}
    int Back()const{
        if(IsEmpty())
        {
            std::cout<<"empty!\n";
            return -1;
        }

        int real_back = back-1;
        if(real_back < 0)
            real_back+=capacity;
        return Q[real_back];
    }
    int Front()const{
        
        if(IsEmpty())
        {
            std::cout<<"empty!\n";
            return -1;
        }
        return Q[front]; 
    }
    int get_size()const{
        int size = back - front;
        if(size < 0)size+=capacity;
        return size;
    }

    queue& push(int val);
    queue& pop();
private:
    int back,front;//front 都指向當前有效的位置,back則指向無效的位置(下一次添加的位置)
    int *Q;
    int capacity;
};


queue& queue::push(int val)
{   
    if(IsFull())
    {
        int *new_Q = new int [capacity*2];
        int size = get_size();
        for(int i = 0;i<size;i++)
        {
            new_Q[i] = Q[(front++)%capacity];
        }
        delete [] Q;
        Q = new_Q;
        front = 0;
        back = size;
        capacity*=2;
    }

    Q[back] = val;
    back = (back+1)%capacity;
    return *this;
}

queue& queue::pop()
{
    if(IsEmpty())return *this;
    front = (front+1)%capacity;
    return *this;
}


std::ostream &operator<<(std::ostream&os,const queue&Q)
{
    os<<"size = "<<Q.get_size()<<"\n";
    size_t size = Q.get_size();

    os<<"--------------";
    for(int i = 0;i<size;i++)
        os<<"-----";
    os<<"\n";
    
    os <<"front -> ";
    for(int i = Q.front;i!=Q.back;i=(i+1)%Q.capacity)
    {
        os << Q.Q[i] <<std::setw(5);
    }
    os << "<- back";
    os <<"\n";
    os<<"--------------";
    
    for(int i = 0;i<size;i++)
        os<<"-----";
    return os;
}

int main()
{

    queue Q;
    
    int op = 0;

    while(op!=-1)
    {
        std::cin >> op;
        switch (op)
        {
        case 0:{
            op = -1;
            break;
        }       
        case 1:{
            int val;
            std::cin>>val;
            Q.push(val);
            break;
        } 
        case 2:{
            Q.pop();
            break;
        }
        case 3:{
            std::cout<<"front = "<<Q.Front()<<"\n";
            break;
        }
        case 4:{
            std::cout<<"back = "<<Q.Back()<<"\n";
            break;
        }
        case 5:{
            std::cout<<Q<<std::endl;
            break;
        }
        default:
            break;
        }
    }


    return 0;
}
