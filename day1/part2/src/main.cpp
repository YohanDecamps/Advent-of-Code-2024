#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream file("../input.txt");

    std::vector<int> left, right;

    for (int num, l = 0; file >> num; l = 1 - l)
        l == 0 ? left.push_back(num) : right.push_back(num);

    std::vector<int> res(left.size());
    std::transform(left.begin(), left.end(), res.begin(),
    [&right](int a) {return std::abs(a * std::count(right.begin(), right.end(), a));});

    std::cout << std::accumulate(res.begin(), res.end(), 0) << std::endl;
    return 0;
}