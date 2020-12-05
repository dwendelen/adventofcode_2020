#include <iostream>
#include "../../util.hpp"

int main() {
    std::vector<std::string> strings = readStrings("day03/input.txt");

    int nbRows = strings.size();
    int nbColumns = strings[0].length();
    
    bool map[nbRows][nbColumns];
    for(int y = 0; y < nbRows; y++) {
        for(int x = 0; x < nbColumns; x++) {
            char &c = strings[y][x];
            bool val;
            switch(c) {
                case '.':
                    val = false;
                    break;
                case '#':
                    val = true;
                    break;
                default:
                    throw std::runtime_error(std::string("Invalid char ") + c);
            }
            map[y][x] = val;
        }
    }

    int nbTrees = 0;
    int dx = 3;
    for(int y = 0; y < nbRows; y++) {
        if(map[y][(dx * y)%nbColumns]) {
            nbTrees++;
        }
    }

    std::cout << nbTrees << std::endl;
}