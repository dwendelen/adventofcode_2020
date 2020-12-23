#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

const std::string example = "389125467";
const std::string input = "364297581";
const std::string& ref = input;

int main() {
    std::vector<int> deck;
    deck.reserve(ref.size());
    int max = 0;
    for(char c: ref) {
        int x = c - '0';
        deck.push_back(x);
        max = std::max(max, x);
    }
    std::vector<int> tmp(3);
    for(int i = 0; i < 100; i++) {
        int current = deck[0];
        int dst = current;
        auto dest = deck.end();
        while(dest == deck.end()) {
            --dst;
            if(dst <= 0) {
                dst = max;
            }
            dest = std::find(deck.begin() + 4, deck.end(), dst);
        }
        std::copy(deck.begin() + 1, deck.begin() + 4, tmp.begin());
        std::copy(deck.begin() + 4, dest + 1, deck.begin());
        std::copy(tmp.begin(), tmp.end(), dest - 3);
        std::copy(dest + 1, deck.end(), dest);
        deck[deck.size() - 1] = current;
    }

    for(auto d: deck) {
        std::cout << d;
    }
    std::cout << std::endl;
}