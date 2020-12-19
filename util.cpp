#include "util.hpp"

#include <fstream>

std::vector<int64_t> readIntegers(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.good()) {
        throw std::runtime_error(fileName + " is not a valid file");
    }
    std::vector<int64_t> integers;
    std::string line;
    while (std::getline(file, line)) {
        integers.push_back(std::stol(line));
    }
    file.close();

    return integers;
}

std::vector<std::string> readStrings(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.good()) {
        throw std::runtime_error(fileName + " is not a valid file");
    }
    std::vector<std::string> strings;
    std::string line;
    while (std::getline(file, line)) {
        strings.push_back(line);
    }
    file.close();

    return strings;
}

std::vector<std::string> split(const std::string &string, const std::string &delimiter) {
    std::vector<std::string> result;
    std::string rest = string;
    while (true) {
        unsigned long pos = rest.find(delimiter);
        if (pos == std::string::npos) {
            result.push_back(rest);
            return result;
        }
        result.push_back(rest.substr(0, pos));
        rest = rest.substr(pos + delimiter.size());
    }
}