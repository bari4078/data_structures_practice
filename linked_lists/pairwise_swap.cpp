#include <bits/stdc++.h>
using namespace std;
class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

Node *pairwiseSwap(Node *head){
    if(head == nullptr || head->next == nullptr){
        return head;//empty or 1 node, trivial
    }

    Node *curr=head;
    Node *prevN=nullptr;
    head= curr->next;

    while(curr != nullptr && curr->next != nullptr){
        Node *next=curr->next;
        Node *next_pair=curr->next->next;

        next->next = curr;
        if(prevN != nullptr)
            prevN->next=next;
        curr->next=next_pair;

        prevN=curr;
        curr=next_pair;
    }
    return head;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    
    // Creating the linked list:
  	// 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);

    head = pairwiseSwap(head);
    
    printList(head);

    return 0;
}