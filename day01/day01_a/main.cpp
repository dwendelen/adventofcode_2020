#include <vector>
#include <iostream>
#include "../../util.hpp"

int main() {
    std::vector<int> integers = readIntegers("day01/input.txt");

    bool found[2020];
    for (int i = 0; i < 2020; i++) {
        found[i] = false;
    }

    for (int i: integers) {
        if(i >= 2020 || i < 0) {
            throw "Bad number: " + i;
        }
        if(found[2020 - i]) {
            std::cout << (i * (2020 - i)) << std::endl;
            return 0;
        } else {
            found[i] = true;
        }
    }

    std::cout << "Nothing found" << std::endl;
}