#include "../../util.hpp"
#include <vector>
#include <regex>
#include <iostream>

int main() {
    std::vector<std::string> lines = readStrings("day08/input.txt");

    std::regex regex(R"((\w*) ((\+|-)\d*))");

    int acc;
    for(int i = 0; i < lines.size(); i++) {
        std::vector<std::string> pgm(lines.begin(), lines.end());
        std::vector<bool> visited(lines.size(), false);
        acc = 0;
        int pp = 0;

        auto &mod = pgm[i];
        if(mod.substr(0, 3) == "nop") {
            mod = "jmp" + mod.substr(3, mod.size() - 3);
        } else if(mod.substr(0, 3) == "jmp") {
            mod = "nop" + mod.substr(3, mod.size() - 3);
        }

        while (!visited[pp] && pp < lines.size()) {
            visited[pp] = true;

            auto &line = pgm[pp];
            std::smatch match;
            if (!std::regex_match(line, match, regex)) {
                throw std::runtime_error("Regex not matching");
            }
            if (match[1] == "acc") {
                acc += std::stoi(match[2]);
                pp++;
            } else if (match[1] == "jmp") {
                pp += std::stoi(match[2]);
            } else if (match[1] == "nop") {
                pp++;
            } else {
                throw std::runtime_error(std::string("Invalid op ") + (std::string) match[1]);
            }
        }

        if(pp >= lines.size()) {
            std::cout << acc << std::endl;

            break;
        }
    }
    std::cout << "Done" << std::endl;

}