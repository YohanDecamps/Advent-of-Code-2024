
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define FILE_PATH "../input.txt"

int main() {
    std::ifstream file(FILE_PATH);

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line); lines.push_back(line));


    int size_x = lines[0].size();
    int size_y = lines.size();
    std::vector<std::pair<int, int>> trailheads;
    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            if (lines[i][j] == '0') {
                trailheads.push_back({j, i});
            }
        }
    }

    int count = 0;
    for (auto& trailhead : trailheads) {
        std::vector<std::pair<char, std::pair<int, int>>> visited = {{'0', trailhead}};
        char current = '0';
        do {
            current++;
            for (auto &v : visited) {
                if (v.first != current - 1) continue;
                int x = v.second.first, y = v.second.second;
                if (x + 1 >= 0 && x + 1 < size_x && y >= 0 && y < size_y && lines[y][x + 1] == current)
                    visited.push_back({current, {x + 1, y}});
                if (x - 1 >= 0 && x - 1 < size_x && y >= 0 && y < size_y && lines[y][x - 1] == current)
                    visited.push_back({current, {x - 1, y}});
                if (x >= 0 && x < size_x && y + 1 >= 0 && y + 1 < size_y && lines[y + 1][x] == current)
                    visited.push_back({current, {x, y + 1}});
                if (x >= 0 && x < size_x && y - 1 >= 0 && y - 1 < size_y && lines[y - 1][x] == current)
                    visited.push_back({current, {x, y - 1}});
            }
        } while (std::any_of(visited.begin(), visited.end(), [&](std::pair<char, std::pair<int, int>> v) {
            if (v.first == '9') return false;
            int x = v.second.first, y = v.second.second;
            if (!((x + 1 >= 0 && x + 1 < size_x && y >= 0 && y < size_y && lines[y][x + 1] == current) || (x - 1 >= 0 && x - 1 < size_x && y >= 0 && y < size_y && lines[y][x - 1] == current) || (x >= 0 && x < size_x && y + 1 >= 0 && y + 1 < size_y && lines[y + 1][x] == current) || (x >= 0 && x < size_x && y - 1 >= 0 && y - 1 < size_y && lines[y - 1][x] == current)))
                return false;
            return true;
        }));
        count += std::count_if(visited.begin(), visited.end(), [](std::pair<char, std::pair<int, int>> v) { return v.first == '9'; });
    }
    std::cout << count << std::endl;
}