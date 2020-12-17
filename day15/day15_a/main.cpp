#include <stdexcept>
#include <map>
#include <iostream>
#include "../../util.hpp"

int main() {
    std::vector<u_int64_t> example1{0, 3, 6}; // 436
    std::vector<u_int64_t> example2{1, 3, 2}; // 1
    std::vector<u_int64_t> example3{2, 1, 3}; // 10
    std::vector<u_int64_t> example4{1, 2, 3}; // 27
    std::vector<u_int64_t> example5{2, 3, 1}; // 78
    std::vector<u_int64_t> example6{3, 2, 1}; // 438
    std::vector<u_int64_t> example7{3, 1, 2}; // 1836
    std::vector<u_int64_t> input{0, 14, 1, 3, 7, 9}; // 1836

    std::vector<u_int64_t> &start = input;

    std::map<uint64_t, uint64_t> lastTimeSpoken;
    uint64_t lastSpoken;
    for (int i = 0; i < start.size(); i++) {
        lastSpoken = start[i];
        lastTimeSpoken[lastSpoken] = i;
    }

    for(int i = start.size(); i < 2020; i++) {
        uint64_t newNumber;
        if(lastTimeSpoken.count(lastSpoken) == 0) {
            newNumber = 0;
        } else {
            newNumber = i - 1 - lastTimeSpoken[lastSpoken];
        }
        lastTimeSpoken[lastSpoken] = i - 1;
        lastSpoken = newNumber;
    }
    std::cout << lastSpoken << std::endl;
}