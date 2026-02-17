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

        vector<HashNode<K,V> *> * getProbeTable(){
            return &probeTable;
        }

        vector< list< HashNode<K,V> > >* getChainTable(){
            return &chainTable;
        }
        
        void printAllNodes(){
            if(method == CHAINING) return;
            for(auto nodes: probeTable){
                if(nodes != nullptr && nodes != DELETED){
                    cout<<nodes->value<<" ";
                }
            }
            cout<<endl;
        }

        HashNode<K,V>* getDeleted(){
            return DELETED;
        }
};

string randomWord(int l){
    string word = "";
    for(int i=0;i<l;i++){
        word += 'a' + ( rand() % 25);
    }
    return word;
}


void union_hash(HashTable<int,int> &table1, HashTable<int,int> &table2){
    HashTable<int,int> u_table(INITIAL_TABLE_SIZE,CUSTOM_PROBING,1);

    vector<HashNode<int,int> *>* firstTable = table1.getProbeTable();
    int temp;
    
    for(auto nodes: *firstTable){
        if(nodes == nullptr || nodes == table1.getDeleted()) continue;
        if(table1.search(nodes->key,temp) != -1)
            u_table.insert(nodes->key,nodes->value);
    }

    vector<HashNode<int,int> *>* secondTable = table2.getProbeTable();

    for(auto nodes: *secondTable){
        if(nodes == nullptr || nodes == table2.getDeleted()) continue;

        if(table2.search(nodes->key,temp) != -1)
            u_table.insert(nodes->key,nodes->value);
    }
    cout<<"Union: ";
    u_table.printAllNodes();
}

void intersect_hash(HashTable<int,int> &table1, HashTable<int,int> &table2){
    HashTable<int,int> u_table(INITIAL_TABLE_SIZE,CUSTOM_PROBING,1);

    vector<HashNode<int,int> *>* firstTable = table1.getProbeTable();
    vector<HashNode<int,int> *>* secondTable = table2.getProbeTable();
    int temp;
    for(auto nodes: *firstTable){
        if(nodes == nullptr || nodes == table1.getDeleted()) continue;
        if(table2.search(nodes->key,temp) != -1 && table1.search(nodes->key,temp) != -1)
            u_table.insert(nodes->key,nodes->value);
    }
    cout<<"Intersection: ";
    u_table.printAllNodes();
}

void diff_hash(HashTable<int,int> &table1, HashTable<int,int> &table2){
    HashTable<int,int> u_table(INITIAL_TABLE_SIZE,CUSTOM_PROBING,1);

    vector<HashNode<int,int> *>* firstTable = table1.getProbeTable();
    vector<HashNode<int,int> *>* secondTable = table2.getProbeTable();
    int temp;
    for(auto nodes: *firstTable){
        if(nodes == nullptr || nodes == table1.getDeleted()) continue;
        if(table1.search(nodes->key,temp) != -1 && table2.search(nodes->key,temp) == -1)
            u_table.insert(nodes->key,nodes->value);
    }
    cout<<"Difference (A-B):";
    u_table.printAllNodes();
}


int main(){
    int n;
    cin>>n;
    HashTable<int,int> A(INITIAL_TABLE_SIZE,CUSTOM_PROBING,1);
    while(n--){
        int k;
        cin>>k;
        A.insert(k,k);
    }

    int m;
    cin>>m;
    HashTable<int,int> B(INITIAL_TABLE_SIZE,CUSTOM_PROBING,2);

    while(m--){
        int k;
        cin>>k;
        B.insert(k,k);
    }

    union_hash(A,B);
    intersect_hash(A,B);
    diff_hash(A,B);
}