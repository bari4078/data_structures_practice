#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    capacity = initial_capacity;
    data = new int[capacity];
    front_idx = -1;
    rear_idx = -1;
    // TODO: Allocate memory for the array with the specified initial capacity
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    if((rear_idx + 1)%capacity == front_idx){
        resize(capacity*2);
    }
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
    if(empty()){
        front_idx = 0;
        rear_idx = 0;
    }
    else{
        rear_idx = (rear_idx + 1)%capacity;
    }
    data[rear_idx] = item;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if(empty()){
        cout<<"Error: Tried to dequeue from an empty queue, -1 will be returned"<<endl;
        return -1;
    }
    int out = data[front_idx];
    if(front_idx == rear_idx){
        front_idx = -1;
        rear_idx = -1;
    }
    else{
        // TODO: Decrement current_size and return the element at the front of the queue
        front_idx = (front_idx + 1)%capacity;
    }
    if(size() < capacity/4 && capacity > 2) resize(capacity/2);
    // TODO: Update front index
    // TODO: Return the dequeued element
    return out;
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    front_idx = -1;
    rear_idx = -1;
    capacity = 2;
    delete[] data;
    data = new int[capacity];
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    if(empty()) return 0;

    if(rear_idx >= front_idx) return rear_idx - front_idx +1;
    return (capacity - (front_idx - rear_idx) + 1);
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if(empty()){
        cout<<"Error: queue is empty, -1 will be returned"<<endl;
        return -1;
    }
    // TODO: Return the element at the front of the queue without removing it
    return data[front_idx];
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if(empty()){
        cout<<"Error: queue is empty, -1 will be returned"<<endl;
        return -1;
    }
    // TODO: Return the element at the back of the queue without removing it
    return data[rear_idx];
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    return front_idx == -1;
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    if(empty()) return "<|";
    string out = "<";
    int i = front_idx;
    while(1){
        out += to_string(data[i]);
        if(i == rear_idx) break;
        out += ", ";
        i = (++i) % capacity;
    }
    out += "|";
    return out;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    if(new_capacity < 2) new_capacity = 2;
    int *new_data = new int[new_capacity];
    // TODO: Copy elements from the old array to the new array
    int current_size = size();
    for(int i=0;i<current_size;i++){
        new_data[i] = data[(front_idx + i)%capacity];
    }
    // TODO: Delete the old array
    delete[] data;
    // TODO: Update the data pointer and capacity
    data = new_data;
    // TODO: Update front and rear indices
    front_idx = 0;
    rear_idx = current_size - 1;
    capacity = new_capacity;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}