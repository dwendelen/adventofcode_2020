#include <map>

template<typename T>
class set {
private:
    std::map<T, bool> map;

    class SetIterator {
    private:
        typename std::map<T, bool>::iterator parent;
    public:
        explicit SetIterator(typename std::map<T, bool>::iterator parent): parent(parent){}
        void operator++() {
            parent.operator++();
        }

        T operator*() {
            auto &pair = parent.operator*();
            return pair.first;
        }

        T *operator->() {
            auto *pPair = parent.operator->();
            return &pPair->first;
        }

        bool operator!=(SetIterator& other) {
            return parent != other.parent;
        }
    };

public:
    typedef SetIterator iterator;

    void operator+=(const T elem) {
        map[elem] = true;
    }

    void operator-=(const T elem) {
        map.erase(elem);
    }

    // Intersection
    void operator&=(set<T>& other) {
        auto it = map.begin();
        while (it != map.end()) {
            if (!other.contains(it->first)) {
                it = map.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Union
    void operator|=(set<T>& other) {
        for (auto o: other) {
            this->operator+=(o);
        }
    }

    size_t size() {
        return map.size();
    }

    bool contains(const T elem) const {
        return map.count(elem) == 1;
    }

    iterator begin() {
        return iterator(map.begin());
    }

    iterator end() {
        return iterator(map.end());
    }
};

