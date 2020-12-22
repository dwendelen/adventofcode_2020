#include <iostream>
#include "../../util.hpp"

int main() {
    auto lines = readStrings("day22/input.txt");

    std::vector<int> deck1;
    std::vector<int> deck2;

    auto it = lines.begin();
    ++it;
    while (!it->empty()) {
        deck1.push_back(std::stoi(*it));
        ++it;
    }

    it += 2;
    while (!it->empty()) {
        deck2.push_back(std::stoi(*it));
        ++it;
    }

    while (!deck1.empty() && !deck2.empty()) {
        if (deck1[0] > deck2[0]) {
            deck1.push_back(deck1[0]);
            deck1.push_back(deck2[0]);
        } else {
            deck2.push_back(deck2[0]);
            deck2.push_back(deck1[0]);
        }
        deck1.erase(deck1.begin());
        deck2.erase(deck2.begin());
    }

    std::vector<int> &winner = deck1.empty() ? deck2 : deck1;

    int score = 0;
    int i = 1;
    for(auto itr=winner.rbegin(); itr != winner.rend(); ++i, ++itr) {
        score +=  i * *itr;
    }
    std::cout << score << std::endl;
}