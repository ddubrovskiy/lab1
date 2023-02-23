#ifndef LAB1_HASH_H
#define LAB1_HASH_H
#include "Struct.h"

template<typename T>
inline void hashCombine(std::size_t& seed, const T& val) {
    seed ^= std::hash<T>()(val) + 0x9e3379b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hashVal(std::size_t& seed, const T& val) {
    hashCombine(seed, val);
}

template<typename T, typename... Types>
inline void hashVal(std::size_t& seed, const T& val, const Types &...args) {
    hashCombine(seed, val);
    hashVal(seed, args...);
}

template<typename... Types>
inline std::size_t hashVal(const Types &...args) {
    std::size_t seed = 0;
    hashVal(seed, args...);
    return seed;
}

struct hash {
    size_t operator()(const Edge& edge) const {
        if (edge.edgeNodes.first <= edge.edgeNodes.second) {
            return hashVal(edge.edgeNodes.first, edge.edgeNodes.second);
        }
        else {
            return hashVal(edge.edgeNodes.second, edge.edgeNodes.first);
        }
    }
};

#endif //LAB1_HASH_H
