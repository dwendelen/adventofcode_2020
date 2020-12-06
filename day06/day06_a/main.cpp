#include <iostream>
#include <map>
#include <regex>
#include "../../util.hpp"

int parse(std::string);

int main() {
    std::vector<std::string> strings = readStrings("day06/input.txt");

    int count = 0;
    bool answered[26];
    for(bool & i : answered) {
        i = false;
    }

    for(const auto& line: strings) {
        if(line.empty()) {
            for(bool & i : answered) {
                if(i) {
                    count++;
                }
                i = false;
            }
        } else {
            for(auto c: line) {
                answered[c - 'a'] = true;
            }
        }
    }

    for(bool & i : answered) {
        if(i) {
            count++;
        }
        i = false;
    }

    std::cout << count << std::endl;
}