#include <regex>
#include <iostream>
#include "../../util.hpp"

class Range {
public:
    uint64_t from1;
    uint64_t to1;
    uint64_t from2;
    uint64_t to2;
};

std::vector<uint64_t> parseTicket(std::string line) {
    auto stream = std::stringstream(line);
    std::vector<uint64_t> ticket;

    std::string num;
    while (getline(stream, num, ',')) {
        ticket.push_back(std::stol(num));
    }
    return ticket;
}

int main() {
    std::vector<std::string> lines = readStrings("day16/input.txt");
    std::regex regex1(R"(([a-z ]+): (\d+)-(\d+) or (\d+)-(\d+))");
    std::smatch match;
    int i = 0;
    std::vector<Range> ranges;

    for (; i < lines.size(); i++) {
        if (lines[i].empty()) {
            i++;
            break;
        }
        if (!std::regex_match(lines[i], match, regex1)) {
            throw std::runtime_error("Regex not matching");
        }
        ranges.emplace_back();
        ranges[ranges.size() - 1].from1 = std::stol(match[2]);
        ranges[ranges.size() - 1].to1 = std::stol(match[3]);
        ranges[ranges.size() - 1].from2 = std::stol(match[4]);
        ranges[ranges.size() - 1].to2 = std::stol(match[5]);
    }

    if (lines[i] != "your ticket:") {
        throw std::runtime_error("Expecting your ticket header");
    }
    i += 3;

    if (lines[i] != "nearby tickets:") {
        throw std::runtime_error("Expecting nearby tickets header");
    }
    i++;

    uint64_t totalError = 0;
    for (; i < lines.size(); i++) {
        std::vector<uint64_t> ticket = parseTicket(lines[i]);
        for(uint64_t val: ticket) {
            bool withinRange = false;
            for(Range& range: ranges) {
                if((range.from1 <= val && val <= range.to1) || (range.from2 <= val && val <= range.to2)) {
                    withinRange = true;
                }
            }
            if(!withinRange) {
                totalError += val;
            }
        }
    }

    std::cout << totalError << std::endl;
}