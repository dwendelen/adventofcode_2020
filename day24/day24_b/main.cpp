#include <map>
#include <iostream>
#include "../../util.hpp"

class Hex {
public:
    int x; // = e
    int y;

    // x + y + z = 0
    bool operator<(const Hex &other) const {
        if (x < other.x) {
            return true;
        } else if (x > other.x) {
            return false;
        } else {
            return y < other.y;
        }
    }

    std::vector<Hex> neighbours() const {
        return std::vector<Hex>{
                {x + 1, y},
                {x - 1, y},
                {x,     y + 1},
                {x,     y - 1},
                {x + 1, y + 1},
                {x - 1, y - 1}
        };
    }
};

int main() {
    auto lines = readStrings("day24/input.txt");
    std::map<Hex, bool> current;
    std::map<Hex, bool> next;

    for (auto line: lines) {
        Hex hex{0, 0};
        for (auto it = line.begin(); it != line.end(); ++it) {
            switch (*it) {
                case 'e':
                    hex.x++;
                    break;
                case 'w':
                    hex.x--;
                    break;
                case 's':
                    ++it;
                    switch (*it) {
                        case 'e':
                            hex.x++;
                            hex.y++;
                            break;
                        case 'w':
                            hex.y++;
                            break;
                        default:
                            throw std::runtime_error("Unexpected char");
                    }
                    break;
                case 'n':
                    ++it;
                    switch (*it) {
                        case 'w':
                            hex.x--;
                            hex.y--;
                            break;
                        case 'e':
                            hex.y--;
                            break;
                        default:
                            throw std::runtime_error("Unexpected char");
                    }
                    break;
                default:
                    throw std::runtime_error("Unexpected char");
            }
        }
        current[hex] = !current[hex];
    }

    for(auto it = current.begin(); it !=current.end();) {
        if(!it->second) {
            it = current.erase(it);
        } else {
            ++it;
        }
    }

    for (int i = 0; i < 100; i++) {
        next.clear();
        for(auto entry: current) {
            for(auto tile: entry.first.neighbours()) {
                if(next.count(tile) == 1){
                    continue;
                }
                int cnt = 0;
                for(auto n: tile.neighbours()) {
                    if(current.count(n) == 1) {
                        cnt++;
                    }
                }
                if(current.count(tile) == 1) {
                    if (cnt != 0 && cnt <= 2) {
                        next[tile] = true;
                    }
                } else {
                    if(cnt == 2) {
                        next[tile] = true;
                    }
                }
            }
        }
        std::swap(current, next);
    }

    int cnt = 0;
    for (auto entry: current) {
        if (entry.second) {
            cnt++;
        }
    }
    std::cout << cnt << std::endl;
}