#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    Node * next;

    Node(int n){
        this->data=n;
        this->next=nullptr;
    }
};

void print_list(Node * head){
    if(head == nullptr){ 
        cout<<endl;return;
    }
    cout<<head->data<<" ";
    head = head->next;
    print_list(head);    
}

bool search_list(Node * head, int key){
    Node * curr = head;
    while(curr != nullptr){
        if(curr->data == key) return true;
        curr = curr->next;
    }
    return false;
}

int length_list(Node * head){
    int size = 0;
    Node* curr=head;
    while(curr != nullptr){
        size++;
        curr = curr->next;
    }
    return size;
}

Node * insert_at_begining(Node* head, int new_data){
    Node * new_node = new Node(new_data);
    new_node->next = head;
    return new_node;
}

Node * insert_at_end(Node* head, int new_data){
    Node * new_node = new Node(new_data);
    Node * ptr= head;
    if(ptr == nullptr) return new_node;
    while(ptr->next != nullptr){
        ptr = ptr->next;
    }       
    ptr->next = new_node;
    return head;
}

Node *insert(Node * head, int new_data, int pos){
    if(pos == 1) return insert_at_begining(head,new_data);
    int i=1;

    Node * temp = head;
    while(i < pos-1 && temp != nullptr){
        temp = temp->next;
        i++;
    }
    if(temp == nullptr) return insert_at_end(head,new_data);
    Node * new_node = new Node(new_data);
    new_node->next = temp->next;
    temp->next=new_node;
    return head;
}

Node * delete_node(Node* head,int pos){
    int size = length_list(head);
    if(pos == 1){
        if(head == nullptr) return head;
        Node *temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    else if(pos > size || pos<1) return head;
    else if(pos == size){
        int i=1;
        Node * temp=head;
        while(i < size-1){
            temp = temp->next;
            i++;
        }
        Node * temp2 = temp->next;
        temp->next = nullptr;
        delete temp2;
        return head;
    }
    else{
        int i=1;
        Node * temp=head;
        while(i < pos-1){
            temp = temp->next;
            i++;
        }
        Node * temp2 = temp->next;
        temp->next = temp2->next;
        delete temp2;
        return head;
    }
}

Node * update_node(Node * head, int pos, int new_data){
    int i=1;
    Node * temp = head;
    while(i<pos){
        temp = temp->next;
        i++;
    }
    if(pos < 1 || pos > length_list(head)) return head;
    temp->data = new_data;
    return head;
}

Node * reverse(Node * head){
    Node *prev=nullptr,*curr=head,*next=nullptr;
    while(curr != nullptr){
        next = curr->next;
        curr->next = prev;
        prev=curr;
        curr=next;
    }
    return prev;
}

//recursive reverse
Node * reverse_recur(Node * head){
    //last node ba empty list hole return
    if(head == nullptr || head->next == nullptr) return head;
    //baki part reverse korbo & assume korbo j reversed
    Node * rest = reverse_recur(head->next);
    //head er porer element k head e point korabo
    head->next->next=head;
    head->next = nullptr;
    return rest;
}

int getNth(Node * head, int k){
    int i=1;
    Node * curr=head;
    while(i < k && curr != nullptr){
        i++;
        curr=curr->next;
    }
    if(i == k) return curr->data;
    return -1;
}

int getN_from_last(Node * head,int n){
    Node *ref_ptr=head;
    Node *end_ptr=head;
    int i;
    for(i=1;i<n;i++){
        end_ptr=end_ptr->next;
        if(end_ptr == nullptr) return -1;
    }
    while(end_ptr->next != nullptr){
        i++;
        end_ptr=end_ptr->next;
        ref_ptr=ref_ptr->next;
    }
    
    return ref_ptr->data;
}

int main(){
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next= new Node(30);
    head->next->next->next = new Node(23);
    print_list(head);

    cout<<"**** "<<search_list(head,30)<<endl;
    cout<<"**** "<<search_list(head,45)<<endl;
    cout<<"size of list: "<<length_list(head)<<endl;

    head = insert_at_begining(head, 1111);
    print_list(head);

    head = insert_at_end(head,2222);
    print_list(head);
    cout<<"size of list: "<<length_list(head)<<endl;

    head = insert(head,3333,3);
    print_list(head);
    cout<<"size of list: "<<length_list(head)<<endl;

    head = insert(head,8888,9);
    print_list(head);
    cout<<"size of list: "<<length_list(head)<<endl;

    head = delete_node(head,1);
    print_list(head);
    cout<<"size of list: "<<length_list(head)<<endl;

    head = delete_node(head,2);
    print_list(head);
    cout<<"size of list: "<<length_list(head)<<endl;

    head = delete_node(head,6);
    print_list(head);
    cout<<"size of list: "<<length_list(head)<<endl;

    head = update_node(head,2,655654);
    print_list(head);
    cout<<"size of list: "<<length_list(head)<<endl;

    head = reverse(head);
    cout<<"Reversed list: ";
    print_list(head);

    head = reverse_recur(head);
    cout<<"Reversed list: ";
    print_list(head);

    cout<<"value at 3: "<<getNth(head,3)<<endl;
    cout<<"value at 8: "<<getNth(head,8)<<endl;

    cout<<"value at 2 from the end: "<<getN_from_last(head,2)<<endl;
    cout<<"value at 20 from the end: "<<getN_from_last(head,20)<<endl;
    return 0;
}