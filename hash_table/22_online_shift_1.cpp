#include <bits/stdc++.h>
using namespace std;

double PROBES;
const double LOAD_FACTOR_LOWER = 0.2; 

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


class MemoryManager{
    private:
        struct HashNode{
            int key;
            int value;
            
            HashNode(int key, int value){
                this->key = key;
                this->value = value;
            }
        };


        vector<HashNode*> table;
        int currentSize;
        HashNode* DELETED;
        int deletions;
        int elementCount;
        int probeCount;
        int probes;
        int initialSize;

        int hash(int key){
            return key;
        }
        int getTableSize(){
            return currentSize;
        }
        
        double getLoadFactor(){
            return (double) elementCount / currentSize;
        }
        void rehash(int newSize,bool isInsertion){
            if(isInsertion){
                cout<<"--- Rehash Triggered: BEFORE --- \n";
                cout<<"Table Size: "<<currentSize<<"\n";
                cout<<"Active Processes: "<<elementCount<<"\n";
                cout<<"Load Factor: "<<getLoadFactor()<<"\n";
                cout<<"Max Probe Sequence: "<<probeCount<<"\n";


            }
            if(newSize < initialSize) return;
            int oldSize = currentSize;
            auto oldProbe = table;
            currentSize = newSize;
            deletions = 0;


            table.assign(newSize,nullptr);
            for(int i=0;i<oldSize;i++){
                if(oldProbe[i] != nullptr && oldProbe[i] != DELETED){
                    insert(oldProbe[i]->key, oldProbe[i]->value);
                    delete oldProbe[i];
                }
            }

            if(isInsertion){
                cout<<"--- Rehash Triggered: After --- \n";
                cout<<"Table Size: "<<currentSize<<"\n";
                cout<<"Active Processes: "<<elementCount<<"\n";
                cout<<"Load Factor: "<<getLoadFactor()<<"\n";
                cout<<"Max Probe Sequence: "<<probeCount<<"\n";
            }
        }

        void checkResizing(bool isInsertion){
            double loadFactor = getLoadFactor();

            if(isInsertion){
                if(probes > PROBES){
                    rehash(nextPrime(currentSize*2),true);
                }
            }
            else{
                deletions++;
                if(deletions%5==0 && loadFactor <=LOAD_FACTOR_LOWER)
                    {
                        rehash(prevPrime(currentSize/2),false);
                    }
            }
        }

public:

        MemoryManager(int size= 13){
            currentSize = size;
            probeCount = -1;
            elementCount = 0;
            deletions = 0;
            DELETED = (HashNode*) new char;
            initialSize = size;
            table.assign(size,nullptr);
        }
        bool insert(int key,int value){
            int h = hash(key);
            int firstDeletedIndex = -1;
            probes = 0;
            int index;
            for(int i=0;i< currentSize;i++){
                index = (h + i*i) % getTableSize();
                
                if(table[index] == nullptr){
                    if(firstDeletedIndex == -1){
                        table[index] = new HashNode(key,value);
                        break;
                    }
                    else{
                        table[firstDeletedIndex] = new HashNode(key,value);
                        break;
                    }
                }
                else if(table[index] != DELETED && table[index]->key == key){
                    return false;
                }
                else if(table[index] == DELETED && firstDeletedIndex == -1){
                    firstDeletedIndex = index;
                }
                else if(table[index] != DELETED){
                    probes++;
                }
            }
        cout<<"ALLOCATE <"<<key<<">: Inserted at index <"<<index<<"> (probes: <"<<probes<<">)"<<endl; 
        elementCount++;
        probeCount = max(probes,probeCount);
        checkResizing(true);
        return true;
    }

    bool remove(int key){
                int h = hash(key);

                for(int i=0;i<currentSize;i++){
                    int index = (h + i*i) % getTableSize();
                    if(table[index] == nullptr) return false;
                    if(table[index] != DELETED && table[index]->key == key){
                        delete table[index];
                        table[index] = DELETED;
                        elementCount--;
                        checkResizing(false);
                        cout<<"FREE <"<<key<<">: Freed from index <"<<index<<">\n"; 
                        return true;
                    }
                }
            

            return false;
        }
};

int main(){
    int n,q;
    cin>>n>>PROBES>>q;
    MemoryManager manager(n);
    while(q--){
        string op;
        cin>>op;
        if(op == "ALLOCATE"){
            int k;
            cin>>k;
            manager.insert(k,k);

        }
        else{
            int k;
            cin>>k;
            manager.remove(k);
        }
    }
}