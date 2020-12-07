#include "../../util.hpp"
#include <vector>
#include <regex>
#include <iostream>

class Type;

class Content;

class Content {
public:
    int amount;
    std::string type;

    Content(int amount, std::string type) : amount(amount), type(type) {}
};

class Type {
public:
    std::string name;
    std::vector<Content> content;

    Type() = default;
    Type(std::string name, std::vector<Content> content) : name(name), content(content) {}

    int nbOfOtherBags(std::map<std::string, Type> types) {
        int i = 1;
        for(auto &c: content) {
            Type &type = types[c.type];
            i += c.amount * type.nbOfOtherBags(types);
        }
        return i;
    }
};

Type parseType(const std::string& line);
std::vector<Content> parseContent(const std::string& string);

void visit(std::map<std::string, Type> types, std::string name, std::map<std::string, bool>& outer);

std::regex typeRegex(R"((\w* \w*) bags contain ([^\.]*)\.)");
std::regex contentRegex(R"(, (\d*) (\w* \w*) bags?)");

int main() {
    std::vector<std::string> lines = readStrings("day07/input.txt");

    std::map<std::string, Type> types;
    for (auto &str: lines) {
        Type type = parseType(str);
        types[type.name] = type;
    }

    int bags = types["shiny gold"].nbOfOtherBags(types);

    std::cout << bags - 1 << std::endl;

    return 0;
}


Type parseType(const std::string& line) {
    std::smatch match;
    if (!std::regex_match(line, match, typeRegex)) {
        throw std::runtime_error("Regex not matching");
    }

    return Type(match[1], parseContent(match[2]));
}

std::vector<Content> parseContent(const std::string& string) {
    std::string string2 = ", " + string;

    auto pieces_begin = std::sregex_iterator(string2.begin(), string2.end(), contentRegex);
    auto pieces_end = std::sregex_iterator();

    std::vector<Content> result;

    for (std::sregex_iterator i = pieces_begin; i != pieces_end; ++i) {
        result.emplace_back(std::stoi((*i)[1]), (*i)[2]);
    }

    return result;
}