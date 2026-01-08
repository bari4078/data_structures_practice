#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    front_node = nullptr;
    rear_node = nullptr;
    // TODO: Initialize current_size to 0
    current_size = 0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    Node *new_node = new Node(item);
    if(empty()){
        rear_node = new_node;
        front_node = new_node;
        current_size++;
        return;
    }
    // TODO: Link the new node to the rear
    rear_node->next = new_node;
    // TODO: Update the rear_node
    rear_node = new_node;
    // TODO: Increment the current size
    current_size++;
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if(empty()){
        cout<<"Error: Tried to dequeue empty queue, -1 will be returned"<<endl;
        return -1;
    }
    // TODO: Store the data from the front node
    Node *to_delete = front_node;
    int out = front_node->data;
    // TODO: Update the front pointer to the next node
    // TODO: Update the rear pointer if the queue becomes empty
    if(current_size == 1){
        rear_node = front_node = nullptr;
    }
    else{
        front_node = front_node->next;
    }
    // TODO: Delete the old front node
    delete to_delete;
    // TODO: Decrement current_size
    current_size--;
    // TODO: Return the stored data
    return out;
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    Node *curr = front_node;
    while(curr){
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
    // TODO: Reset front and rear pointer
    front_node = nullptr;
    rear_node = nullptr;
    // TODO: Reset current_size to 0
    current_size = 0;
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if(empty()){
        cout<<"Error: Queue is empty, -1 will be returned"<<endl;
        return -1;
    }
    // TODO: Return the data from the front node without removing it
    return front_node->data;
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    if(empty()){
        cout<<"Error: Queue is empty, -1 will be returned"<<endl;
        return -1;
    }
    // TODO: Return the data from the back node without removing it
    return rear_node->data;
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    return (front_node == nullptr);
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    if(empty()){
        return "<|";
    }
    // TODO: Traverse the linked list from front
    string out = "<";
    Node *curr = front_node;
    while(curr){
        out += to_string(curr->data);
        if (curr->next) out += ", ";
        curr = curr->next;
    }
    out += "|";
    return out;
}
