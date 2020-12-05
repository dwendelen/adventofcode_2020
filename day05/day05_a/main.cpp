#include <iostream>
#include <map>
#include <regex>
#include "../../util.hpp"

int parse(std::string);

int main() {
    std::vector<std::string> strings = readStrings("day05/input.txt");

    std::vector<int> numbers(strings.size());
    std::transform(strings.begin(), strings.end(), numbers.begin(), parse);

    int max = *std::max_element(numbers.begin(), numbers.end());

    std::cout << "Max: " << max << std::endl;
}

int parse(std::string line) {
    int res = 0;
    int factor = 1;
    for (auto i = line.rbegin(); i != line.rend(); ++i) {
        char &c = *i;
        int add;
        switch (c) {
            case 'F':
                add = 0;
                break;
            case 'B':
                add = 1;
                break;
            case 'L':
                add = 0;
                break;
            case 'R':
                add = 1;
                break;
            default:
                throw std::runtime_error(std::string("Invalid char ") + c);

        }
        res += factor * add;
        factor *= 2;
    }
    std::cout << line << ": " << res << std::endl;
    return res;
}