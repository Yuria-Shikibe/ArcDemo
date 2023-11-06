#pragma once
#include <unordered_map>

template <class K, class V, class Hasher = std::hash<K>, class KeyEqualOperator = std::equal_to<K>,
    class Alloc = std::allocator<std::pair<const K, V>>>
class HashMap : protected std::unordered_map<K, V, Hasher, KeyEqualOperator, Alloc>{
public:
    void put(const K& k, const V& v){
        this->insert_or_assign(k, v);
    }
};

