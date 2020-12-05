#include <regex>
#include <iostream>
#include "../../util.hpp"


int main() {
    std::vector<std::string> strings = readStrings("day02/input.txt");

    std::regex regex(R"((\d*)-(\d*) (\w): (\w*))");

    int res = 0;

    for(const auto& str: strings) {
        std::smatch match;
        if(!std::regex_match(str, match, regex)){
            throw std::runtime_error("Regex not matching");
        }
        int from = std::stoi(match[1]);
        int to = std::stoi(match[2]);
        char c = match[3].str()[0];
        std::string toCheck = match[4];

        if(toCheck[from - 1] == c && toCheck[to - 1] != c || toCheck[to - 1] == c && toCheck[from - 1] != c) {
            res++;
        }
    }

    std::cout << res << std::endl;
    return 0;
}