#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

#define FILE_PATH "../input.txt"

std::unordered_map<int, std::vector<int>> connectComponnents(std::unordered_map<int, std::vector<int>> &labelMap, int a, int b) {
    for (uint32_t k = 0; k < labelMap.size(); k++)
        for (uint32_t l = 0; l < labelMap[k].size(); l++)
            if (labelMap[k][l] == a)
                labelMap[k][l] = b;
    return labelMap;
}

std::unordered_map<int, std::vector<int>> labelize(std::unordered_map<int, std::string> &map) {
    std::unordered_map<int, std::vector<int>> labelMap;
    int label = 0;
    for (uint32_t i = 0; i < map.size(); i++) {
        for (uint32_t j = 0; j < map[i].size(); j++) {
            if (i > 0 && map[i - 1][j] == map[i][j] && j > 0 && map[i][j - 1] == map[i][j] && labelMap[i - 1][j] != labelMap[i][j - 1])
                labelMap = connectComponnents(labelMap, labelMap[i - 1][j], labelMap[i][j - 1]);
            if (i > 0 && map[i - 1][j] == map[i][j])
                labelMap[i].push_back(labelMap[i - 1][j]);
            else if (j > 0 && map[i][j - 1] == map[i][j])
                labelMap[i].push_back(labelMap[i][j - 1]);
            else
                labelMap[i].push_back(++label);
        }
    }
    return labelMap;
}

int main() {
    std::ifstream file(FILE_PATH);

    std::unordered_map<int, std::vector<std::vector<int>>> countMap;
    std::unordered_map<int, int> areas;
    std::unordered_map<int, int> perimeters;
    std::unordered_map<int, std::vector<int>> labelMap;

    {
        std::unordered_map<int, std::string> map;
        std::string line;
        for (int i = 0; std::getline(file, line); i++) map[i] = line;
        labelMap = labelize(map);
    }

    for (uint32_t i = 0; i < labelMap.size(); i++) {
        for (uint32_t j = 0; j < labelMap[i].size(); j++) {
            countMap[i].push_back({});
            areas[labelMap[i][j]]++;
            if (i + 1 >= labelMap.size() || labelMap[i + 1][j] != labelMap[i][j]) {
                if (static_cast<int>(j) - 1 < 0 || labelMap[i][j] != labelMap[i][j - 1] || std::find(countMap[i][j - 1].begin(), countMap[i][j - 1].end(), 1) == countMap[i][j - 1].end())
                    perimeters[labelMap[i][j]]++;
                countMap[i][j].push_back(1);
            } if (static_cast<int>(i) - 1 < 0 || labelMap[i - 1][j] != labelMap[i][j]) {
                if (static_cast<int>(j) - 1 < 0 || labelMap[i][j] != labelMap[i][j - 1] || std::find(countMap[i][j - 1].begin(), countMap[i][j - 1].end(), 2) == countMap[i][j - 1].end())
                    perimeters[labelMap[i][j]]++;
                countMap[i][j].push_back(2);
            } if (j + 1 >= labelMap[i].size() || labelMap[i][j + 1] != labelMap[i][j]) {
                if (static_cast<int>(i) - 1 < 0 || labelMap[i][j] != labelMap[i - 1][j] || std::find(countMap[i - 1][j].begin(), countMap[i - 1][j].end(), 3) == countMap[i - 1][j].end())
                    perimeters[labelMap[i][j]]++;
                countMap[i][j].push_back(3);
            } if (static_cast<int>(j) - 1 < 0 || labelMap[i][j - 1] != labelMap[i][j]) {
                if (static_cast<int>(i) - 1 < 0 || labelMap[i][j] != labelMap[i - 1][j] || std::find(countMap[i - 1][j].begin(), countMap[i - 1][j].end(), 4) == countMap[i - 1][j].end())
                    perimeters[labelMap[i][j]]++;
                countMap[i][j].push_back(4);
            }
        }
    }
    std::cout << std::accumulate(areas.begin(), areas.end(), 0, [&](int sum, std::pair<int, int> area) { return sum + area.second * perimeters[area.first]; }) << std::endl;
}