#include "../../util.hpp"
#include <algorithm>
#include <iostream>
#include <map>


int main() {
    std::vector<int64_t> integers = readIntegers("day10/input.txt");
    std::map<int64_t, int64_t> numberOfways;

    numberOfways[0] = 1;

    for(int64_t plug: integers) {
        numberOfways[plug] = -1;
    }

    auto start = numberOfways.begin();
    start++;
    for(auto i = start; i != numberOfways.end(); i++) {
        int64_t plug = i->first;
        int64_t sum = 0;
        for(int j = plug - 3; j < plug; j++) {
            if(numberOfways.count(j) != 0) {
                sum += numberOfways[j];
            }
        }
        numberOfways[plug] = sum;
    }

    std::cout << "Number of ways to last plug " << numberOfways.rbegin()->second << std::endl;
}