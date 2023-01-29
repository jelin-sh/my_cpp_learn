#include <iostream>
#include <vector>
#include <numeric>

void foo1(const std::vector<int>& nums){
    int res = std::accumulate(nums.begin(),nums.end(),0,[](int a,int b){
        return a*b;
    });
    std::cout << "foo1: " << res << std::endl;
}

void foo2(const std::vector<int>& nums){
    std::string res = std::accumulate(std::next(nums.begin()),nums.end(),std::to_string(nums[0]),[](const std::string& a,int b){
        return a + ";" + std::to_string(b);
    });
    std::cout << "foo2: " << res << std::endl;
}

std::string foo3_operation(const std::string& a ,int b){
    return a + ";" + std::to_string(b);
}

void foo3(const std::vector<int>& nums){
    std::string res = std::accumulate(std::next(nums.begin()),nums.end(),std::to_string(nums[0]),foo3_operation);
    std::cout << "foo3: " << res << std::endl;
}

void print_vector(const std::vector<int>& nums){
    for (auto i : nums){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::vector<int> nums = {1,2,3,4,5};
    foo1(nums);
    foo2(nums);
    foo3(nums);
    print_vector(nums);
    return 0;
}
