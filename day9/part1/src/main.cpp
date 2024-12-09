#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>

#define FILE_PATH "../input.txt"

int main() {
    std::string file = std::string(std::istreambuf_iterator<char>(std::ifstream(FILE_PATH).rdbuf()), std::istreambuf_iterator<char>());

    std::vector<int> output = {};
    bool isFile = true;
    int ID = 0;
    for (char c : file) {
        int num = std::stoi(std::string(1, c));
        if (isFile) {
            for (int i = 0; i < num; ++i)
                output.push_back(ID);
            ID++;
        } else {
            for (int i = 0; i < num; ++i)
                output.push_back(-1);
        }
        isFile = !isFile;
    }

    int size = output.size();
    for (int i = size - 1; i >= 0; i--) {
        int temp = output[i];
        output[i] = -1;
        auto it = std::find(output.begin(), output.end(), -1);
        if (temp != -1 && it != output.end()) {
            *it = temp;
        }
    }

    std::cout << std::accumulate(output.begin(), output.end(), 0LL, [](int64_t acc, int a) {
        static int i = 0;
        if (a != -1)
            acc += a * i;
        i++;
        return acc;
    }) << std::endl;

}