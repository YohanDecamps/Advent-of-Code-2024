#include <fstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#define FILE_PATH "../input.txt"

int main() {
    std::ifstream file(FILE_PATH);

    std::unordered_map<int, std::vector<int>> rules;
    for (std::string line; std::getline(file, line) && line.find('|') != std::string::npos;)
        rules[std::stoi(line.substr(0, line.find('|')))].push_back(std::stoi(line.substr(line.find('|') + 1)));

    std::vector<std::vector<int>> updates;
    for (std::string line; std::getline(file, line);) {
        std::vector<int> update;
        std::stringstream ss(line);
        for (std::string token; std::getline(ss, token, ',');)
            update.push_back(std::stoi(token));
        updates.push_back(update);
    }

    auto sortCondition = [&rules](int a, int b) {
        return std::find(rules[a].begin(), rules[a].end(), b) != rules[a].end();
    };

    std::cout << std::accumulate(updates.begin(), updates.end(), 0,
    [&sortCondition, &rules](int sum, std::vector<int> update) {
        if (std::is_sorted(update.begin(), update.end(), sortCondition))
            sum += update.at(update.size() / 2);
        return sum;
    }) << std::endl;
}