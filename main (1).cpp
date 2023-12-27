#include <iostream>
#include <vector>
#include <cmath>

bool findPair(std::vector<int>& nums, int indexdiff, int valuediff) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i+1; j < nums.size(); j++) {
            if (abs(i - j) <= indexdiff && abs(nums[i] - nums[j]) <= valuediff) {
                return true;
            }
        }
    }
    return false;
}

int main() { // Пример использования
    std::vector<int> nums = {1, 2, 3, 1};
    int indexdiff = 3;
    int valuediff = 0;

    bool result = findPair(nums, indexdiff, valuediff);

    std::cout << std::boolalpha << result << std::endl;

    return 0;
}
