#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#define FILE_PATH "../input.txt"

int main() {

    std::ifstream file(FILE_PATH);

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line); lines.push_back(line));
    file.close();
    int size_x = lines.at(0).size(), size_y = lines.size();

    int count = 0;

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

    for (const auto& [dx, dy] : directions) {
        for (int i = 0; i < size_y; i++) {
            for (int j = 0; j < size_x; j++) {
                bool match = true;
                for (size_t k = 0; k < pattern.size(); k++) {
                    int x = j + k * dx;
                    int y = i + k * dy;
                    if (x < 0 || x >= size_x || y < 0 || y >= size_y || lines[y][x] != pattern[k]) {
                        match = false;
                        break;
                    }
                }
                if (match) count++;
            }
        }
    }

    std::cout << count << std::endl;
}