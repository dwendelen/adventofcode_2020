#include <map>
#include <iostream>
#include <regex>
#include "../../util.hpp"

void parseAndSetMask(const std::string &line, std::vector<u_int64_t> &andMasks, std::vector<u_int64_t> &orMasks);

int main() {
    auto lines = readStrings("day14/input.txt");

    std::regex memRegex(R"(mem\[(\d*)\] = (\d*))");

    std::vector<u_int64_t> andMasks;
    std::vector<u_int64_t> orMasks;
    std::map<u_int64_t, u_int64_t> memory;
    for(const auto& line: lines) {
        if(line.substr(0, 4) == "mask") {
            parseAndSetMask(line, andMasks, orMasks);
        } else {
            std::smatch match;
            if(!std::regex_match(line, match, memRegex)) {
                throw std::runtime_error("Invalid mem set instruction");
            }
            u_int64_t val = std::stol(match[2]);
            u_int64_t addr = std::stol(match[1]);

            for(int j = 0; j < andMasks.size(); j++) {
                u_int64_t addr2 = addr & andMasks[j];
                addr2 |= orMasks[j];
                memory[addr2] = val;
            }
        }
    }

    u_int64_t  sum = 0;
    for(auto entry: memory) {
        sum+= entry.second;
    }

    std::cout << sum << std::endl;
}

void parseAndSetMask(const std::string &line, std::vector<u_int64_t> &andMask, std::vector<u_int64_t> &orMask) {
    if(line.length() != 4 + 3 + 36) {
        throw std::runtime_error("Invalid mask");
    }
    andMask.clear();
    andMask.push_back(~0UL);
    orMask.clear();
    orMask.push_back(0UL);
    for(int i = 0; i < 36; i++) {
        unsigned long size = andMask.size();
        for(int j = 0; j < size; j++) {
            andMask[j] <<= 1;
            orMask[j] <<= 1;

            switch (line[i + 3 + 4]) {
                case '0':
                    andMask[j] |= 1UL;
                    orMask[j] &= ~1UL;
                    break;
                case '1':
                    orMask[j] |= 1UL;
                    break;
                case 'X':
                    andMask.push_back(andMask[j]); // force 1
                    orMask.push_back(orMask[j] | 1UL); //force 1
                    andMask[j] &= ~1UL; // force 0
                    orMask[j] &= ~1UL; // force 0
                    break;
                default:
                    throw std::runtime_error("Invalid mask char");
            }
        }
    }
}
