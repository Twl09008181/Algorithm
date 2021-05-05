#include <iostream>
#include <vector>
#include <algorithm>
#include "random.hpp"

void heapify(std::vector<int>&nums,int i,int n)
{
    int val = nums.at(i);

    while(i*2+1<=n)
    {
        int suc = i*2+1;
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
    for(int i = (n-1)/ 2;i >= 0; i--)//use nums[0] as root
    {
        heapify(nums,i,n);
    }


    //開始將root跟n交換,並做heapify
    for(int i = n;i > 0;i--)
    {
        std::swap(nums.at(i),nums.at(0));
        heapify(nums,0,--n);
    }
}



int main()
{
    std::vector<int>nums = get_rand_nums(10);
    heap_sort(nums);
    std::for_each(nums.begin(),nums.end(),[](int v){std::cout<<v<<" ";});
    return 0;
}
