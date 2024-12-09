#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>

#define FILE_PATH "../input.txt"

struct fileSpace {
    int ID;
    int size;
};

int main() {
    std::string file = std::string(std::istreambuf_iterator<char>(std::ifstream(FILE_PATH).rdbuf()), std::istreambuf_iterator<char>());

    std::vector<fileSpace> output = {};
    bool isFile = true;
    int ID = 0;
    for (char c : file) {
        int num = std::stoi(std::string(1, c));
        isFile ? output.push_back({ID++, num}) : output.push_back({-1, num});
        isFile = !isFile;
    }

    for (int i = output.size() - 1; i >= 0; i--) {
        if (output[i].ID == -1) continue;
        fileSpace temp = output[i];
        output[i].ID = -1;
        auto newIt = std::find_if(output.begin(), output.end(), [&temp](fileSpace fs) { return fs.ID == -1 && fs.size >= temp.size; });
        if (newIt != output.end()) {
            int freeSpace = newIt->size - temp.size;
            *newIt = temp;
            output.insert(newIt + 1, {-1, freeSpace});
        }
    }

    std::cout << std::accumulate(output.begin(), output.end(), 0LL, [](int64_t acc, fileSpace a) {
        static int i = 0;
        for (int j = 0; j < a.size; j++, i++)
            if (a.ID != -1)
                acc += a.ID * i;
        return acc;
    }) << std::endl;
}