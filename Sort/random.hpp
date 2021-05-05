#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <ctime>
std::vector<int> get_rand_nums(int n)
{
    std::default_random_engine generator(time(NULL));
    std::uniform_int_distribution<int> dis(0,100);

    std::vector<int>nums;nums.reserve(n);
    std::generate_n(std::back_inserter(nums),n,[&](){return dis(generator);});
    return nums;
}
