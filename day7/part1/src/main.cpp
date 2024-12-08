#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

#define FILE_PATH "../input2.txt"

enum class Operator {
    PLUS,
    MULTIPLY
};

std::vector<Operator> generateOperators(std::vector<Operator> &operators) {
    for (auto &op : operators)
        if (op == Operator::PLUS) {
            op = Operator::MULTIPLY;
            break;
        } else
            op = Operator::PLUS;
    return operators;
}

int main() {
    std::ifstream file(FILE_PATH);

    std::vector<std::pair<int64_t, std::vector<int64_t>>> nums;
    for (std::string line; std::getline(file, line) && line.find(':') != std::string::npos;) {
        std::stringstream ss(line.substr(line.find(':') + 1));
        std::vector<int64_t> tempNums = {};
        for (std::string num; ss >> num; tempNums.push_back(std::stoll(num)));
        nums.push_back({std::stoll(line.substr(0, line.find(':'))), tempNums});
    }

    std::cout << std::accumulate(nums.begin(), nums.end(), 0LL, [&nums] (int64_t sum, std::pair<int64_t, std::vector<int64_t>> num) {
        std::vector<Operator> operators(num.second.size() - 1, Operator::PLUS);
        do {
            int64_t tempValue = num.second[0];
            for (size_t i = 0; i < operators.size(); i++)
                if (operators[i] == Operator::PLUS)
                    tempValue += num.second[i + 1];
                else
                    tempValue *= num.second[i + 1];
            if (tempValue == num.first)
                return sum += num.first;
            generateOperators(operators);
        } while (!std::all_of(operators.begin(), operators.end(), [](Operator op) { return op == Operator::PLUS; }));
        return sum;
    }) << std::endl;

}