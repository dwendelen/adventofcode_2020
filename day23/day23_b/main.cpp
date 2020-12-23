#include <vector>
#include <string>
#include <iostream>

class Node {
public:
    uint32_t number;
    Node *next;
    Node *minusOne;
};

const std::string example = "389125467";
const std::string input = "364297581";
const std::string &ref = input;

int main() {
    uint32_t max = 1000000;
    std::vector<Node> nodes(max);

    auto it = nodes.begin();
    for (char c: ref) {
        it->number = c - '0';
        ++it;
    }
    Node *one;
    for (auto it2 = nodes.begin(); it2 != nodes.begin() + 9; ++it2) {
        if (it2->number == 1) {
            it2->minusOne = &*(nodes.end() - 1);
            one = &*it2;
        } else {
            for (auto it3 = nodes.begin(); it3 != nodes.begin() + 9; ++it3) {
                if (it3->number == it2->number - 1) {
                    it2->minusOne = &*it3;
                }
            }
        }
    }
    it->number = 10;
    for (auto it3 = nodes.begin(); it3 != nodes.begin() + 9; ++it3) {
        if (it3->number == 9) {
            it->minusOne = &*it3;
        }
    }
    ++it;
    for (int i = 11; i <= max; i++) {
        it->number = i;
        it->minusOne = &*(it - 1);
        ++it;
    }
    (nodes.end() - 1)->next = &*nodes.begin();
    for (auto it2 = nodes.begin(); it2 != nodes.end() - 1; ++it2) {
        (it2)->next = &*(it2 + 1);
    }

    Node *current = &nodes[0];
    for (uint32_t i = 0; i < 10000000; i++) {
        Node *t1 = current->next;
        Node *t2 = t1->next;
        Node *t3 = t2->next;

        Node *dest = current->minusOne;
        while (dest == t1 || dest == t2 || dest == t3) {
            dest = dest->minusOne;
        }
        Node *b1 = t3->next;
        Node *b2 = dest->next;
        current->next = b1;
        dest->next = t1;
        t3->next = b2;

        current = current->next;
    }

    uint64_t num1 = one->next->number;
    uint64_t num2 = one->next->next->number;
    std::cout << num1 << ", " << num2 << " multiplied " << num1 * num2 << std::endl;
}