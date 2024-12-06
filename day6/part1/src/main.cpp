#include <fstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#define FILE_PATH "../input.txt"

#define OBSTACLE '#'
#define VISITED 'X'

const std::unordered_map<char, std::pair<int8_t, int8_t>> guardsMap {{'^', {0, -1}}, {'v', {0, 1}}, {'<', {-1, 0}}, {'>', {1, 0}}};

int main() {
    std::ifstream file(FILE_PATH);

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line); lines.push_back(line));

    std::pair<int, int> guardPos, guardDir;

    std::vector<char> guards;
    for (const auto& guard : guardsMap)
        guards.push_back(guard.first);

    for (size_t i = 0; i < lines.size(); i++) {
        auto guard = std::find_first_of(lines[i].begin(), lines[i].end(), guards.begin(), guards.end());
        if (guard != lines[i].end()) {
            guardPos = {static_cast<int>(guard - lines[i].begin()), static_cast<int>(i)};
            guardDir = guardsMap.at(*guard);
            break;
        }
    }

    lines[guardPos.second][guardPos.first] = VISITED;

    while (guardPos.first + guardDir.first >= 0 && guardPos.first + guardDir.first < static_cast<int>(lines[0].size()) && guardPos.second + guardDir.second >= 0 && guardPos.second + guardDir.second < static_cast<int>(lines.size())) {
        if (lines[guardPos.second + guardDir.second][guardPos.first + guardDir.first] == OBSTACLE) {
            guardDir = {guardDir.second * -1, guardDir.first};
        }
        guardPos.first += guardDir.first;
        guardPos.second += guardDir.second;
        lines[guardPos.second][guardPos.first] = VISITED;
    }

    std::string allLines = std::reduce(lines.begin(), lines.end());
    std::cout << std::count(allLines.begin(), allLines.end(), VISITED) << std::endl;
}