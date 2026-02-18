V* getRef(K key) {
    if (method == CHAINING) {
        int index = getHash(key) % currentSize;

        for (auto &node : chainTable[index]) {
            if (node.key == key) {
                return &(node.value); // Return the memory address of the value
            }
        }
    } 
    else {
        ull h = getHash(key);
        ull aux = auxHash(key);

        for (int i = 0; i < currentSize; i++) {
            int index;
            if (method == DOUBLE_HASHING) {
                index = (h + i * aux) % currentSize;
            } else {
                index = (h + (ull)C1 * i * aux + (ull)C2 * i * i) % currentSize;
            }

            if (probeTable[index] == nullptr) break; // Key definitely not here
            
            if (probeTable[index] != DELETED && probeTable[index]->key == key) {
                return &(probeTable[index]->value); // Return address of the value
            }
        }
    }
    return nullptr; // Key not found
}
