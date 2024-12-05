#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define FILE_PATH "../input.txt"

int main() {
    std::vector<std::string> lines;
    std::ifstream file(FILE_PATH);

    for (std::string line; std::getline(file, line); lines.push_back(line));

    int size_x = lines.at(0).size();
    int size_y = lines.size();

    int count = 0;

    for (int i = 0; i < size_y - 2; i++)
        for (int j = 0; j < size_x - 2; j++)
            count += ((lines[i][j] == 'M' && lines[i][j + 2] == 'S' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'M' && lines[i + 2][j + 2] == 'S') ||
            (lines[i][j] == 'S' && lines[i][j + 2] == 'M' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'S' && lines[i + 2][j + 2] == 'M') ||
            (lines[i][j] == 'M' && lines[i][j + 2] == 'M' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'S' && lines[i + 2][j + 2] == 'S') ||
            (lines[i][j] == 'S' && lines[i][j + 2] == 'S' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'M' && lines[i + 2][j + 2] == 'M'));


    std::cout << count << std::endl;
}