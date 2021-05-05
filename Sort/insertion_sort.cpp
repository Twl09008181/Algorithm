#include "random.hpp"
#include <iostream>


bool increasing(int a,int b){return a<=b;}
bool decreasing(int a,int b){return a>=b;}

void insertion_sort(std::vector<int>&nums,decltype(increasing)*cmp)
{
    for(int i = 1;i < nums.size();i++)
    {
        int tmp = nums.at(i);
        int j = i-1;
        for(;j >=0 && cmp(tmp,nums.at(j)); j--)//第j個元素不滿足,代表tmp要擺在j+1的位置
        {
            nums.at(j+1) = nums.at(j); 
        }
        nums.at(j+1) = tmp;
    }
}


int main()
{
    std::vector<int>nums = get_rand_nums(10);

    std::for_each(nums.begin(),nums.end(),[](int n){std::cout<<n<<" ";});std::cout<<std::endl;
    insertion_sort(nums,increasing);
    std::for_each(nums.begin(),nums.end(),[](int n){std::cout<<n<<" ";});std::cout<<std::endl;
    insertion_sort(nums,decreasing);
    std::for_each(nums.begin(),nums.end(),[](int n){std::cout<<n<<" ";});std::cout<<std::endl;
    return 0;
}
