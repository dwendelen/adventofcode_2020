#include <stdexcept>
#include <iostream>
#include "../../util.hpp"

void print(int rows, int cols, const u_int8_t *occupied, const bool *seat) {
    int i = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (seat[i]) {
                if (occupied[i] == 1) {
                    std::cout << '#';
                } else {
                    std::cout << 'L';
                }
            } else {
                std::cout << '.';
            }
            i++;
        }
        std::cout << std::endl;
    }
}

bool round(int rows, int cols, const u_int8_t *occupied, const bool *seat, u_int8_t *occupiedNext, bool *seatNext) {
    bool changed = false;
    int i = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (seat[i]) {
                int count = 0;
                if (y != 0) {
                    if (x != 0) {
                        count += occupied[cols * (y - 1) + (x - 1)];
                    }
                    count += occupied[cols * (y - 1) + x];
                    if (x != cols - 1) {
                        count += occupied[cols * (y - 1) + (x + 1)];
                    }
                }
                if (x != 0) {
                    count += occupied[cols * y + (x - 1)];
                }
                if (x != cols - 1) {
                    count += occupied[cols * y + (x + 1)];
                }
                if (y != rows - 1) {
                    if (x != 0) {
                        count += occupied[cols * (y + 1) + (x - 1)];
                    }
                    count += occupied[cols * (y + 1) + x];
                    if (x != cols - 1) {
                        count += occupied[cols * (y + 1) + (x + 1)];
                    }
                }
                if (occupied[i] == 1 && count >= 4) {
                    occupiedNext[i] = 0;
                    changed = true;
                } else if (occupied[i] == 0 && count == 0) {
                    occupiedNext[i] = 1;
                    changed = true;
                } else {
                    occupiedNext[i] = occupied[i];
                }
                seatNext[i] = true;
            } else {
                seatNext[i] = false;
                occupiedNext[i] = 0;
            }

            i++;
        }
    }
    return changed;
}

int main() {
    std::vector<std::string> lines = readStrings("day11/input.txt");
    int rows = lines.size();
    int cols = lines[0].size();

    auto *occupied = new u_int8_t[rows * cols];
    bool *seat = new bool[rows * cols];

    auto *occupiedNext = new u_int8_t[rows * cols];
    bool *seatNext = new bool[rows * cols];

    u_int8_t *occ = &occupied[0];
    bool *sea = &seat[0];
    for (const auto &line: lines) {
        for (auto c: line) {
            switch (c) {
                case '.':
                    *sea = false;
                    *occ = 0;
                    break;
                case 'L':
                    *sea = true;
                    *occ = 0;
                    break;
                case '#':
                    *sea = true;
                    *occ = 1;
                default:
                    throw std::runtime_error(std::string("Unknown char ") + c);
            }
            occ++;
            sea++;
        }
    }

    bool changed = true;
    while (changed) {
        std::cout << "Start round" << std::endl;
        changed = round(rows, cols, occupied, seat, occupiedNext, seatNext);
        std::swap(occupied, occupiedNext);
        std::swap(seat, seatNext);
        //print(rows, cols, occupied, seat);
    }

    int totalOccupied = 0;
    for (int i = 0; i < cols * rows; i++) {
        totalOccupied += occupied[i];
    }

    std::cout << "Occupied: " << totalOccupied << std::endl;

    std::cout << "Done" << std::endl;
}