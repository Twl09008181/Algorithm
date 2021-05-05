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
    void Print_List()const{print(head);}
    void Push_front(int val);
    void Push_back(int val){push_back(head,val);}
    void Delete(int val){head = delete_node(head,val);}
    void Clear(){clear(head);head=nullptr;}
    void Reverse(){reverse(nullptr,head);}
private:
    void print(ListNode*cur)const;
    ListNode* push_back(ListNode*cur,int val);
    ListNode *delete_node(ListNode*cur,int val);
    void reverse(ListNode*last,ListNode*cur);
    void clear(ListNode*cur);
    ListNode *head; 
};


void Linked_list::print(ListNode*cur)const
{   
    if(cur)
    {
        std::cout << cur->data <<" ";
        print(cur->link);
    }
}


void Linked_list::Push_front(int val)
{
    head = new ListNode(val, head);
}

ListNode* Linked_list::push_back(ListNode*cur,int val)
{   
    if(!cur){
        cur = new ListNode(val);
    }
    else{
        cur->link = push_back(cur->link,val);
    }
    return cur;
}

ListNode *Linked_list::delete_node(ListNode*cur,int val)
{
    if(cur)
    {
        if(cur->data == val)
        {
            ListNode *tmp = cur->link;
            delete cur;
            cur = nullptr;
            return tmp;
        }
        else {
            cur->link = delete_node(cur->link,val);
        }
    }
    return cur;
}

void Linked_list::clear(ListNode*cur)
{
    if(cur)
    {
        clear(cur->link);
        delete cur;
        cur = nullptr;
    }
}

void Linked_list::reverse(ListNode*last,ListNode*cur)
{   
    if(!cur)//到盡頭
    {
        head = last;
    }
    else{
        reverse(cur,cur->link);
        cur->link = last;
    }
}


int main()
{
    Linked_list Lst;


    while(1)
    {
        int op;
        std::cin >> op;

        switch (op)
        {
        case 0:
            exit(0);
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

    return 0;
}
