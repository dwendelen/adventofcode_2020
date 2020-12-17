#include <map>
#include <iostream>
#include <regex>
#include "../../util.hpp"

void parseAndSetMask(const std::string &line, u_int64_t &andMask, u_int64_t &orMask);

int main() {
    auto lines = readStrings("day14/input.txt");

    std::regex memRegex(R"(mem\[(\d*)\] = (\d*))");

    u_int64_t andMask;
    u_int64_t orMask;
    std::map<u_int64_t, u_int64_t> memory;
    for(const auto& line: lines) {
        if(line.substr(0, 4) == "mask") {
            parseAndSetMask(line, andMask, orMask);
        } else {
            std::smatch match;
            if(!std::regex_match(line, match, memRegex)) {
                throw std::runtime_error("Invalid mem set instruction");
            }
            u_int64_t addr = std::stol(match[1]);
            u_int64_t val = std::stol(match[2]);
            val &= andMask;
            val |= orMask;
            memory[addr] = val;
        }
    }

    u_int64_t  sum = 0;
    for(auto entry: memory) {
        sum+= entry.second;
    }

    std::cout << sum << std::endl;
}

void parseAndSetMask(const std::string &line, u_int64_t &andMask, u_int64_t &orMask) {
    if(line.length() != 4 + 3 + 36) {
        throw std::runtime_error("Invalid mask");
    }
    andMask = ~0UL;
    orMask = 0UL;
    for(int i = 0; i < 36; i++) {
        andMask <<= 1;
        orMask <<= 1;
        switch(line[i + 3 + 4]) {
            case 'X':
                andMask |= 1UL;
                orMask &= ~1UL;
                break;
            case '1':
                andMask |= 1UL;
                orMask |= 1UL;
                break;
            case '0':
                andMask &= ~1UL;
                orMask &= ~1UL;
                break;
            default:
                throw std::runtime_error("Invalid mask char");
        }
    }
}
