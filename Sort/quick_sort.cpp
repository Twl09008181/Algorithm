#include "random.hpp"
#include <iostream>


bool increasing(int a,int b){return a < b;}
bool decreasing(int a,int b){return a > b;}
void quick(std::vector<int>&nums,int l,int r,bool(*cmp)(int,int));
void quick_sort(std::vector<int>&nums,bool(*cmp)(int,int))
{
    quick(nums,0,nums.size()-1,cmp);
}

void quick(std::vector<int>&nums,int l,int r,bool(*cmp)(int,int))
{
    if(l < r){
        int pivot = nums.at(l);
        int left = l + 1;
        int right = r;
        while(left < right)
        {
            while(cmp(nums.at(left),pivot)&&left<right)
            {
                left++;
              
            }
            while(cmp(pivot,nums.at(right)))
            {
               
                right--;
            }
            if(left<right)
                std::swap(nums.at(left),nums.at(right));


            
        }
        std::swap(nums.at(l),nums.at(right));

        quick(nums,l,right-1,cmp);
        quick(nums,right+1,r,cmp);
    }
}

int main()
{
    std::vector<int>nums = get_rand_nums(10);

    std::for_each(nums.begin(),nums.end(),[](int n){std::cout<<n<<" ";});std::cout<<std::endl;
    quick_sort(nums,decreasing);
    std::for_each(nums.begin(),nums.end(),[](int n){std::cout<<n<<" ";});std::cout<<std::endl;
    quick_sort(nums,increasing);
    std::for_each(nums.begin(),nums.end(),[](int n){std::cout<<n<<" ";});std::cout<<std::endl;

    return 0;
}
