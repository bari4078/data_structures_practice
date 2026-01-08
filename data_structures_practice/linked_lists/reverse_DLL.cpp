#include <bits/stdc++.h>
#include "linkedList.h"
using namespace std;

node *reverse_recur(node *curr){
    if(curr == nullptr) return nullptr;
    swap(curr->prev,curr->next);
    if(curr->prev == nullptr) return curr;
    return reverse_recur(curr->prev);
}

node *reverse_2ptr(node *head){
    if(head == NULL || head->next == NULL) return head;
    node *curr=head;
    node *prev=NULL;
    while(curr != NULL){
        prev=curr->prev;
        curr->prev = curr->next;
        curr->next = prev;
        
        curr=curr->prev;
    }
    return prev->prev;
}

int main(){
    linkedList *list;
    init(list);
    for(int i=0;i<20;i++){
        insert(i,list);
    }
    print(list);
    list->head=reverse_recur(list->head);
    print(list);
    list->head=reverse_2ptr(list->head);
    print(list);

    return 0;
}