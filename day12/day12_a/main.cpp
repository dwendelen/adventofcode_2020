#include <stdexcept>
#include <iostream>
#include "../../util.hpp"

int main() {
    std::vector<std::string> lines = readStrings("day12/input.txt");

    int64_t n = 0;
    int64_t e = 0;
    int64_t de = 1;
    int64_t dn = 0;

    for(auto line: lines) {
        char instruction = line[0];
        int64_t amount = std::stol(line.substr(1, line.size() - 1));
        int64_t tmp;
        switch (instruction) {
            case 'N':
                n += amount;
                break;
            case 'S':
                n -= amount;
                break;
            case 'E':
                e += amount;
                break;
            case 'W':
                e -= amount;
                break;
            case 'F':
                n += dn * amount;
                e += de * amount;
                break;
            case 'L':
                switch(amount % 360) {
                    case 0:
                        break;
                    case 90:
                        tmp = dn;
                        dn = de;
                        de = -tmp;
                        break;
                    case 180:
                        dn = -dn;
                        de = -de;
                        break;
                    case 270:
                        tmp = dn;
                        dn = -de;
                        de = tmp;
                        break;
                    default:
                        throw std::runtime_error(std::string("Invalid angle ") + std::to_string(amount));
                }
                break;
            case 'R':
                switch(amount % 360) {
                    case 0:
                        break;
                    case 90:
                        tmp = dn;
                        dn = -de;
                        de = tmp;
                        break;
                    case 180:
                        dn = -dn;
                        de = -de;
                        break;
                    case 270:
                        tmp = dn;
                        dn = de;
                        de = -tmp;
                        break;
                    default:
                        throw std::runtime_error(std::string("Invalid angle ") + std::to_string(amount));
                }
                break;
            default:
                throw std::runtime_error(std::string("Invalid instruction ") + instruction);
        }
    }

    std::cout << "Ended at N" << n << " E" << e << " distance: " << std::abs(n) + std::abs(e) << std::endl;
}