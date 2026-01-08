#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/


int main()
{
    freopen("test_input_1.txt", "r", stdin); // Test Case 1
    // freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;

    const int MAX_PATIENTS = 10005;
    int timestamps[MAX_PATIENTS] = {0};
    bool merged = false;
    for (int i = 1; i <= N; i++)
    {
        cout<<"Operation "<<i;
        // TODO: Edit here to add your own logic
        int op, id, timestamp;
        cin >> op;
        // After each operation, we will check the queue's size and capacity
        if(op == 1){
            cout<<" (Arrival ";
            cin>>id>>timestamp;
            cout<<id <<" "<<timestamp<<")"<<endl;
            if(!merged){
                if(Q1->empty() && Q2->empty()){
                    int choice = randomQueue();
                    if(choice == 1) Q1->enqueue(id);
                    else Q2->enqueue(id);
                    
                }
                else if(Q1->empty()){
                    Q1->enqueue(id);
                }
                else if(Q2->empty()){
                    Q2->enqueue(id);
                }
                else{
                    int t1 = timestamps[Q1->back()];
                    int t2 = timestamps[Q2->back()];
                    if(t1<=t2) Q1->enqueue(id);
                    else Q2->enqueue(id);
                }
            }
            else{
                Q->enqueue(id);
            }
            timestamps[id] = timestamp;
        }
        else if(op == 2){
            cin>>id>>timestamp;
            cout<<"(Leave "<<id<<" "<<timestamp<<")"<<endl;




        }
        else if(op == 3){
            cout<<"(Merge)"<<endl;

            vector<int> mergedQueue;

            while(!Q1->empty()){
                mergedQueue.push_back(Q1->front());
                Q1->dequeue();
            }
            while(!Q2->empty()){
                mergedQueue.push_back(Q2->front());
                Q2->dequeue();
            }

            int Tsize = mergedQueue.size();
            for(int i=0;i<Tsize;i++){
                for(int j=i;j<Tsize;j++){
                    if(timestamps[mergedQueue[i]] > timestamps[mergedQueue[j]]){
                        swap(mergedQueue[i],mergedQueue[j]);
                    }
                }
            }

            for(int i=0;i<Tsize;i++){
                Q->enqueue(mergedQueue[i]);
            }
            Q1->clear();
            Q2->clear();

            merged = true;
        }
        else if(op == 4){
            cout<<"(Split)"<<endl;

            int Tsize = Q->size();
            for(int i=0;i<Tsize;i++){
                if(i%2 == 0){
                    Q1->enqueue(Q->dequeue());
                }
                else{
                    Q2->enqueue(Q->dequeue());
                }
            }
            Q1->clear();
            merged = false;
        }
        else if(op == 5){
            cout<<"(Departure)"<<endl;
            if(!merged){
                    if(!Q1->empty() && !Q2->empty()){
                    int choice = randomQueue();
                    if(choice == 1){
                        Q1->dequeue();
                    }
                    else{
                        Q2->dequeue();
                    }
                }
                else if(!Q1->empty()) Q1->dequeue();
                else if(!Q2->empty()) Q2->dequeue();
            }
            else{
                if(!Q->empty()) Q->dequeue(); 
            }
        }

        cout << "Q1: " << Q1->toString() << endl;
        cout << "Q2: " << Q2->toString() << endl;
        cout << "Q : " << Q->toString() << endl;


        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    return 0;
}