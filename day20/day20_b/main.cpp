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
    int rot;
    bool flip;
    std::vector<Configuration *> eFriends;
    std::vector<Configuration *> sFriends;
};

class Tile {
public:
    uint64_t id;
    std::vector<Configuration> configurations;
    std::vector<std::vector<bool>> image;
};

void process(uint16_t &n, char c) {
    n <<= 1;
    if (c == '#') {
        n |= 1;
    }
}

void
addSolution(std::vector<std::vector<Configuration *>> current, const std::vector<Tile *> &availableTiles, int x, int y,
            int size,
            std::vector<std::vector<std::vector<Configuration *>>> &out) {
    if (availableTiles.empty()) {
        out.push_back(current);
        return;
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

        addSolution(newCurrent, newAvailable, nextX, nextY, size, out);
    }
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
        ptr->id = id;
        ptr->configurations = {
                {&(*ptr), n,  e,  s,  w,  0, false},
                {&(*ptr), s,  er, n,  wr, 0, true},
                {&(*ptr), wr, n,  er, s,  1, false},
                {&(*ptr), er, nr, wr, sr, 1, true},
                {&(*ptr), sr, wr, nr, er, 2, false},
                {&(*ptr), nr, w,  sr, e,  2, true},
                {&(*ptr), e,  sr, w,  nr, 3, false},
                {&(*ptr), w,  s,  e,  n,  3, true}
        };
        ptr->image.resize(10, std::vector<bool>(10, false));
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 10; ++x) {
                ptr->image[y][x] = lines[line + y][x] == '#';
            }
        }
        line += 11;
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

    std::vector<std::vector<std::vector<Configuration *>>> solutions;
    std::vector<std::vector<Configuration *>> current(size, std::vector<Configuration *>(size));
    std::vector<Tile *> available(tiles.size());
    for (int i = 0; i < tiles.size(); ++i) {
        available[i] = &tiles[i];
    }
    addSolution(current, available, 0, 0, size, solutions);
    // I expect to find 8 solutions (one for every orientation)
    int maxNbMonsters = 0;
    for (auto &solution: solutions) {
        std::vector<std::vector<bool>> image(8 * size, std::vector<bool>(8 * size));
        for (int ty = 0; ty < size; ++ty) {
            for (int tx = 0; tx < size; ++tx) {
                auto conf = solution[ty][tx];
                // t = transformation matrix
                int t11 = 1;
                int t12 = 0;
                int t21 = 0;
                int t22 = 1;
                for (int i = 0; i < conf->rot; i++) {
                    t21 *= -1;
                    t22 *= -1;
                    std::swap(t11, t21);
                    std::swap(t12, t22);
                }
                if (conf->flip) {
                    t21 *= -1;
                    t22 *= -1;
                }
                for (int y = 1; y < 9; y++) {
                    for (int x = 1; x < 9; x++) {
                        int transx = t11 * (x + 1) + t12 * (y + 1);
                        int transy = t21 * (x + 1) + t22 * (y + 1);
                        if (transx < 0) {
                            transx += 11;
                        }
                        --transx;
                        if (transy < 0) {
                            transy += 11;
                        }
                        --transy;
                        image[8 * ty + transy - 1][8 * tx + transx - 1] = conf->tile->image[y][x];
                    }
                }
            }
        }

        for (int y = 0; y < 8 * size; ++y) {
            for (int x = 0; x < 8 * size; ++x) {
                std::cout << (image[y][x] ? '#' : ' ');
            }
            std::cout << std::endl;
        }

        int nbMonsters = 0;
        for (int y = 0; y < 8 * size - 2; ++y) {
            for (int x = 0; x < 8 * size - 19; ++x) {
                if(image[y][x + 18] &&

                    image[y + 1][x] &&
                    image[y + 1][x + 5] &&
                    image[y + 1][x + 6]  &&
                    image[y + 1][x + 11] &&
                    image[y + 1][x + 12] &&
                    image[y + 1][x + 17] &&
                    image[y + 1][x + 18] &&
                    image[y + 1][x + 19] &&

                    image[y + 2][x + 1] &&
                    image[y + 2][x + 4] &&
                    image[y + 2][x + 7] &&
                    image[y + 2][x + 10] &&
                    image[y + 2][x + 13] &&
                    image[y + 2][x + 16]) {
                    ++nbMonsters;
                }
            }
        }
        std::cout << "Monsters: " << nbMonsters << std::endl;
        std::cout << std::endl;
        if(nbMonsters > maxNbMonsters) {
            maxNbMonsters = nbMonsters;
        }
    }
    int hashes = 0;
    for(auto tile: tiles) {
        for (int y = 1; y < 9; ++y) {
            for (int x = 1; x < 9; ++x) {
                if(tile.image[y][x]) {
                    hashes++;
                }
            }
        }
    }
    std::cout << maxNbMonsters << " " << hashes -maxNbMonsters* 15<<std::endl;
}