#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct 
{
    int *array;
    // declare variables you need
    int curr_size;
    int curr;
    int capacity;
} arrayList;

void init(arrayList* list)
{
    // implement initialization
    list->curr_size=0;
    list->curr=-1;
    list->capacity=2;
    list->array=(int*)malloc(list->capacity*sizeof(int));
}

void free_list(arrayList* list)
{
    // implement destruction of list
    free(list->array);
    list->capacity=2;
    list->curr=-1;
    list->curr_size=0;
}

void increase_capacity(arrayList* list)
{
    // implement capacity increase
    printf("Capacity increased form %d to %d\n",list->capacity,list->capacity*2);
    list->capacity=2*list->capacity;
    int *aux=(int*)malloc(list->capacity*sizeof(int));
    for(int i=0;i<list->curr_size;i++){
        aux[i]=list->array[i];
    }
    free(list->array);
    list->array=aux;
}

void decrease_capacity(arrayList* list)
{
    // implement capacity decrease
    printf("Capacity decreased form %d to %d\n",list->capacity,list->capacity/2);
    list->capacity=ceil(0.5*list->capacity);
    int *aux=(int*)malloc(list->capacity*sizeof(int));
    for(int i=0;i<list->curr_size;i++){
        aux[i]=list->array[i];
    }
    free(list->array);
    list->array=aux;
}

void print(arrayList* list)
{
    // implement list printing
    printf("[");
    if(list->curr == -1) printf("|");
    for(int i=0;i<list->curr_size;i++){
        printf("%d ",list->array[i]);
        if(list->curr == i){
            printf("|");
        }
    }
    printf("]\n");
}

void insert(int item, arrayList* list)
{
    // implement insert function
    if(list->curr_size >= list->capacity / 2) increase_capacity(list);
    if (list->curr < -1 || list->curr >= list->curr_size) return;
    if (list->curr == -1) {
        list->array[0] = item;
        list->curr = 0;
        list->curr_size = 1;
        return;
    }    
    for(int i=list->curr_size;i>list->curr+1;i--){
        list->array[i]=list->array[i-1];
    }
    list->array[list->curr+1] = item;
    list->curr++;
    list->curr_size++;
    return;
}

int delete_cur(arrayList* list)
{
    // implement deletion of current index function
    if(list->curr == -1 || list->curr >=list->curr_size) return -1;

    int temp=list->array[list->curr];
    for(int i=list->curr;i<list->curr_size-1;i++){
        list->array[i]=list->array[i+1];
    }

    list->curr_size--;

    if (list->curr_size == 0) {
    list->curr = -1;
    }
    else if (list->curr == list->curr_size) {
        list->curr--;
    }

    if(list->curr_size <= list->capacity/4) decrease_capacity(list);
    return temp;
}

void append(int item, arrayList* list)
{
    // implement append function
    if(list->curr_size >= list->capacity / 2) increase_capacity(list);

    list->array[list->curr_size] = item;
    if(list->curr_size == 0){
        list->curr=0;
    }
    list->curr_size++;
}

int size(arrayList* list)
{
    // implement size function
    return list->curr_size;
}

void prev(int n, arrayList* list)
{
    // implement prev function
    if(list->curr <0) return;
    list->curr=list->curr-n;
    if(list->curr <0) list->curr=0;
}

void next(int n, arrayList* list)
{
    // implement next function
    list->curr = list->curr+n;
    if(list->curr >= list->curr_size) list->curr=list->curr_size-1;
}

int is_present(int n, arrayList* list)
{
    // implement presence checking function
    for(int i=0;i<list->curr_size;i++){
        if(list->array[i] == n) return 1;
    }
    return 0;
}

void clear(arrayList* list)
{
    // implement list clearing function
    free(list->array);
    list->capacity = 2;
    list->curr_size = 0;
    list->curr = -1;
    list->array = (int*)malloc(list->capacity * sizeof(int));
}

void delete_item(int item, arrayList* list)
{
    // implement item deletion function
    int found = 0;
    for(int i=0;i<list->curr_size;i++){
        if(list->array[i] == item){
            for(int j=i;j<list->curr_size-1;j++){
                list->array[j]=list->array[j+1];
            }
            found =1;
            break;
        }
    }
    if(!found){
        printf("%d was not found\n",item);
        return;
    }

    list->curr_size--;

    if (list->curr_size == 0) {
    list->curr = -1;
    }
    else if (list->curr == list->curr_size) {
        list->curr--;
    }

    if(list->curr_size <= list->capacity/4) decrease_capacity(list);
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    // implement swap function
    if(ind1 <0 || ind2<0 || ind1 >= list->curr_size || ind2 >= list->curr_size) return;
    int temp=list->array[ind1];
    list->array[ind1]=list->array[ind2];
    list->array[ind2]=temp;
}

// you can define helper functions you need