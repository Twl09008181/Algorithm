#include <iostream>
#include <vector>
#include <algorithm>


void heapify(std::vector<int>&nums,int i,int n)
{
    int val = nums.at(i);

    while(i*2<=n)
    {
        int suc = i*2;
        if(suc+1<=n&&nums.at(suc) < nums.at(suc+1))suc++;

        if(val >= nums.at(suc))break;

        nums.at(i) = nums.at(suc);
        i = suc;
    }
    nums.at(i) = val;
}

void heap_sort(std::vector<int>&nums)
{
    int n = nums.size() - 1;
    for(int i = n / 2;i >= 1; i--)//use nums[1] as root
    {
        heapify(nums,i,n);
    }

    

    //開始將root跟n交換,並做heapify
    for(int i = n;i>1;i--)
    {
        std::swap(nums.at(i),nums.at(1));
        heapify(nums,1,--n);
    }
}



int main()
{
    std::vector<int>nums = {0,100,30,110,120,40,150,5};//想排成遞增,用max_heap
    
    heap_sort(nums);
    std::for_each(nums.begin(),nums.end(),[](int v){std::cout<<v<<" ";});
    return 0;
}
