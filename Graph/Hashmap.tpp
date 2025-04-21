#ifndef _HASHMAP_T_
#define _HASHMAP_T_

// Constructors ---------------------
template<typename K, typename V>
HashMap<K, V>::HashMap(int initialCap) : myHashTable(initialCap), size(0), capacity(initialCap) { // initialize all values

}

template<typename K, typename V>
int HashMap<K, V>::hash(const K& key) {
    return std::hash<K>{}(key) % capacity; // hash our key - only works if the key's type has std::hash defined
}

// Get a map value if you know its key
template<typename K, typename V>
V& HashMap<K, V>::getValue(const K& key) {
    int idx = hash(key);

    // iterate over the bucket and check for its key
    for (Entry& entry : myHashTable[idx]) {
        if (entry.key == key) { return entry.value; }
    }
    throw std::out_of_range("Key doesn't exist!");
}

// Insert a new map key-value pair
template<typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value) {
    if (size > capacity) { rehash(); } // rehash whole table in case of overflow

    int idx = hash(key); // hash the key

    // loop over all entry in the same "bucket" 
    for (Entry& entry : myHashTable[idx]) {
        if (entry.key == key) {
            entry.value = value;  // update value if key already exist
            return;
        }
    }

    // else, push new key into hash table and increase size
    myHashTable[idx].push_back(Entry(key, value)); size++;
}

// Check if a key is available
template<typename K, typename V>
bool HashMap<K, V>::contains(const K& key) {
    int idx = hash(key);

    // loop through the bucket and check if key exist
    for (Entry& entry : myHashTable[idx]) {
        if (entry.key == key) {
            return true;
        }
    }
    return false;
}

// Remove a key if it exists
template<typename K, typename V>
bool HashMap<K, V>::remove(const K& key) {
    int idx = hash(key);
    std::vector<Entry>& bucket = myHashTable[idx];

    // loop through the bucket and remove the key-value pair if it's found
    for (typename std::vector<Entry>::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (it->key == key) {
            bucket.erase(it); size--;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
int HashMap<K, V>::getSize() {
    return size;
}

template<typename K, typename V>
std::vector<K> HashMap<K, V>::getKeys() {
    std::vector<K> keys;
    for (std::vector<Entry>& bucket : myHashTable) {
        for (Entry& entry : bucket) {
            keys.push_back(entry.key);
        }
    }
    return keys;
}

// Helper function ----------------------------------------------------
// Rehash and increase capacity of map in case it overflow;
template<typename K, typename V>
void HashMap<K, V>::rehash() {
    // double the capacity
    capacity *= 2;
    std::vector<std::vector<Entry>> newTable(capacity);

    // iterate over all buckets and rehash the entries
    for (std::vector<Entry>& bucket : myHashTable) {
        for (Entry& entry : bucket) {
            int idx = std::hash<K>{}(entry.key) % capacity; // rehash to new size of map
            newTable[idx].push_back(Entry(entry.key, entry.value)); // insert back to new table
        }
    }

    myHashTable = newTable; // replace the old hash table
}

#endif