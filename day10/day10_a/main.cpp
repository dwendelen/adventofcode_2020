#include "../../util.hpp"
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int64_t> integers = readIntegers("day10/input.txt");

    std::sort(integers.begin(), integers.end());
    integers.push_back(integers[integers.size() - 1] + 3);

    int nbOne = 0;
    int nbThree = 0;
    int last = 0;
    for(auto integer: integers) {
        if(integer - last == 1) {
            nbOne++;
        } else if(integer - last == 3) {
            nbThree++;
        }

        last = integer;
    }

    std::cout << "1: " << nbOne << ", 3: " << nbThree << ". Multiply: " << nbOne * nbThree << std::endl;
}