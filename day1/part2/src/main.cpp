#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <algorithm>

#define FILE_PATH "../input.txt"

int main() {
    std::ifstream file(FILE_PATH);

    std::vector<int> left, right;

    for (int num, l = 0; file >> num; l = 1 - l)
        l == 0 ? left.push_back(num) : right.push_back(num);

    std::transform(left.begin(), left.end(), left.begin(),
    [&right](int a) {return a * std::count(right.begin(), right.end(), a);});

    std::cout << std::reduce(left.begin(), left.end()) << std::endl;
    return 0;
}