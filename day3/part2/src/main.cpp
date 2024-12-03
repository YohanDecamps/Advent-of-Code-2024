#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#define FILE_PATH "../input.txt"

int main() {
    std::string file = std::string(std::istreambuf_iterator<char>(std::ifstream(FILE_PATH).rdbuf()), std::istreambuf_iterator<char>());

    int res = 0;

    std::regex pattern = std::regex(R"(mul\((\d+),(\d+)\)|(don't\(\))|(do\(\)))");
    bool enabled = true;

    for (std::regex_iterator<std::string::iterator> it(file.begin(), file.end(), pattern), end; it != end; ++it) {
        if (it->str() == "don't()")
            enabled = false;
        else if (it->str() == "do()")
            enabled = true;
        else if (enabled)
            res += std::stoi(it->str(1)) * std::stoi(it->str(2));
    }

    std::cout << res << std::endl;
    return 0;
}