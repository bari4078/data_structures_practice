#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;
const int INITIAL_TABLE_SIZE = 13;

const double LOAD_FACTOR_UPPER = 0.5;
const double LOAD_FACTOR_LOWER = 0.25;

const int C1 = 5;
const int C2 = 3;

const int WORD_SIZE = 10;

const int TOTAL_WORDS = 10000;
const int SEARCH_TEST_COUNT = 1000;

bool isPrime(int n) {
    if (n <= 1) return false;

    if(n<=3) return true;

    if(n%2 == 0 || n%3 == 0) return false;

    for (int i = 5; i * i <= n; i=i+6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int nextPrime(int n) {
    n++;
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

int prevPrime(int n) {
    n--;
    while (!isPrime(n)) {
        n--;
    }
    return n;
}



template<typename K, typename V>
struct HashNode{
    K key;
    V value;

    HashNode(K key, V value){
        this->key = key;
        this->value = value;
    }
};

enum CollisionMethod{
    CHAINING,
    DOUBLE_HASHING,
    CUSTOM_PROBING
};

template<typename K, typename V>
class HashTable{
    private:
        vector< list< HashNode <K,V> > > chainTable;

        vector<HashNode<K,V> *> probeTable;

        using Hasher = std::hash<K>;
        Hasher hasher;
        int currentSize;
        int elementCount;
        int initialSize;
        int lastResizedAtCount;

        int totalCollisions;

        CollisionMethod method;

        int hashFunctionChoice;

        HashNode<K,V>* DELETED;

        ull hash1(const K &key) {
            return (ull) hasher(key);
        }

        ull hash2(const K &key) {
            uint64_t x = (uint64_t) hasher(key);
            x += 0x9e3779b97f4a7c15ULL;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
            x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
            x = x ^ (x >> 31);
            return (ull) x;
        }

        ull getHash(K key){
            if(hashFunctionChoice == 1){
                return hash1(key);
            }
            return hash2(key);
        }
        
        ull auxHash(const K &key) {
            
            return 1 + (hash1(key) % (currentSize-1));
        }

        void rehash(int newSize){
            vector< list<HashNode<K,V> > > oldChain = chainTable;
            vector< HashNode<K,V>* > oldProbe = probeTable;
            
            int oldSize = currentSize;

            currentSize = newSize;
            elementCount = 0;
            lastResizedAtCount = 0;

            if(method == CHAINING){
                chainTable.assign(newSize, list<HashNode<K,V>>());

                for(int i=0;i<oldSize;i++){
                    for(auto &node:oldChain[i]){
                        insert(node.key,node.value);
                    }
                }
            }
            else{
                probeTable.assign(newSize,nullptr);
                for(int i=0;i<oldSize;i++){
                    if(oldProbe[i] != nullptr && oldProbe[i] != DELETED){
                        insert(oldProbe[i]->key, oldProbe[i]->value);
                        delete oldProbe[i];
                    }
                }
            }
        }

        void checkResizing(bool isInsertion){
            double loadFactor = getLoadFactor();

            if(isInsertion){
                lastResizedAtCount++;
                if(loadFactor > LOAD_FACTOR_UPPER && lastResizedAtCount >= (elementCount)/2){
                    rehash(nextPrime(currentSize*2));
                }
            }
            else{
                lastResizedAtCount++;
                if(loadFactor < LOAD_FACTOR_LOWER 
                    && currentSize > initialSize
                    && lastResizedAtCount >= (elementCount)/2)
                    {
                        rehash(prevPrime(currentSize/2));
                    }
            }
        }
    public:
        HashTable(int size, CollisionMethod m, int hashChoice){
            initialSize = size;
            currentSize = size;
            elementCount = 0;
            lastResizedAtCount = 0;
            method = m;
            hashFunctionChoice = hashChoice;

            totalCollisions = 0;
            
            DELETED = (HashNode<K,V>*) new char;

            if(method == CHAINING){
                chainTable.resize(currentSize);
            }
            else{
                probeTable.assign(currentSize, nullptr);
            }
        }
        
        int getTableSize(){
            return currentSize;
        }
        int getTotalCollsions(){
            return totalCollisions;
        }
        double getLoadFactor(){
            return (double) elementCount / currentSize;
        }

        bool insert(K key, V value){
            if(method == CHAINING){
                int index = getHash(key) % currentSize;
                if(!chainTable[index].empty()){
                    totalCollisions++;
                }
                for(auto &node:chainTable[index]){
                    if(node.key == key) return false;
                }
                chainTable[index].push_back(HashNode<K,V>(key,value));
    
            }
            else{
                ull h = getHash(key);
                ull aux = auxHash(key);
                int firstDeletedIndex = -1;
                for(int i=0;i< currentSize;i++){
                    int index;

                    if(method == DOUBLE_HASHING){
                        index = (h + i*aux) % currentSize;
                    } else{
                        index = (
                                    h + (ull) C1 * i * aux + (ull) C2 * i * i
                                ) % currentSize;
                    }
                    
                    if(probeTable[index] == nullptr){
                        if(firstDeletedIndex == -1){
                            probeTable[index] = new HashNode<K,V>(key,value);
                            break;
                        }
                        else{
                            probeTable[firstDeletedIndex] = new HashNode<K,V>(key,value);
                            break;
                        }
                    }
                    else if(probeTable[index] != DELETED && probeTable[index]->key == key){
                        return false;
                    }
                    else if(probeTable[index] == DELETED && firstDeletedIndex == -1){
                        firstDeletedIndex = index;
                    }
                    else if(probeTable[index] != DELETED){
                        totalCollisions++;
                    }
                }
            }
            elementCount++;
            checkResizing(true);
            return true;
        }

        int search(K key, int &totalHits){
            int hits = 0;

            if(method == CHAINING){
                int index = getHash(key) % currentSize;

                for(auto &nodes:chainTable[index]){
                    hits++;
                    if(nodes.key == key){
                        totalHits = hits;
                        return hits;
                    }
                }
            }
            else{
                ull h = getHash(key);
                ull aux = auxHash(key);

                for(int i=0;i<currentSize;i++){
                    hits++;
                    int index;
                    if(method == DOUBLE_HASHING){
                        index = (h + i*aux)%currentSize;
                    }
                    else{
                        index = (
                                    h + (ull) C1 * i * aux + (ull) C2 * i * i
                                ) % currentSize;
                    }

                    if(probeTable[index] == nullptr) break;
                    if(probeTable[index] != DELETED && probeTable[index]->key == key){
                        totalHits = hits;
                        return hits;
                    }
                }
            }
            totalHits = hits;
            return -1;
        }

        bool remove(K key){
            if(method == CHAINING){
                int index = getHash(key) % currentSize;

                for(auto curr = chainTable[index].begin();
                    curr != chainTable[index].end();
                    curr++ ){
                        if(curr->key == key){
                            chainTable[index].erase(curr);
                            elementCount--;
                            checkResizing(false);
                            return true;
                        }
                }
            }
            else{
                ull h = getHash(key);
                ull aux = auxHash(key);

                for(int i=0;i<currentSize;i++){
                    int index;
                    if(method == DOUBLE_HASHING){
                        index = (h + i*aux)%currentSize;

                    }
                    else{
                        index = (
                                    h + (ull) C1 * i * aux + (ull) C2 * i * i
                                ) % currentSize;
                    }

                    if(probeTable[index] == nullptr) return false;
                    if(probeTable[index] != DELETED && probeTable[index]->key == key){
                        delete probeTable[index];
                        probeTable[index] = DELETED;
                        elementCount--;
                        checkResizing(false);
                        return true;
                    }
                }
            }

            return false;
        }


};

string randomWord(int l){
    string word = "";
    for(int i=0;i<l;i++){
        word += 'a' + ( rand() % 25);
    }
    return word;
}

ull randomNumber(int l){
    return ((ull)rand() % nextPrime(100000));
}


int main() {
    vector<ull> nums;
    HashTable<ull,int> uniqueChecker(nextPrime(20001),CHAINING,1);

    while(nums.size() < 10000){
        ull num = randomNumber(10);
        int temp;
        int k = uniqueChecker.search(num,temp);

        if(k == -1){
            uniqueChecker.insert(num,nums.size()+1);
            nums.push_back(num);
        }

    }

    vector<int> searchIdx;

    for(int i=0;i<1000;i++){
        searchIdx.push_back(rand() % nums.size());
    }



    vector<CollisionMethod> methods = {CHAINING,DOUBLE_HASHING,CUSTOM_PROBING};

    for(int i=0;i<3;i++){
        if(i == 0)      cout<<"||--------Chaining-----------||\n";
        else if(i == 1) cout<<"||--------Double Hashing-----||\n";
        else if(i == 2) cout<<"||--------Custom Probing-----||\n";

        for(int hChoice = 1; hChoice <=2; hChoice++){
            HashTable<ull,int> demoTable(INITIAL_TABLE_SIZE,methods[i],hChoice);
            int count = 0;
            for(auto &w:nums){
                demoTable.insert(w,count + 1);
            }

            int totalHits = 0;
            for(auto idx:searchIdx){
                int hits = 0;
                demoTable.search(nums[ idx ],hits);
                totalHits += hits;
            }

            string methodName = (hChoice == 1) ? "Hash1" : "Hash2";
            
            cout<<methodName<<"||   Collisions: "<<demoTable.getTotalCollsions()
                <<"  Hits: "<<  (double)    totalHits/1000   <<"\n";
        }
        cout<<endl;
    }

    return 0;
}