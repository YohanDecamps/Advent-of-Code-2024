#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <string>

#define FILE_PATH "../input.txt"

std::pair<int64_t, int64_t> changeStone(int64_t base) {
    if (base == 0)
        return {1, -1};
    std::string str = std::to_string(base);
    if (str.size() % 2 == 0)
        return {std::stoll(str.substr(0, str.size() / 2)), std::stoll(str.substr(str.size() / 2))};
    return {base * 2024, -1};
}

int main() {
    std::ifstream file(FILE_PATH);

    std::unordered_map<int64_t, int64_t> stones;

    for (int64_t stone; file >> stone; stones[stone] = 1);

    for (int k = 0; k < 25; k++) {
        std::unordered_map<int64_t, int64_t> newStones;
        for (auto &stone : stones) {
            auto newStone = changeStone(stone.first);
            newStones.find(newStone.first) != newStones.end() ? newStones[newStone.first] += stone.second : newStones[newStone.first] = stone.second;
            if (newStone.second != -1) {
                newStones.find(newStone.second) != newStones.end() ? newStones[newStone.second] += stone.second : newStones[newStone.second] = stone.second;
            }
            stone.second = 0;
        }
        for (auto &newStone : newStones) {
            if (stones.find(newStone.first) != stones.end()) {
                stones[newStone.first] += newStone.second;
                continue;
            }
            stones[newStone.first] = newStone.second;
        }
    }

    std::cout << std::accumulate(stones.begin(), stones.end(), 0LL, [](int64_t acc, std::pair<int64_t, int64_t> a) {return acc + a.second;}) << std::endl;
}