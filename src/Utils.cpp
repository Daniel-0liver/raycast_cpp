#include "Utils.hpp"

std::vector<std::vector<int>> parseMap(std::string filename) {
    std::vector<std::vector<int>> grid;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return grid;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char ch : line) {
            row.push_back(ch - '0'); // Convert char to int
        }
        grid.push_back(row);
    }

    file.close();
    return grid;
}