#include <cstdint>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include <string>
#include <vector>

struct Machine {
    std::pair<int64_t, int64_t> A;
    std::pair<int64_t, int64_t> B;
    std::pair<int64_t, int64_t> p;
};

#define FILE_PATH "../input.txt"

int main() {
    std::string file = std::string(std::istreambuf_iterator<char>(std::ifstream(FILE_PATH).rdbuf()), std::istreambuf_iterator<char>());

    std::regex pattern(R"(.+X\+(\d+), Y\+(\d+)\n.+X\+(\d+), Y\+(\d+)\n.+X=(\d+), Y=(\d+))");

    std::vector<Machine> machines;

    std::for_each(std::sregex_iterator(file.begin(), file.end(), pattern), std::sregex_iterator(), [&](const auto& match) {
        machines.push_back({{std::stoi(match[1]), std::stoi(match[2])}, {std::stoi(match[3]), std::stoi(match[4])}, {std::stoi(match[5]) + 10000000000000, std::stoi(match[6]) + 10000000000000}});
    });

    int64_t nb_tokens = 0;
    for (const auto& machine : machines) {
        int64_t B = ((machine.p.first * machine.A.second) - (machine.p.second * machine.A.first)) / ((machine.B.first * machine.A.second) - (machine.B.second * machine.A.first));
        int64_t A = (machine.p.first - (machine.B.first * B)) / machine.A.first;
        if (B * machine.B.first + A * machine.A.first == machine.p.first && B * machine.B.second + A * machine.A.second == machine.p.second) {
            nb_tokens += A * 3 + B;
        }
    }
    std::cout << nb_tokens << std::endl;
}