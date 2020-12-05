#include <iostream>
#include <map>
#include <regex>
#include "../../util.hpp"

int main() {
    std::vector<std::string> strings = readStrings("day04/input.txt");

    std::regex regex(R"(([^: ]*):([^ ]*))");

    std::vector<std::map<std::string, std::string>> cards;
    bool newEntry = true;
    for (const auto &line: strings) {
        if (newEntry) {
            newEntry = false;
            cards.emplace_back();
        }
        if (line.empty()) {
            newEntry = true;
            continue;
        }

        auto pieces_begin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto pieces_end = std::sregex_iterator();

        for (std::sregex_iterator i = pieces_begin; i != pieces_end; ++i) {
            std::string key = (*i)[1];
            std::string val = (*i)[2];
            cards.back()[key] = val;
        }
    }

    int total = 0;
    for (auto card: cards) {
        int val = card.count("byr") *
                  card.count("iyr") *
                  card.count("eyr") *
                  card.count("hgt") *
                  card.count("hcl") *
                  card.count("ecl") *
                  card.count("pid") /**
                card.count("cid")*/;
        total += val;
    }

    std::cout << total << std::endl;
}