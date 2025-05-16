#include "arraylist.h"
// #include "linkedlist.h"
#include <stdio.h>

void 


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

    arrayList books;
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


    clear(&books);
    fclose(file);
    return 0;
}