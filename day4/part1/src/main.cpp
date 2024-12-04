#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define FILE_PATH "../input.txt"

int main() {
    std::string file = std::string(std::istreambuf_iterator<char>(std::ifstream(FILE_PATH).rdbuf()), std::istreambuf_iterator<char>());

    int size = std::find(file.begin(), file.end(), '\n') - file.begin();
    file.erase(std::remove(file.begin(), file.end(), '\n'), file.end());

    const std::vector<std::pair<int, int>> directions = {
        {0, 1},   // Horizontal
        {0, -1},  // Reverse Horizontal
        {1, 0},   // Vertical
        {-1, 0},  // Reverse Vertical
        {1, 1},   // Diagonal 45 degrees
        {-1, -1}, // Reverse Diagonal 45 degrees
        {1, -1},  // Diagonal 135 degrees
        {-1, 1}   // Reverse Diagonal 135 degrees
    };

    std::string pattern = "XMAS";

    int count = 0;

    for (const auto& [dx, dy] : directions) {
        for (size_t j = 0; j < file.size(); j++) {
            bool match = true;
            for (size_t k = 0; k < pattern.size(); k++) {
                int x = j % size + k * dx;
                int y = j / size + k * dy;
                if (x < 0 || x >= size || y < 0 || y >= static_cast<int>(file.size()) / size || file[y * size + x] != pattern[k]) {
                    match = false;
                    break;
                }
            }
            if (match) count++;
        }
    }

    std::cout << count << std::endl;
}