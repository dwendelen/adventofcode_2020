#include <iostream>
#include "../../util.hpp"

uint64_t getNbOfTrees(const bool *map, int nbRows, int nbColumns, int dx, int dy);

int main() {
    std::vector<std::string> strings = readStrings("day03/input.txt");

    int nbRows = strings.size();
    int nbColumns = strings[0].length();

    bool map[nbRows * nbColumns];
    for (int y = 0; y < nbRows; y++) {
        for (int x = 0; x < nbColumns; x++) {
            char &c = strings[y][x];
            bool val;
            switch (c) {
                case '.':
                    val = false;
                    break;
                case '#':
                    val = true;
                    break;
                default:
                    throw std::runtime_error(std::string("Invalid char ") + c);
            }
            map[nbColumns * y + x] = val;
        }
    }

    uint64_t trees1 = getNbOfTrees(map, nbRows, nbColumns, 1, 1);
    uint64_t trees2 = getNbOfTrees(map, nbRows, nbColumns, 3, 1);
    uint64_t trees3 = getNbOfTrees(map, nbRows, nbColumns, 5, 1);
    uint64_t trees4 = getNbOfTrees(map, nbRows, nbColumns, 7, 1);
    uint64_t trees5 = getNbOfTrees(map, nbRows, nbColumns, 1, 2);

    std::cout << trees1 << " " << trees2 << " " << trees3 << " " << trees4 << " " << trees5 << std::endl;
    std::cout << (trees1 * trees2 * trees3 * trees4 * trees5) << std::endl;
}

uint64_t getNbOfTrees(const bool *map, int nbRows, int nbColumns, int dx, int dy) {
    uint64_t nbOfTrees = 0;
    int x = 0;
    for (int y = 0; y < nbRows; y += dy) {
        bool tree = map[nbColumns * y + x];
        if(tree) {
            nbOfTrees++;
        }
        x = (x + dx) % nbColumns;
    }
    return nbOfTrees;
}