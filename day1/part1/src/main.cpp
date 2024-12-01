#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#define FILE_PATH "../input.txt"

int main() {
    std::ifstream file(FILE_PATH);

    std::vector<int> left, right;

    for (int num, l = 0; file >> num; l = 1 - l)
        l == 0 ? left.push_back(num) : right.push_back(num);

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    std::transform(left.begin(), left.end(), right.begin(), left.begin(),
    [](int a, int b) { return std::abs(a - b); });

    std::cout << std::reduce(left.begin(), left.end()) << std::endl;
    return 0;
}