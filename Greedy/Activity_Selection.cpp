

#include <vector>
#include <iostream>
#include <algorithm>

struct activity{
    activity(int s,int f)
        :start{s},finish{f}{}
    int start;
    int finish;
};

bool increasing_finish(const activity&a1,const activity&a2)
{
    return a1.finish <= a2.finish;
}


std::vector<int> activity_selection(std::vector<activity>&A)
{
    if(A.size()==0)return {};

    std::sort(A.begin(),A.end(),increasing_finish);
    
    std::vector<int>Ans;Ans.reserve(A.size());

    int last_f = A[0].start;

    for(int i = 0;i<A.size();i++)
    {
        if(A[i].start>=last_f)
        {
            Ans.push_back(i);
            last_f = A[i].finish;
        }
    }
    return Ans;
}

int main()
{

    std::vector<activity>A = {
        {1,4},
        {3,5},
        {0,6},
        {5,7},
        {3,8},
        {5,9},
        {6,10},
        {8,11},
        {8,12},
        {9,13},
        {12,14}
    };
    
    auto ans = activity_selection(A);

    for(auto a:ans)
    {
        std::cout<<"a"<<a+1<<" ";
    } 

    return 0;
}
