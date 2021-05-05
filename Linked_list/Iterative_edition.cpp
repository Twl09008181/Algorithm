#include <iostream>

class Linked_list;

class ListNode{
    friend class Linked_list;
public:
    ListNode(int d,ListNode*l=nullptr)
        :data{d}, link{l}
    {}
private:
    int data;
    ListNode *link;
};


class Linked_list{
    
public:
    Linked_list(ListNode*h=nullptr)
        : head{h}{}
    
    Linked_list(const Linked_list&other)
    {
        std::cout << "copy constructor\n";
        help_copy(&head,other.head);
    }

    Linked_list& operator=(const Linked_list&other)
    {
        std::cout<<"copy assignment" << std::endl;

        if(&other==this)return *this;

        while(head)
        {
            ListNode*tmp = head;
            head = head->link;
            delete tmp;
            
        }

        help_copy(&head,other.head);
        return *this;
    }

    ~Linked_list()
    {
        std::cout<<"destructor" << std::endl;
        while(head)
        {
            ListNode*tmp = head;
            head = head->link;
            delete tmp;
        }
    }
    void Print_List()const;
    void Push_front(int val);
    void Push_back(int val);
    void Delete(int val);
    void Clear();
    void Reverse();
private:
    void help_copy(ListNode**cur,ListNode*other)
    {
        if(other){
            *cur = new ListNode(other->data);
            help_copy(&((*cur)->link),other->link);
        }
    }
    ListNode *head; 
};


void Linked_list::Print_List()const
{
    for(auto ptr = head;ptr;ptr=ptr->link)
    {
        std::cout << ptr->data << " ";
    }
}

void Linked_list::Push_front(int val)
{
    head = new ListNode(val, head);
}

void Linked_list::Push_back(int val)
{
    //可以用dummy node,但這邊用別的方法
    ListNode ** ptr = &head;
    while(*ptr)
        ptr = &((*ptr)->link);

    *ptr = new ListNode(val);
}

void Linked_list::Delete(int val)
{
    //需要哨兵
    ListNode *parent = nullptr,*cur = head;

    while(cur && cur->data != val)
    {
        parent = cur;
        cur = cur->link;
    }

    if(cur==nullptr)//not found
        ;
    else if (cur==head)
    {
        head = head->link;
    } 
    else {
        parent->link = cur->link;
    }

    delete cur;
}

void Linked_list::Clear()
{
    while(head)
    {
        ListNode*tmp = head->link;
        delete head;
        head = tmp;
    }
}

void Linked_list::Reverse()
{
    if(!head || !head->link)
        return ;


    ListNode *cur = head,*prev = nullptr,*suc = nullptr;
    while(cur)
    {
        suc = cur->link;
        cur->link = prev;
        prev = cur;
        cur = suc;
    }
    head = prev;
}


int main()
{
    Linked_list Lst;

    int op = 0;
    while(op != -1)
    {
        std::cin >> op;

        switch (op)
        {
        case 0:
            op = -1;
            break;

        case 1:{
            std::cout <<"enter val to push_front" << std::endl;
            int val;
            std::cin >> val;
            Lst.Push_front(val);
            break;
        }
        case 2:{
            std::cout <<"enter val to push_back" << std::endl;
            int val;
            std::cin >> val;
            Lst.Push_back(val);
            break;
        }
        case 3:{
            std::cout <<"enter val to delete" << std::endl;
            int val;
            std::cin >> val;
            Lst.Delete(val);
            std::cout <<"delete : " << val << std::endl;
            break;
        }
        case 4:{
            Lst.Clear();
            break;
        }
        case 5:{
            Lst.Print_List();
            std::cout << std::endl;
            break;
        }
        case 6:{
            Lst.Reverse();
            break;
        }
        default:
            break;
        }
    }


    Linked_list LST1;
    LST1.Push_front(10);LST1.Push_front(50);LST1.Push_front(20);LST1.Push_front(30);
    LST1.Print_List();std::cout << std::endl;

    Linked_list LST2{LST1};
    LST2.Print_List();std::cout << std::endl;

    LST2.Delete(50);
    LST1.Print_List();std::cout << std::endl;
    LST2.Print_List();std::cout << std::endl;

    Linked_list LST3;
    LST3 = LST2;
    LST2.Print_List();std::cout << std::endl;
    LST3.Print_List();std::cout << std::endl;

    LST3.Push_back(100);

    LST2.Print_List();std::cout << std::endl;
    LST3.Print_List();std::cout << std::endl;
    return 0;
}
