#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#define FILE_PATH "../input.txt"

int main() {
    std::ifstream file(FILE_PATH);

    std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
    std::string line;
    int size_x = 0;
    int size_y = 0;
    for (; std::getline(file, line); size_y++) {
        size_x = line.size();
        auto pos = line.begin() - 1;
        while (std::any_of(pos, line.end(), [](char c) { return c != '.'; })) {
            pos = std::find_if(pos + 1, line.end(), [](char c) { return c != '.'; });
            if (pos == line.end()) break;
            antennas[*pos].push_back({static_cast<int>(pos - line.begin()), size_y});
        }
    }

    std::vector<std::pair<int, int>> frequencies;
    for (const auto &[key, values] : antennas) {
        for (auto v1 = values.begin(); v1 != values.end(); v1++) {
            for (auto v2 = v1 + 1; v2 != values.end(); v2++) {
                for (int k = 0; ; k++) {
                    std::pair<int, int> p1 = {(*v1).first + ((*v1).first - (*v2).first) * k, (*v1).second + ((*v1).second - (*v2).second) * k};
                    std::pair<int, int> p2 = {(*v2).first + ((*v2).first - (*v1).first) * k, (*v2).second + ((*v2).second - (*v1).second) * k};
                    bool added = false;
                    if (p1.first >= 0 && p1.first < size_x && p1.second >= 0 && p1.second < size_y) {
                        frequencies.push_back(p1);
                        added = true;
                    }
                    if (p2.first >= 0 && p2.first < size_x && p2.second >= 0 && p2.second < size_y) {
                        frequencies.push_back(p2);
                        added = true;
                    }
                    if (!added) break;
                }
            }
        }
    }

    std::sort(frequencies.begin(), frequencies.end());
    frequencies.erase(std::unique(frequencies.begin(), frequencies.end()), frequencies.end());
    std::cout << frequencies.size() << std::endl;
}