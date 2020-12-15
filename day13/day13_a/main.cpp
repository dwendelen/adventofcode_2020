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

    long timestamp = std::stol(lines[0]);
    auto stream = std::stringstream(lines[1]);

    long bestBus = -1;
    long bestWait = LONG_MAX;
    std::string num;
    while(getline(stream, num, ',')) {
        if(num == "x") {
            continue;
        }

        long busId = std::stol(num);
        long mod = timestamp % busId;
        long myWait;
        if(mod == 0) {
            myWait = 0;
        } else {
            myWait = busId - mod;
        }

        if(myWait < bestWait) {
            bestWait = myWait;
            bestBus = busId;
        }
    }

    std::cout << "Bus: " << bestBus << ", Wait: " << bestWait << " Res: " << bestBus * bestWait << std::endl;
}