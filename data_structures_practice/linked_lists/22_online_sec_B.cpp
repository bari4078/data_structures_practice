//#include "arraylist.h"
#include "linkedlist.h"
#include <stdio.h>

// void skip(arrayList *list){
//     prev(1,list);
// }

// void swap_with(arrayList *list,int idx){
//     swap_ind(list->curr,idx,list);
// }

// void discard(arrayList *list){
//     delete_cur(list);
// }

void skip(linkedList *list){
    prev(1,list);
}

void swap_with(linkedList *list,int n){
    swap_ind(list->curr,n,list);
}

void discard(linkedList *list){
    delete_cur(list);
}

int main()
{
    const char* input_filename= "books_b.txt";
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

    //arrayList books;
    //init(&books);
    linkedList books;
    init(&books);
    int i;
    for (i=0; i<number_of_books; i++)
    {
        int book_id;
        fscanf(file, "%d", &book_id);
        append(book_id,&books);
    }

    next(books.size,&books);
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
            swap_with(&books, param);
            // use printf here
            printf("Swapped %d with %d\n",books.curr,param);
        }
        else if (func == 3)
        {
            discard(&books);
            // use printf here
            printf("Discarded book\n");
        }
        print(&books);
    }


    clear(&books);
    fclose(file);
    return 0;
}