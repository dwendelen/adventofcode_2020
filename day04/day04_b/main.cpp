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
        if (val == 0) {
            // Not all fields are present
            continue;
        }

        std::string &byr = card["byr"];
        if (byr < "1920" || "2002" < byr) {
            continue;
        }

        std::string &iyr = card["iyr"];
        if (iyr < "2010" || "2020" < iyr) {
            continue;
        }

        std::string &eyr = card["eyr"];
        if (eyr < "2020" || "2030" < eyr) {
            continue;
        }

        std::string &hgt = card["hgt"];
        const std::string &unit = hgt.substr(hgt.size() - 2, 2);
        const std::string &height = hgt.substr(0, hgt.size() - 2);
        if (unit == "cm") {
            if (height < "150" || "193" < height) {
                continue;
            }
        } else if (unit == "in") {
            if (height < "59" || "76" < height) {
                continue;
            }
        } else {
            continue;
        }

        std::string &hcl = card["hcl"];
        if (hcl.size() != 7) {
            continue;
        }
        if (hcl[0] != '#') {
            continue;
        }
        bool ok = true;
        for (int i = 1; i < 7; ++i) {
            char &c = hcl[i];
            if ((c < '0' || '9' < c) && (c < 'a' || 'f' < c)) {
                ok = false;
            }
        }
        if(!ok) {
            continue;
        }

        std::string &ecl = card["ecl"];
        if (
                ecl != "amb" &&
                ecl != "blu" &&
                ecl != "brn" &&
                ecl != "gry" &&
                ecl != "grn" &&
                ecl != "hzl" &&
                ecl != "oth") {
            continue;
        }

        std::string &pid = card["pid"];
        if(pid.size() != 9) {
            continue;
        }
        ok = true;
        for (int i = 0; i < 9; ++i) {
            char &c = pid[i];
            if (c < '0' || '9' < c) {
                ok = false;
            }
        }
        if(!ok) {
            continue;
        }

        total++;
    }

    std::cout << total << std::endl;
}