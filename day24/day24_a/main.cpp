#include <map>
#include <iostream>
#include "../../util.hpp"

class Hex {
public:
    int x; // = e
    int y;
    // x + y + z = 0
    bool operator<(const Hex& other) const {
        if(x < other.x) {
            return true;
        } else if(x > other.x) {
            return false;
        } else {
            return y < other.y;
        }
    }
};

int main() {
    auto lines = readStrings("day24/input.txt");
    std::map<Hex, bool> tiles;

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
        tiles[hex] = !tiles[hex];
    }
    int cnt = 0;
    for(auto entry: tiles) {
        if(entry.second) {
            cnt++;
        }
    }
    std::cout << cnt << std::endl;
}