#include <map>
#include <iostream>
#include "../../util.hpp"

class Coordinate {
public:
    Coordinate(int64_t x, int64_t y, int64_t z) : x(x), y(y), z(z) {}

    int64_t x;
    int64_t y;
    int64_t z;

    bool operator<(const Coordinate &other) const {
        if (x < other.x) {
            return true;
        } else if (x > other.x) {
            return false;
        }

        if (y < other.y) {
            return true;
        } else if (y > other.y) {
            return false;
        }

        if (z < other.z) {
            return true;
        } else if (z > other.z) {
            return false;
        }

        return false;
    }
};

int main() {
    std::vector<std::string> lines = readStrings("day17/input.txt");

    std::map<Coordinate, bool> map1;
    std::map<Coordinate, bool> map2;

    std::map<Coordinate, bool> &current = map1;
    std::map<Coordinate, bool> &next = map2;

    for (int y = 0; y < lines.size(); ++y) {
        auto line = lines[y];
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '#') {
                current[Coordinate(x, y, 0)] = true;
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        for (auto &entry: current) {
            const Coordinate &element = entry.first;
            for (int64_t xx = element.x - 1; xx <= element.x + 1; ++xx) {
                for (int64_t yy = element.y - 1; yy <= element.y + 1; ++yy) {
                    for (int64_t zz = element.z - 1; zz <= element.z + 1; ++zz) {
                        const Coordinate &neighbour = Coordinate(xx, yy, zz);
                        if (next.count(neighbour) == 1) {
                            continue;
                        }

                        int count = 0;
                        for (int64_t xxx = xx - 1; xxx <= xx + 1; ++xxx) {
                            for (int64_t yyy = yy - 1; yyy <= yy + 1; ++yyy) {
                                for (int64_t zzz = zz - 1; zzz <= zz + 1; ++zzz) {
                                    if (xxx == xx && yyy == yy && zzz == zz) {
                                        continue;
                                    }
                                    count += current.count(Coordinate(xxx, yyy, zzz));
                                }
                            }
                        }
                        if (current.count(neighbour) == 0) {
                            if (count == 3) {
                                next[neighbour] = true;
                            } else {
                                next[neighbour] = false;
                            }
                        } else {
                            if (count == 2 || count == 3) {
                                next[neighbour] = true;
                            } else {
                                next[neighbour] = false;
                            }
                        }
                    }
                }
            }
        }
        for (auto it = next.begin(); it != next.end();) {
            if (!it->second) {
                it = next.erase(it);
            } else {
                ++it;
            }
        }
        std::swap(current, next);
        next.clear();
    }

    std::cout << current.size() << std::endl;
}