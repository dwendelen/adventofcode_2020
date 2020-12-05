#include <vector>
#include <iostream>
#include "../../util.hpp"


int main() {
    std::vector<int> integers = readIntegers("day01/input.txt");

    for (int i1: integers) {
        for (int i2: integers) {
            for (int i3: integers) {
                if(i1 + i2 + i3 == 2020) {
                    std::cout << (i1 * i2 * i3) << std::endl;
                    return 0;
                }
            }
        }
    }

    std::cout << "Nothing found" << std::endl;
}