#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#define FILE_PATH "../input.txt"

int main() {
    std::ifstream file(FILE_PATH);
    std::string line;

    int res = 0;
    while (std::getline(file, line)) {
        std::vector<int> nums;
        std::stringstream ss(line);
        for (int num; ss >> num;)
            nums.push_back(num);

        if ((std::is_sorted(nums.begin(), nums.end()) ||
        std::is_sorted(nums.rbegin(), nums.rend())) &&
        std::adjacent_find(nums.begin(), nums.end(),
        [](int a, int b) {return abs(a - b) == 0 || abs(a - b) > 3;}) == nums.end())
            res++;
    }

    std::cout << res << std::endl;
    return 0;
}