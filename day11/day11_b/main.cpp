#include <stdexcept>
#include <iostream>
#include <functional>
#include "../../util.hpp"

class Seat {
public:
    u_int8_t occupied = 0;
    u_int8_t occupiedNext = 0;

    std::vector<std::reference_wrapper<Seat>> neighbours;

    void addNeighbour(Seat& other) {
        neighbours.push_back(std::ref(other));
        other.neighbours.push_back(std::ref(*this));
    }

    bool tick() {
        int count = 0;
        for(auto n: neighbours) {
            count += n.get().occupied;
        }
        if (occupied == 1 && count >= 5) {
            occupiedNext = 0;
            return true;
        } else if (occupied == 0 && count == 0) {
            occupiedNext = 1;
            return true;
        } else {
            occupiedNext = occupied;
            return false;
        }
    }

    void flip() {
        occupied = occupiedNext;
    }
};

void print(int rows, int cols, Seat** grid) {
    int i = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (grid[i] != nullptr) {
                if (grid[i]->occupied == 1) {
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

bool round(std::vector<Seat>& seats) {
    bool changed = false;
    for(auto &seat: seats) {
        changed |= seat.tick();
    }
    for(auto &seat: seats) {
        seat.flip();
    }
    return changed;
}

int main() {
    std::vector<std::string> lines = readStrings("day11/input.txt");
    int rows = lines.size();
    int cols = lines[0].size();

    std::vector<Seat> seats;
    seats.reserve(rows * cols);

    Seat *grid[rows * cols];

    Seat** cell = &grid[0];
    int y = 0;
    for (const auto &line: lines) {
        int x = 0;
        for (auto c: line) {
            Seat* newSeat;
            switch (c) {
                case '.':
                    *cell = nullptr;
                    break;
                case 'L':
                    seats.emplace_back();
                    newSeat = &*seats.rbegin();
                    *cell = newSeat;
                    for(int xx = x - 1; xx >= 0; xx--) {
                        Seat *other = grid[y * cols + xx];
                        if(other != nullptr) {
                            newSeat->addNeighbour(*other);
                            break;
                        }
                    }
                    for(int xx = x - 1, yy = y - 1; xx >= 0 && yy >= 0; xx--, yy--) {
                        Seat *other = grid[yy * cols + xx];
                        if(other != nullptr) {
                            newSeat->addNeighbour(*other);
                            break;
                        }
                    }
                    for(int yy = y - 1; yy >= 0; yy--) {
                        Seat *other = grid[yy * cols + x];
                        if(other != nullptr) {
                            newSeat->addNeighbour(*other);
                            break;
                        }
                    }
                    for(int xx = x + 1, yy = y - 1; xx < cols && yy >= 0; xx++, yy--) {
                        Seat *other = grid[yy * cols + xx];
                        if(other != nullptr) {
                            newSeat->addNeighbour(*other);
                            break;
                        }
                    }
                    break;
                default:
                    throw std::runtime_error(std::string("Unknown char ") + c);
            }
            cell++;
            x++;
        }
        y++;
    }

    bool changed = true;
    while (changed) {
        std::cout << "Start round" << std::endl;
        changed = round(seats);
        //print(rows, cols, grid);
    }

    int totalOccupied = 0;
    for (const auto& seat: seats) {
        totalOccupied += seat.occupied;
    }

    std::cout << "Occupied: " << totalOccupied << std::endl;

    std::cout << "Done" << std::endl;
}