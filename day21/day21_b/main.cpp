#include <regex>
#include <iostream>
#include "../../util.hpp"
#include "../../set.hpp"

int main() {
    auto lines = readStrings("day21/input.txt");
    std::regex regex(R"(([a-z ]+) \(contains ([a-z, ]+)\))");
    std::smatch match;

    std::map<std::string, std::vector<set<std::string>>> map;
    std::map<std::string, std::string> solution;
    set<std::string> allIngredients;
    std::map<std::string, int> ingredientCount;

    for (const auto &line: lines) {
        if (!std::regex_match(line, match, regex)) {
            throw std::runtime_error("Not matching regex");
        }
        std::vector<std::string> ingredients = split(match[1], " ");
        std::vector<std::string> allergens = split(match[2], ", ");

        set<std::string> ingredientSet;
        for (const auto &ingredient: ingredients) {
            ingredientSet += ingredient;
            ingredientCount[ingredient]++;
        }
        allIngredients |= ingredientSet;

        for (const auto &allergen: allergens) {
            map[allergen].push_back(ingredientSet);
        }
    }

    bool changed = true;
    while(changed) {
        changed = false;

        for (auto &entry: map) {
            set<std::string> common = allIngredients;
            for (auto &list: entry.second) {
                common &= list;
            }
            if (common.size() == 1) {
                const auto &ingredient = *common.begin();
                solution[entry.first] = ingredient;

                for(auto &entry2: map) {
                    for(auto &list2: entry2.second) {
                        list2 -= ingredient;
                    }
                }
                changed = true;
            }
        }
    }

    std::string result;
    bool first = true;
    for(auto entry: solution) {
        if(!first) {
            result += ",";
        } else {
            first = false;
        }
        result += entry.second;
    }
    std::cout << result << std::endl;
}