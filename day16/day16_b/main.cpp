#include <regex>
#include <iostream>
#include "../../util.hpp"

class Range {
public:
    std::string name;
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

    for (; i < lines.size(); ++i) {
        if (lines[i].empty()) {
            ++i;
            break;
        }
        if (!std::regex_match(lines[i], match, regex1)) {
            throw std::runtime_error("Regex not matching");
        }
        ranges.emplace_back();
        ranges[ranges.size() - 1].name = match[1];
        ranges[ranges.size() - 1].from1 = std::stol(match[2]);
        ranges[ranges.size() - 1].to1 = std::stol(match[3]);
        ranges[ranges.size() - 1].from2 = std::stol(match[4]);
        ranges[ranges.size() - 1].to2 = std::stol(match[5]);
    }

    if (lines[i] != "your ticket:") {
        throw std::runtime_error("Expecting your ticket header");
    }
    ++i;
    std::vector<uint64_t> myTicket = parseTicket(lines[i]);
    i+= 2;
    if (lines[i] != "nearby tickets:") {
        throw std::runtime_error("Expecting nearby tickets header");
    }
    ++i;

    std::vector<std::map<Range *, bool>> possibilities;
    std::vector<uint64_t> firstTicket = parseTicket(lines[i]);
    for (int j = 0; j < firstTicket.size(); j++) {
        possibilities.emplace_back();
        for (auto &r: ranges) {
            possibilities[possibilities.size() - 1][&r] = true;
        }
    }

    for (; i < lines.size(); ++i) {
        std::vector<uint64_t> ticket = parseTicket(lines[i]);
        bool isTicketValid = true;
        for (unsigned long val : ticket) {
            bool isValid = false;
            for (Range &range: ranges) {
                if ((range.from1 <= val && val <= range.to1) || (range.from2 <= val && val <= range.to2)) {
                    isValid = true;
                    break;
                }
            }
            if (!isValid) {
                isTicketValid = false;
                break;
            }
        }
        if (!isTicketValid) {
            continue;
        }
        for (int j = 0; j < ticket.size(); j++) {
            uint64_t val = ticket[j];
            for (Range &range: ranges) {
                if (!((range.from1 <= val && val <= range.to1) || (range.from2 <= val && val <= range.to2))) {
                    possibilities[j].erase(&range);
                }
            }
        }
    }

    bool changes = true;
    while (changes) {
        changes = false;
        for (int j = 0; j < possibilities.size(); ++j) {
            if (possibilities[j].size() == 1) {
                Range *element = possibilities[j].begin()->first;
                for (int k = 0; k < possibilities.size(); ++k) {
                    if (k != j) {
                        if (possibilities[k].count(element) == 1) {
                            possibilities[k].erase(element);
                            changes = true;
                        }
                    }
                }
            }
        }
    }

    uint64_t result = 1;
    for (int k = 0; k < possibilities.size(); k++) {
        for (auto &r: possibilities[k]) {

            std::string &name = r.first->name;
            if(name.size() > 9 && name.substr(0, 9) == "departure") {
                std::cout << "name: " << name << " val: " << myTicket[k] << std::endl;
                result *= myTicket[k];
            }
        }
    }

    std::cout << result << std::endl;
}