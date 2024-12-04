#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define FILE_PATH "../input.txt"

int main() {
    std::string file = std::string(std::istreambuf_iterator<char>(std::ifstream(FILE_PATH).rdbuf()), std::istreambuf_iterator<char>());
    const int size = std::find(file.begin(), file.end(), '\n') - file.begin();
    file.erase(std::remove(file.begin(), file.end(), '\n'), file.end());

    std::string pattern = "XMAS";

    int count = 0;

    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy)
            for (size_t j = 0, k = 0; j < file.size(); j++, k = 0)
                count += std::all_of(pattern.begin(), pattern.end(), [&](char c) {
                    int x = j % size + k * dx;
                    int y = j / size + k++ * dy;
                    return !(x < 0 || x >= size || y < 0 || y >= static_cast<int>(file.size()) / size || file[y * size + x] != c);
                });

    std::cout << count << std::endl;
}