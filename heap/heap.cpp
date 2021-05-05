#include <string>
#include <iostream>

class heap;
class data{
    friend class heap;
    friend bool operator<=(const data&d1,const data&d2);
    friend bool operator<(const data&d1,const data&d2);
public:
    data() = default;
    data(int k,std::string str)
        :key{k},val{str}{}
private:
    int key;
    std::string val;
};

bool operator<(const data&d1,const data&d2)
{
    return d1.key < d2.key;
}
bool operator<=(const data&d1,const data&d2){
    return d1.key <= d2.key;
}


class heap//min heap
{
public:
    heap()
        :capacity{10},n{0}
    {
        H = new data[10];
    }

    bool IsEmpty()const{return n==0;}

    std::string  extract_min();
    heap& pop();
    heap& push(data d);

    void print_heap()
    {   
        std::cout<<"size = " << n<<"\n";
        int change_line = 2;
        for(int i = 1;i <= n;i++)
        {   
            if(i==change_line)
            {
                std::cout<<"\n";
                change_line*=2;
            }
            std::cout<<H[i].val<<" ";
        }
        std::cout<<"\n";
    }
private:
    data *H;
    int capacity;
    int n;//定義n是最後valid的元素index
};

heap& heap::pop()
{
    if(IsEmpty())
    {
        std::cout<<"is empty\n";
        return *this;
    }
    int i = 1;//root
    H[i] = H[n--];//use last node to adjust heap

    while(i*2 <= n )//not leaf
    {
        int suc = i*2;
        if(suc+1 <= n && H[suc+1] < H[suc])
        {
            suc+=1;
        }

        if(H[i] <= H[suc])//調整好了
            break;

        std::swap(H[i],H[suc]);
        i = suc;
    }
    return *this;
}

heap& heap::push(data d)
{
    if(n+1==capacity)
    {
        data *new_H = new data[capacity*2];

        for(int i = 1;i <= n;i++)
        {
            new_H[i] = H[i];
        }
        delete [] H;
        H = new_H;
        capacity*=2;
    }



    H[++n] = d;
    //往上挑戰    
    int i = n;
    while( i/2 > 0 && H[i] < H[i/2])//注意是d < H[i/2] 不是H[i] < H[i/2] 因為H[i]沒被改過
    {
        //H[i] = H[i/2];
        std::swap(H[i],H[i/2]);
        i/=2;
    }
    // H[i] = d;
    return *this;
}

std::string heap::extract_min()
{
    if(IsEmpty())
    {
        std::cout<<"empty\n";
        return {"empty"};
    }
    return H[1].val;
}



int main()
{
    heap H;

    int op = 0;
    while(op!=-1)
    {
        std::cin>>op;

        switch (op)
        {
            case 0:{
                op = -1;
                break;
            }
            case 1:{
                int val;
                std::cin>>val;
                H.push({val,std::to_string(val)});
                break;
            }
            case 2:{
                H.pop();
                break;
            }
            case 3:{
                std::cout<<"min = " << H.extract_min()<<"\n";
                break;
            }
            case 4:{
                H.print_heap();
                break;
            }
        default:
            break;
        }



    }
    
    return 0;
}
