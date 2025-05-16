//#include "arraylist.h"
#include "linkedlist.h"
#include <stdio.h>

// void reverse(arrayList *list){
//     int i=0,j=list->curr_size-1;
//     while(i<j){
//         int temp=list->array[i];
//         list->array[i]=list->array[j];
//         list->array[j]=temp;
//         i++;
//         j--;
//     }
// }

void reverse(linkedList *list){
    node *last=list->head;
    while(last != NULL && last->next != NULL){
        last = last->next;
    }
    if(last == NULL) return;

    node *left=list->head;
    while(left != last && last->prev != left && left && last){
       int temp=left->element;
       left->element=last->element;
       last->element=temp;

       left=left->next;
       last=last->prev; 
    }
}

int main()
{
    const char* input_filename= "books.txt";
    FILE *file = fopen(input_filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    
    int number_of_books;
    const int CAPACITY = 10;
    fscanf(file, "%d", &number_of_books);

    //arrayList list;
    //init(&list);
    linkedList list;
    init(&list);
    int i;
    for (i=0; i<number_of_books; i++)
    {
        int book_id;
        fscanf(file, "%d", &book_id);
        append(book_id,&list);
    }
    print(&list);
    printf("\n");

    // implement this function
    reverse(&list);

    printf("Reveresed list: ");
    print(&list);


    clear(&list);
    fclose(file);
    return 0;
}