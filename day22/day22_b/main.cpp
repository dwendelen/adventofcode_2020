#include <iostream>
#include <unordered_set>
#include "../../util.hpp"

class Configuration {
public:
    std::vector<int> deck1;
    std::vector<int> deck2;
    bool operator==(const Configuration& other) const {
        return deck1 == other.deck1 && deck2 == other.deck2;
    }
};

namespace std
{
    template<>
    struct hash<Configuration>
    {
        size_t
        operator()(const Configuration & obj) const
        {
            size_t hash = 0;
            for(auto i: obj.deck1) {
                hash = 31*hash + i;
            }
            for(auto i: obj.deck2) {
                hash = 31*hash + i;
            }
            return hash;
        }
    };
}


int playGame(Configuration& config) {

    std::unordered_set<Configuration> configs;

    while (true) {
        if(configs.count(config)) {
            return 1;
        }
        configs.insert(config);

        int wnr;
        if(config.deck1.size() >= config.deck1[0] + 1 && config.deck2.size() >= config.deck2[0] + 1) {
            Configuration newConfig = config;
            newConfig.deck1.erase(newConfig.deck1.begin());
            newConfig.deck2.erase(newConfig.deck2.begin());
            newConfig.deck1.erase(newConfig.deck1.begin() + config.deck1[0], newConfig.deck1.end());
            newConfig.deck2.erase(newConfig.deck2.begin() + config.deck2[0], newConfig.deck2.end());
            wnr = playGame(newConfig);
        } else if (config.deck1[0] > config.deck2[0]) {
            wnr = 1;
        } else {
            wnr = 2;
        }
        if(wnr == 1) {
            config.deck1.push_back(config.deck1[0]);
            config.deck1.push_back(config.deck2[0]);
        } else {
            config.deck2.push_back(config.deck2[0]);
            config.deck2.push_back(config.deck1[0]);
        }
        config.deck1.erase(config.deck1.begin());
        config.deck2.erase(config.deck2.begin());

        if(config.deck1.empty()) {
            return 2;
        } else if(config.deck2.empty()) {
            return 1;
        }
    }
}

int main() {
    auto lines = readStrings("day22/input.txt");

    Configuration config;

    auto it = lines.begin();
    ++it;
    while (!it->empty()) {
        config.deck1.push_back(std::stoi(*it));
        ++it;
    }

    it += 2;
    while (!it->empty()) {
        config.deck2.push_back(std::stoi(*it));
        ++it;
    }

    int winnerr = playGame(config);

    auto &winner = winnerr == 1 ? config.deck1 : config.deck2;

    int score = 0;
    int i = 1;
    for (auto itr = winner.rbegin(); itr != winner.rend(); ++i, ++itr) {
        score += i * *itr;
    }
    std::cout << score << std::endl;
}