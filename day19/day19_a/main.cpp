#include <utility>
#include <iostream>
#include "../../util.hpp"

class Rule {
public:
    virtual bool match(std::string::iterator& cursor, std::string::iterator& end) = 0;
};

class StringRule: public Rule {
public:
    explicit StringRule(char str): str(str) {}
    char str;
    bool match(std::string::iterator& cursor, std::string::iterator& end) override {
        if(cursor == end) {
            return false;
        }
        return *(cursor++) == str;
    }
};

class CompositeRule: public Rule {
public:
    explicit CompositeRule(std::vector<std::vector<Rule*>> subRules): subRules(std::move(subRules)) {}
    std::vector<std::vector<Rule*>> subRules;
    bool match(std::string::iterator &cursor, std::string::iterator &end) override {
        if(cursor == end) {
            return false;
        }
        auto startPoint = cursor;
        for(const auto& subRule: subRules) {
            cursor = startPoint;
            bool matched = true;
            for(auto item: subRule) {
                if(!item->match(cursor, end)) {
                    matched = false;
                }
            }
            if(matched) {
                return true;
            }
        }
        return false;
    }
};

Rule* parseRule(std::vector<std::string>& ruleDefinitions, int idx, std::vector<Rule*>& rules);

CompositeRule* parseComposite(const std::string& definition, std::vector<std::string>& ruleDefinitions, std::vector<Rule*>& rules) {
    auto ors = split(definition, " | ");
    std::vector<std::vector<Rule*>> subRules(ors.size());
    for(int i = 0; i < ors.size(); i++) {
        auto ands = split(ors[i], " ");
        subRules[i].resize(ands.size());
        for(int j = 0; j < ands.size(); j++) {
            int id = std::stoi(ands[j]);
            subRules[i][j] = parseRule(ruleDefinitions, id, rules);
        }
    }
    return new CompositeRule(subRules);
}

StringRule* parseString(std::string definition) {
    return new StringRule(definition[1]);
}

Rule* parseRule(std::vector<std::string>& ruleDefinitions, int idx, std::vector<Rule*>& rules) {
    if(rules[idx] != nullptr) {
        return rules[idx];
    }
    auto definition = ruleDefinitions[idx];
    if(definition[0] == '"') {
        rules[idx] = parseString(definition);
    } else {
        rules[idx] = parseComposite(definition, ruleDefinitions, rules);
    }
    return rules[idx];
}

int main() {
    std::vector<std::string> lines = readStrings("day19/input1.txt");
    std::vector<std::string> ruleDefinitions(lines.size());
    auto it = lines.begin();
    for(; !it->empty() && it != lines.end(); ++it) {
        auto pieces = split(*it, ": ");
        int idx = std::stoi(pieces[0]);
        ruleDefinitions[idx] = pieces[1];
    }
    
    std::vector<Rule*> rules(ruleDefinitions.size());
    Rule* ruleZero = parseRule(ruleDefinitions, 0, rules);

    int matches = 0;
    for(; it != lines.end(); ++it) {
        auto cursor = it->begin();
        auto end = it -> end();
        if(ruleZero->match(cursor, end) && cursor == end) {
            matches++;
        }
    }
    
    std::cout << matches << std::endl;
}