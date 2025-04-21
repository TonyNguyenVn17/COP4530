#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <vector>
#include <string>

template<typename K, typename V>
class HashMap {
    private:
        struct Entry {
            K key;
            V value;
            Entry(const K& k, const V& v) : key(k), value(v) {}
        };

        std::vector<std::vector<Entry>> myHashTable;
        int size, capacity;

        int hash(const K& key);
        void rehash();

    public:
        HashMap(int initialCap = 16);

        void insert(const K& key, const V& value);
        V& getValue(const K& key);
        bool remove(const K& key);
        bool contains(const K& key);
        int getSize();
        std::vector<K> getKeys();
};

#include "Hashmap.tpp"

#endif 
