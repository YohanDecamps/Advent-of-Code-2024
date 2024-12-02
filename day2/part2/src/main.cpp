#include <iostream>
#include <fstream>
#include <iterator>
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
        for (int num; ss >> num;) nums.push_back(num);

        for (auto it = nums.begin(); it != nums.end(); it++) {
            std::vector<int> copy(nums);
            copy.erase(std::next(copy.begin(), std::distance(nums.begin(), it)));
            if ((std::is_sorted(copy.begin(), copy.end()) || std::is_sorted(copy.rbegin(), copy.rend())) && std::adjacent_find(copy.begin(), copy.end(), [](int a, int b) {return abs(a - b) == 0 || abs(a - b) > 3;}) == copy.end()) {
                res++;
                break;
            }
        }
    }

    std::cout << res << std::endl;
    return 0;
}