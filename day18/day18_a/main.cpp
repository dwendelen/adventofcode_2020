#include <stdexcept>
#include <iostream>
#include "../../util.hpp"

uint64_t evalChain(std::string::const_iterator &from, std::string::const_iterator &to);

/*
 *                  terminated by
 * LINE = C EOF
 * C = B (*|+ B)*   EOF )
 * B = P            EOF ) * +
 *   = N
 * N = (0-9)+       EOF ) * +
 * P = '(' C ')'    not needed
 */
int main() {
    std::vector<std::string> lines = readStrings("day18/input.txt");

    uint64_t sum = 0;
    for (const std::string &line: lines) {
        std::string withoutWhitespaces;
        for (const char c: line) {
            if (c != ' ') {
                withoutWhitespaces += c;
            }
        }
        const std::string constLine = withoutWhitespaces;
        auto from = constLine.begin();
        auto to = constLine.end();
        sum += evalChain(from, to);
    }

    std::cout << sum << std::endl;
}

uint64_t evalNumber(std::string::const_iterator &from, std::string::const_iterator &to) {
    uint64_t result = 0;
    while (from != to) {
        auto c = *from;
        if ('0' <= c && c <= '9') {
            result = 10 * result + (c - '0');
            ++from;
        } else if(c == ')' || c == '*' || c == '+') {
            break;
        } else {
            throw std::runtime_error(std::string("Unexpected char when parsing number: ") + c);
        }
    }
    return result;
}

uint64_t evalParentheses(std::string::const_iterator &from, std::string::const_iterator &to) {
    if(*from != '(') {
        throw std::runtime_error("Expected a (");
    }
    ++from;
    uint64_t result = evalChain(from, to);
    if(from == to || *from != ')') {
        throw std::runtime_error("Expected a (");
    }
    ++from;
    return result;
}

uint64_t evalNumberOrParentheses(std::string::const_iterator &from, std::string::const_iterator &to) {
    auto c = *from;
    if ('0' <= c && c <= '9') {
        return evalNumber(from, to);
    } else if(c == '(') {
        return evalParentheses(from, to);
    } else {
        throw std::runtime_error(std::string("Unexpected char when parsing number: ") + c);
    }
}

uint64_t evalChain(std::string::const_iterator &from, std::string::const_iterator &to) {
    uint64_t result = evalNumberOrParentheses(from, to);
    while(from != to) {
        auto c = *from;
        if (c == '+') {
            ++from;
            result += evalNumberOrParentheses(from, to);
        } else if (c == '*') {
            ++from;
            result *= evalNumberOrParentheses(from, to);
        } else if(c == ')') {
            break;
        } else {
            throw std::runtime_error(std::string("Unexpected char when parsing number: ") + c);
        }
    }
    return result;
}

