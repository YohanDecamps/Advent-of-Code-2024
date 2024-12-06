#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <unordered_map>

#define FILE_PATH "../input.txt"

#define OBSTACLE '#'

const std::unordered_map<char, std::pair<int8_t, int8_t>> guardsMap {{'^', {0, -1}}, {'v', {0, 1}}, {'<', {-1, 0}}, {'>', {1, 0}}};

int main() {
    std::ifstream file(FILE_PATH);

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line); lines.push_back(line));

    std::pair<int, int> startPos, startDir;

    std::vector<char> guards;
    for (const auto& guard : guardsMap)
        guards.push_back(guard.first);

    for (size_t i = 0; i < lines.size(); i++) {
        auto guard = std::find_first_of(lines[i].begin(), lines[i].end(), guards.begin(), guards.end());
        if (guard != lines[i].end()) {
            startPos = {static_cast<int>(guard - lines[i].begin()), static_cast<int>(i)};
            startDir = guardsMap.at(*guard);
            break;
        }
    }

    std::vector<std::pair<int, int>> allPos = {startPos};
    for (std::pair<int, int> Pos = startPos, guardDir = startDir;
    Pos.first + guardDir.first >= 0 && Pos.first + guardDir.first < static_cast<int>(lines[0].size()) &&
    Pos.second + guardDir.second >= 0 && Pos.second + guardDir.second < static_cast<int>(lines.size());) {
        if (lines[Pos.second + guardDir.second][Pos.first + guardDir.first] == OBSTACLE)
            guardDir = {guardDir.second * -1, guardDir.first};
        if (std::find(allPos.begin(), allPos.end(), Pos) == allPos.end())
            allPos.push_back(Pos);
        Pos = {Pos.first + guardDir.first, Pos.second + guardDir.second};
    }

    std::cout << std::accumulate(allPos.begin(), allPos.end(), 0, [&] (int sum, std::pair<int, int> a) {
        std::vector<std::tuple<int, int, int, int>> steps;
        for (std::pair<int, int> pos = startPos, dir = startDir; pos.first + dir.first >= 0 && pos.first + dir.first < static_cast<int>(lines[0].size()) && pos.second + dir.second >= 0 && pos.second + dir.second < static_cast<int>(lines.size()); pos = {pos.first + dir.first, pos.second + dir.second}) {
            if (!(lines.at(pos.second + dir.second).at(pos.first + dir.first) == OBSTACLE
            || (pos.second + dir.second == a.second && pos.first + dir.first == a.first)))
                continue;
            if (std::find(steps.begin(), steps.end(), std::make_tuple(pos.first, pos.second, dir.first, dir.second)) != steps.end())
                return sum + 1;
            steps.push_back({pos.first, pos.second, dir.first, dir.second});
            dir = {dir.second * -1, dir.first};
        }
        return sum;
    }) << std::endl;
}