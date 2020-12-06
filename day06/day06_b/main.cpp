#include <iostream>
#include <map>
#include <regex>
#include "../../util.hpp"

int parse(std::string);

int main() {
    std::vector<std::string> strings = readStrings("day06/input.txt");

    int count = 0;
    bool groupAnswered[26];
    bool personAnswered[26];
    for(bool & i : groupAnswered) {
        i = true;
    }

    for(const auto& line: strings) {
        if(line.empty()) {
            for(bool & i : groupAnswered) {
                if(i) {
                    count++;
                }
                i = true;
            }
        } else {
            for(bool & i : personAnswered) {
                i = false;
            }
            for(auto c: line) {
                personAnswered[c - 'a'] = true;
            }
            for(int i = 0; i < 26; i++) {
                groupAnswered[i] &= personAnswered[i];
            }
        }
    }

    for(bool & i : groupAnswered) {
        if(i) {
            count++;
        }
        i = false;
    }

    std::cout << count << std::endl;
}