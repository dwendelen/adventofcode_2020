#include <stdexcept>
#include <sstream>
#include <climits>
#include <iostream>
#include "../../util.hpp"

int main() {
    std::vector<std::string> lines = readStrings("day13/input.txt");
    if(lines.size() != 2) {
        throw std::runtime_error("Expected 2 lines");
    }

    auto stream = std::stringstream(lines[1]);

    long offset = 0;
    long jumpSize = 1;
    long place = 0;
    std::string num;
    while(getline(stream, num, ',')) {
        if(num == "x") {
            place++;
            continue;
        }
        long busId = std::stol(num);

        bool found = false;
        for(long i = 0; i < busId; i++) {
            long wait;
            long mod = offset  % busId;
            if(mod == 0) {
                wait = 0;
            } else {
                wait = busId - mod;
            }
            if(wait == (place % busId)) {
                found = true;
                break;
            }
            offset += jumpSize;
        }
        if(!found) {
            throw std::runtime_error("Stuff not  found");
        }
        jumpSize *= busId;

        place++;
    }

    std::cout << "Offset: " << offset << std::endl;
}