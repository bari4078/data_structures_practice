//#include "arraylist.h"
#include "linkedlist.h"
#include <stdio.h>

// void skip(arrayList *list){
//     if(list->curr < list->curr_size)
//         list->curr++;
// }

// void move_and_shift(arrayList *list,int n){
//     int now=list->curr;
//     if(n>now){
//         int key=list->array[now];
//         for(int i=now;i<n;i++){
//             list->array[i]=list->array[i+1];
//         }
//         list->array[n]=key;
//     }
//     else if(n<now){
//         int key=list->array[now];
//         for(int i=now;i>n;i--){
//             list->array[i]=list->array[i-1];
//         }
//         list->array[n]=key;
//     }
// }

// void discard(arrayList *list){
//     delete_cur(list);
//     if(list->curr > list->curr_size){
//         list->curr=list->curr_size-1;
//     }
// }


void skip(linkedList *list){
    if(list->curr < list->size)
        list->curr++;
}

void move_and_shift(linkedList *list,int n){
    int i=0;
    node *to_move=list->head;

    while(i<list->curr){
        to_move=to_move->next;
        i++;
    }

    i=0;
    node *pos_insert=list->head;
    while(i<n){
        pos_insert=pos_insert->next;
        i++;
    }

    //changing to_move links;
    if(to_move->next)
        to_move->next->prev=to_move->prev;
    else{
        //to move is tail
    }

    if(to_move->prev)
        to_move->prev->next=to_move->next;
    else{
        //to move is head
    }

    //inserting to_move
    if(pos_insert->next){
        pos_insert->next->prev=to_move;
    }
    else{
        //pos_insert tail
    }
    
    if(to_move->next)to_move->next=pos_insert->next;
    else{
        //to_move last node
    }
    pos_insert->next=to_move;
    to_move->prev=pos_insert;
}

void discard(linkedList *list){
    delete_cur(list);
    if(list->curr > list->size){
        list->curr=list->size-1;
    }
}


int main()
{
    const char* input_filename= "books_c.txt";
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

    // arrayList books;
    // init(&books);
    linkedList books;
    init(&books);
    int i;
    for (i=0; i<number_of_books; i++)
    {
        int book_id;
        fscanf(file, "%d", &book_id);
        append(book_id,&books);
    }
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
            printf("Skipped\n");
        }
        else if (func == 2)
        {
            move_and_shift(&books, param);
            // use printf here
            printf("Moved from %d to %d\n",books.curr,param);
        }
        else if (func == 3)
        {
            discard(&books);
            // use printf here
            printf("Discarded\n");
        }
        print(&books);
    }


    clear(&books);
    fclose(file);
    return 0;
}