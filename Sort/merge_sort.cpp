#include "random.hpp"


#include <iostream>

void merge(std::vector<int>&nums,int l1_s,int l1_e,int l2_e)//l1 = [l1_s,l1_e),l2 = [l1_e,l2_e)
{
    std::vector<int>tmp;tmp.reserve(l1_e-l1_s+1);
    std::copy(nums.begin()+l1_s,nums.begin()+l1_e,std::back_inserter(tmp));

    int index = l1_s;
    int l1_i = 0;
    int l2_i = l1_e;
    while(l1_i < tmp.size() &&l2_i < l2_e)
    {
        if(tmp.at(l1_i) <= nums.at(l2_i))
        {
            nums.at(index++) = tmp.at(l1_i++);
        }
        else{
            nums.at(index++) = nums.at(l2_i++);
        }
    }

    while(l1_i < tmp.size())
        nums.at(index++) = tmp.at(l1_i++);
    while(l2_i < l2_e)
        nums.at(index++) = nums.at(l2_i++);
}

void merge_sort(std::vector<int>&nums,int l,int r)//[l,r)
{
    if(l < r - 1)
    {
        int mid = (l + r) / 2;
        merge_sort(nums,l,mid);//[l,mid)
        merge_sort(nums,mid,r);//[mid,r)
        merge(nums,l,mid,r);
    }
}
 


int main()
{

    std::vector<int>nums = get_rand_nums(10);
    std::for_each(nums.begin(),nums.end(),[](int n){std::cout<<n<<" ";});std::cout<<std::endl;

    merge_sort(nums,0,nums.size());
    std::for_each(nums.begin(),nums.end(),[](int n){std::cout<<n<<" ";});std::cout<<std::endl;

    return 0;
}
