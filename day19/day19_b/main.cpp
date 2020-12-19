#include <iostream>
#include "../../util.hpp"

class Rule {
public:
    virtual bool match(std::string::iterator& cursor, std::string::iterator& end) = 0;
    virtual void print(std::string prefix) = 0;
    virtual ~Rule() = default;
};

class Terminal: public Rule {
public:
    bool match(std::string::iterator& cursor, std::string::iterator& end) override {
        return cursor == end;
    }

    void print(std::string prefix) override {
        std::cout << prefix << std::endl;
    }

    ~Terminal() override = default;
};

class StringRule: public Rule {
public:
    explicit StringRule(char str, Rule* next): str(str), next(next) {}
    char str;
    Rule* next;
    bool match(std::string::iterator& cursor, std::string::iterator& end) override {
        if(cursor == end) {
            return false;
        }
        if(*(cursor++) != str) {
            return false;
        }
        return next->match(cursor, end);
    }

    void print(std::string prefix) override {
        next->print(prefix + str);
    }

    ~StringRule() override = default;
};

class CompositeRule: public Rule {
public:
    std::vector<Rule*> subRules;
    bool match(std::string::iterator &cursor, std::string::iterator &end) override {
        if(cursor == end) {
            return false;
        }
        auto startPoint = cursor;
        for(const auto& subRule: subRules) {
            cursor = startPoint;
            if(subRule->match(cursor, end)) {
                return true;
            }
        }
        return false;
    }

    void print(std::string prefix) override {
        for(int i = 0; i < subRules.size(); i++) {
            subRules[i]->print(prefix);
        }
    }

    ~CompositeRule() override = default;
};

Rule* parseRule(std::vector<std::string>& ruleDefinitions, int idx, Rule* next);

Rule* parseComposite(const std::string& definition, std::vector<std::string>& ruleDefinitions, int idx, Rule* next, int depth) {
    auto *newRule = new CompositeRule();
    auto ors = split(definition, " | ");
    std::vector<Rule*> subRules(ors.size());
    for(int i = 0; i < ors.size(); ++i) {
        auto nxt = next;
        auto ands = split(ors[i], " ");
        for(int j = ands.size() - 1; j >= 0; --j) {
            int id = std::stoi(ands[j]);
            if(id == idx) {
                if(depth != 200) {
                    nxt = parseComposite(definition, ruleDefinitions, id, nxt, depth + 1);
                }
            } else {
                nxt = parseRule(ruleDefinitions, id, nxt);
            }
        }
        subRules[i] = nxt;
    }
    newRule->subRules = subRules;
    if(subRules.size() == 1) {
        return subRules[0];
    }
    return newRule;
}

StringRule* parseString(std::string definition, Rule* next) {
    return new StringRule(definition[1], next);
}

Rule* parseRule(std::vector<std::string>& ruleDefinitions, int idx, Rule* next) {
    auto definition = ruleDefinitions[idx];
    if(definition[0] == '"') {
        return parseString(definition, next);
    } else {
        return parseComposite(definition, ruleDefinitions, idx, next, 0);
    }
}

int main() {
    std::vector<std::string> lines = readStrings("day19/input2.txt");
    std::vector<std::string> ruleDefinitions(lines.size());
    auto it = lines.begin();
    for(; !it->empty() && it != lines.end(); ++it) {
        auto pieces = split(*it, ": ");
        int idx = std::stoi(pieces[0]);
        ruleDefinitions[idx] = pieces[1];
    }
    ++it;
    Rule* ruleZero = parseRule(ruleDefinitions, 0, new Terminal);
    //ruleZero->print("");

    int matches = 0;
    for(; it != lines.end(); ++it) {
        auto cursor = it->begin();
        auto end = it -> end();
        if(ruleZero->match(cursor, end)) {
            matches++;
        }
    }
    
    std::cout << matches << std::endl;
}