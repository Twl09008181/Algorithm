#include <iostream>
#include <iomanip>

class queue;
class queue_node{
    friend class queue;
    friend std::ostream &operator<<(std::ostream&os,const queue&Q);
public:
    queue_node(int val,queue_node*next_node=nullptr)
        :data{val}, link{next_node}{}
private:
    int data;
    queue_node*link;
};


class queue{
    friend std::ostream &operator<<(std::ostream&os,const queue&Q);
public:
    queue()
        :front{nullptr},back{nullptr},size{0}
        {}

    bool IsEmpty()const{return front==nullptr;}

    int Back()const;
    int Front()const;
    int get_size()const{return size;}

    queue& push(int val);
    queue& pop();
private:
    queue_node *front;
    queue_node *back;
    int size;
};

int queue::Back()const{
    if(IsEmpty())
    {
        std::cout<<"queue is empty\n";
        return -1;
    }
    return back->data;            
}
int queue::Front()const
{
    if(IsEmpty())
    {
        std::cout<<"queue is empty\n";
        return -1;
    }   
    return front->data;
}
queue& queue::push(int val)
{   
    queue_node *new_node = new queue_node(val);
    if(IsEmpty())
    {
        front = new_node; 
    }
    else{
        back->link = new_node;
    }
    size++;
    back = new_node;
    return *this;
}

queue& queue::pop()
{
    if(IsEmpty())return *this;

    size--;
    queue_node*tmp = front;
    front = front->link;
    delete tmp;
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
    for(queue_node*ptr = Q.front;ptr;ptr=ptr->link)
    {
        os << ptr->data <<std::setw(5);
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
