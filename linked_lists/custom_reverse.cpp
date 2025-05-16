#include <bits/stdc++.h>
#include "linkedList.h"
using namespace std;

void skip(linkedList *list){
    list->curr--;
    if(list->curr <0) list->curr=-1;
}


void move_and_shift(linkedList *list,int n){
    int idx1=list->curr,indx2=0;
    node *curr=list->head;
    while(curr != NULL){
        if(curr->element == n){
            break;
        }
        indx2++;
        curr=curr->next;
    }
    if(indx2 >= list->size) return;
    if(idx1 == indx2) return;
    swap_ind(idx1,indx2,list);
}

void discard(linkedList *list){
    delete_cur(list);
    skip(list);
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
    printf("number_of_books: %d\n", number_of_books);

    linkedList books;
    init(&books);
    // LinkedList books;
    // init_linkedlist(&books);
    int i;
    for (i=0; i<number_of_books; i++)
    {
        int book_id;
        fscanf(file, "%d", &book_id);
        append(book_id,&books);
    }
    next(i,&books);//curr k last e nilam

    print(&books);
    printf("\n");

    int func, param;
    while (number_of_books--)
    {
        fscanf(file, "%d %d", &func, &param);
        if (func == 1)
        {
            skip(&books);
            // use printf here
        }
        else if (func == 2)
        {
            move_and_shift(&books, param);
            // use printf here
        }
        else if (func == 3)
        {
            discard(&books);
            // use printf here
        }
        print(&books);
    }


    free_list(&books);
    fclose(file);
    return 0;
}