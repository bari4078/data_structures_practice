#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct 
{
    // declare head, tail, cur and other variables you need
    node *head;
    node *tail;
    int curr;
    int size;
} linkedList;

void init(linkedList* list)
{
    // implement initialization
    list->head = NULL;
    list->tail = NULL;
    list->curr = -1;
    list->size = 0;
}

void free_list(linkedList* list)
{
    // implement destruction of list
    node *now=list->head;
    while(now != NULL){
        node *temp = now->next;
        free(now);
        now=temp;
    }
    init(list);
}

void print(linkedList* list)
{
    // implement list printing
    node *temp=list->head;
    printf("[");
    if(list->curr == -1) printf("|");
    for(int i=0;i<list->size;i++){
        printf("%d ",temp->element);
        if(i==list->curr) printf("|");
        temp=temp->next;
    }
    printf("]\n");
}


void insert(int item, linkedList* list)
{
    // implement insert function
    if(list->curr == -1 && list->size == 0){
        node *new_node=(node*)malloc(sizeof(node));
        new_node->element = item;
        new_node->prev = NULL;
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
        list->curr = 0;
        list->size = 1;
        return;
    }
    else if(list->curr == -1){
        node *new_node=(node*)malloc(sizeof(node));
        new_node->element = item;
        new_node->next=list->head;
        list->head->prev=new_node;
        new_node->prev=NULL;
        list->head=new_node;
    }
    else if(list->curr == list->size -1){
        node *new_node=(node*)malloc(sizeof(node));
        new_node->element = item;
        new_node->next = NULL;
        new_node->prev=list->tail;
        list->tail->next=new_node;
        list->tail = new_node;
    }
    else{
        node *new_node=(node*)malloc(sizeof(node));
        new_node->element = item;
        node *temp=list->head;
        for(int i=0;i<list->curr;i++){
            temp=temp->next;
        } 
        
        new_node->next=temp->next;
        new_node->next->prev=new_node;
        new_node->prev=temp;
        temp->next=new_node;
    }
    list->curr++;
    list->size++;

    return;
}

int delete_cur(linkedList* list)
{
    // implement deletion of current index function
    if (list->size == 0 || list->curr >= list->size || list->head == NULL)
        return -1;
    node* cur_node = list->head;
    for (int i = 0; i < list->curr; i++) {
        cur_node = cur_node->next;
    }
        
    int out = cur_node->element;
    if(cur_node->prev)
        cur_node->prev->next = cur_node->next;
    else
        list->head = cur_node->next;
    if(cur_node->next)
        cur_node->next->prev = cur_node->prev;
    else
        list->tail = cur_node->prev;
    
    if (list->size == 1){
        list->curr = -1;
    }
    else if (cur_node->next != NULL) {}
    else {
        list->curr--;
    }        
     
    free(cur_node);
    list->size--;
    return out;
}

void append(int item, linkedList* list)
{
    // implement append function
    node *new_node=(node*)malloc(sizeof(node));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->element = item;
    new_node->next = NULL;
    if(list->size == 0){
        list->head=new_node;
        new_node->prev = NULL;
        list->curr=0;
    }
    else{
        new_node->prev = list->tail;
        list->tail->next = new_node;
    }
    
    list->tail=new_node;
    list->size++;
    return;
}

int size(linkedList* list)
{
    // implement size function
    return list->size;
}

void prev(int n, linkedList* list)
{
    // implement prev function
    if(list->curr < 0) return;
    list->curr = list->curr -n;
    if(list->curr < 0) list->curr = 0;
    return;
}

void next(int n, linkedList* list)
{
    // implement next function
    list->curr = list->curr + n;
    if(list->curr >= list->size) list->curr = list->size -1;
}

int is_present(int n, linkedList* list)
{
    // implement presence checking function
    node *now=list->head;
    while(now){
        if(now->element==n){
            return 1;
        }
        now=now->next;
    }
    return 0;
}

void clear(linkedList* list)
{
    // implement list clearing function
    node *now=list->tail;
    while(now){
        node *temp = now->prev;
        free(now);
        now = temp;
    }
    init(list);
}

void delete_item(int item, linkedList* list)
{
    // implement item deletion function
    node *target=list->head;
    int i=0;
    int found=0;
    while(target){
        if(target->element == item){
            found=1;
            break;
        }
        target = target->next;
        i++;
    }
    if(!found){
        printf("%d is not found\n",item);
        return;
    }
    int temp_curr=list->curr;
    list->curr = i;
    int trash = delete_cur(list);
    if(temp_curr == list->size){
        temp_curr--;
        list->curr=temp_curr;
    }
    else{
        list->curr=temp_curr;
    }
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    // implement swap function
    if(ind1 <0 || ind2<0 || ind1 >= list->size || ind2 >= list->size) return;
    node *node1=list->head,*node2=list->head;
    for(int i=0;i<ind1;i++){
        node1 = node1->next;
    }
    for(int i=0;i<ind2;i++){
        node2 = node2->next;
    }
    int ele;
    
    ele = node1->element;
    node1->element = node2->element;
    node2->element = ele;

    return;
}

// you can define helper functions you need