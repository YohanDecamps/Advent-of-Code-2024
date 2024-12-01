#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream file("../input.txt");

    std::vector<int> left, right;

    for (int num, l = 0; file >> num; l = 1 - l)
        l == 0 ? left.push_back(num) : right.push_back(num);

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    std::vector<int> res(left.size());
    std::transform(left.begin(), left.end(), right.begin(), res.begin(),
    [](int a, int b) { return std::abs(a - b); });

    std::cout << std::accumulate(res.begin(), res.end(), 0) << std::endl;
    return 0;
}