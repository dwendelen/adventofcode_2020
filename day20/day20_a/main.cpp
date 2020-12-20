#include <iostream>
#include <cmath>
#include "../../util.hpp"

class Tile;

class Configuration {
public:
    Tile *tile;
    uint16_t n;
    uint16_t e;
    uint16_t s;
    uint16_t w;
    std::vector<Configuration *> eFriends;
    std::vector<Configuration *> sFriends;
};

class Tile {
public:
    uint64_t id;
    std::vector<Configuration> configurations;
};

void process(uint16_t &n, char c) {
    n <<= 1;
    if (c == '#') {
        n |= 1;
    }
}

bool
findConfig(std::vector<std::vector<Configuration *>> current, const std::vector<Tile *> &availableTiles, int x, int y,
           int size,
           std::vector<std::vector<Configuration *>> &out) {
    if (availableTiles.empty()) {
        out = current;
        return true;
    }

    std::vector<Configuration *> allOptions;

    if (x == 0 && y == 0) {
        for (auto &availableTile : availableTiles) {
            for (auto &c: availableTile->configurations) {
                allOptions.push_back(&c);
            }
        }
    } else if (y == 0) {
        auto left = current[y][x - 1];
        allOptions = left->eFriends;
    } else if (x == 0) {
        auto up = current[y - 1][x];
        allOptions = up->sFriends;
    } else {
        auto left = current[y][x - 1];
        auto up = current[y - 1][x];
        for (auto l: left->eFriends) {
            for (auto u: up->sFriends) {
                if (u == l) {
                    allOptions.push_back(u);
                }
            }
        }
    }

    int nextX;
    int nextY;
    if (x == size - 1) {
        nextX = 0;
        nextY = y + 1;
    } else {
        nextX = x + 1;
        nextY = y;
    }

    for (auto option: allOptions) {
        std::vector<std::vector<Configuration *>> newCurrent = current;
        newCurrent[y][x] = option;

        std::vector<Tile *> newAvailable = availableTiles;
        bool isAvailable = false;
        for (auto it = newAvailable.begin(); it != newAvailable.end(); ++it) {
            if (*it == option->tile) {
                newAvailable.erase(it);
                isAvailable = true;
                break;
            }
        }

        if (!isAvailable) {
            continue;
        }

        if (findConfig(newCurrent, newAvailable, nextX, nextY, size, out)) {
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<std::string> lines = readStrings("day20/input.txt");
    std::vector<Tile> tiles((lines.size() + 1) / 12);
    int size = sqrt(tiles.size());

    auto ptr = tiles.begin();
    int line = 0;
    while (line < lines.size()) {
        uint64_t id = std::stol(lines[line].substr(5, 4));
        ++line;
        uint16_t n = 0;
        uint16_t nr = 0;
        uint16_t e = 0;
        uint16_t er = 0;
        uint16_t s = 0;
        uint16_t sr = 0;
        uint16_t w = 0;
        uint16_t wr = 0;
        for (int i = 0; i < 10; ++i) {
            process(n, lines[line + 0][i]);
            process(nr, lines[line + 0][9 - i]);
            process(s, lines[line + 9][i]);
            process(sr, lines[line + 9][9 - i]);
            process(w, lines[line + i][0]);
            process(wr, lines[line + 9 - i][0]);
            process(e, lines[line + i][9]);
            process(er, lines[line + 9 - i][9]);

        }
        line += 11;
        ptr->id = id;
        ptr->configurations = {
                {&(*ptr), n,  e,  s,  w},
                {&(*ptr), s,  er, n,  wr},
                {&(*ptr), wr, n,  er, s},
                {&(*ptr), er, nr, wr, sr},
                {&(*ptr), sr, wr, nr, er},
                {&(*ptr), nr, w,  sr, e},
                {&(*ptr), e,  sr, w,  nr},
                {&(*ptr), w,  s,  e,  n}
        };
        ++ptr;
    }

    for (auto &t: tiles) {
        for (auto &c: t.configurations) {
            for (auto &t2: tiles) {
                if (&t2 == &t) {
                    continue;
                }
                for (auto &c2: t2.configurations) {
                    if (c.e == c2.w) {
                        c.eFriends.push_back(&c2);
                    }
                    if (c.s == c2.n) {
                        c.sFriends.push_back(&c2);
                    }
                }
            }
        }
    }


    std::vector<std::vector<Configuration *>> solution;
    std::vector<std::vector<Configuration *>> current(size, std::vector<Configuration *>(size));
    std::vector<Tile *> available(tiles.size());
    for (int i = 0; i < tiles.size(); i++) {
        available[i] = &tiles[i];
    }
    bool found = findConfig(current, available, 0, 0, size, solution);
    if (found) {
        std::cout << "Found" << " "
                  << solution[0][0]->tile->id << " "
                  << solution[0][size - 1]->tile->id << " "
                  << solution[size - 1][size - 1]->tile->id << " "
                  << solution[size - 1][0]->tile->id << " "
                  << solution[0][0]->tile->id *
                     solution[0][size - 1]->tile->id *
                     solution[size - 1][size - 1]->tile->id *
                     solution[size - 1][0]->tile->id
                  << std::endl;
    } else {
        std::cout << "No solution" << std::endl;
    }
}