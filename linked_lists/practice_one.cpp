#include <bits/stdc++.h>
using namespace std;
class Node{
public:
    int value;
    Node* next;
};

Node *append(Node *head,int data){
    if(head == nullptr){
        Node *new_node = new Node{data, nullptr};
        head=new_node;
        new_node->next=head;
        return head;
    }
    else{
        Node *new_node = new Node{data, nullptr};
        Node *curr=head;
        while(curr->next != head){
            curr=curr->next;
        }
        curr->next=new_node;
        new_node->next=head;
        return head;
    }
}

void printLL(Node *head){
    Node *curr=head;
    if(head==nullptr) return;
    do{
        cout<<curr->value<<" ";
        curr=curr->next;
    }while(curr != head);
    cout<<endl;
}

Node *exchange(Node* head){
    if(head == nullptr) return nullptr;
    Node *last=head;
    Node *prev_last;
    while(last->next != head){
        prev_last=last;
        last = last->next;
    }

    last->next=head->next;
    prev_last->next=head;
    head->next=last;
    head=last;
    return head;
}

int main()
{
    Node *head=nullptr;
    for(int i=0;i<14;i++){
        head=append(head,i);
    }
    printLL(head);
    head=exchange(head);
    printLL(head);
}