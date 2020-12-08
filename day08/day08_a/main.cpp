#include "../../util.hpp"
#include <vector>
#include <regex>
#include <iostream>

int main() {
    std::vector<std::string> lines = readStrings("day08/input.txt");

    std::vector<bool> visited(lines.size(), false);
    int acc = 0;
    int pp = 0;

    std::regex regex(R"((\w*) ((\+|-)\d*))");

    while (!visited[pp]) {
        visited[pp] = true;

        auto &line = lines[pp];
        std::smatch match;
        if (!std::regex_match(line, match, regex)) {
            throw std::runtime_error("Regex not matching");
        }
        if (match[1] == "acc") {
            acc += std::stoi(match[2]);
            pp++;
        } else if (match[1] == "jmp") {
            pp += std::stoi(match[2]);
        } else if (match[1] == "nop") {
            pp++;
        } else {
            throw std::runtime_error(std::string("Invalid op ") + (std::string) match[1]);
        }
    }

    std::cout << acc << std::endl;
}