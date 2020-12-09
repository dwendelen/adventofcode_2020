#include <iostream>
#include "../../util.hpp"

int preamble = 25;

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
    std::vector<int64_t> integers = readIntegers("day09/input.txt");

    for(int i = preamble; i < integers.size(); i++) {
        if(!valid(integers, i)) {
            std::cout << integers[i] << std::endl;
            break;
        }
    }
    std::cout << "Done" << std::endl;
}