#include <iostream>
#include <algorithm>
#include "../../util.hpp"

int preamble = 25;
auto file = "day09/input.txt";

bool valid(std::vector<int64_t> integers, int idx) {
    int val = integers[idx];
    for(int i = idx - 1; i >= idx - preamble; i--) {
        for(int j = i; j >= idx - preamble; j--) {
            if(integers[i] + integers[j] == val) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::vector<int64_t> integers = readIntegers(file);

    int64_t theNumber = 0;
    for(int i = preamble; i < integers.size(); i++) {
        if(!valid(integers, i)) {
            theNumber = integers[i];
            std::cout << "The number: " << theNumber << std::endl;
            break;
        }
    }

    int start = 0;
    int end = 0;
    uint64_t sum = 0;

    while(true) {
        std::cout << start << " -> " << end << ": " << sum << std::endl;
        if(sum == theNumber) {
            std::cout << "Found " << start << " -> " << end << std::endl;
            break;
        } else if(sum < theNumber) {
            sum += integers[end];
            end++;
        } else { // sum > theNumber
            sum -= integers[start];
            start++;
        }
    }

    auto max = std::max_element(&integers[start], &integers[end]);
    auto min = std::min_element(&integers[start], &integers[end]);
    std::cout << "Max: " << *max <<", Min: " << *min << ", Sum: " << (*min + *max) << std::endl;
    std::cout << "Done" << std::endl;
}