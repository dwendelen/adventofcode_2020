#include "util.hpp"

#include <fstream>

std::vector<int> readIntegers(const std::string& fileName) {
    std::ifstream file(fileName);
    if(!file.good()) {
        throw std::runtime_error(fileName + " is not a valid file");
    }
    std::vector<int> integers;
    std::string line;
    while(std::getline(file, line)) {
        integers.push_back(std::stoi(line));
    }
    file.close();

    return integers;
}

std::vector<std::string> readStrings(const std::string& fileName) {
    std::ifstream file(fileName);
    if(!file.good()) {
        throw std::runtime_error(fileName + " is not a valid file");
    }
    std::vector<std::string> strings;
    std::string line;
    while(std::getline(file, line)) {
        strings.push_back(line);
    }
    file.close();

    return strings;
}