#include <bits/stdc++.h>
#include "linkedList.h"
using namespace std;
   
linkedList *merge_sorted_lists(linkedList *one,linkedList *two){
    linkedList *out=(linkedList*)malloc(sizeof(linkedList));
    init(out);
    node *p1=one->head,*p2=two->head;
    while(p1 != NULL && p2 != NULL){
        if(p1->element > p2->element){
            insert(p2->element,out);
            p2=p2->next;
        }
        else if(p1->element < p2->element){
            insert(p1->element,out);
            p1=p1->next;
        }
        else{
            insert(p2->element,out);
            p2=p2->next;
            p1=p1->next;
        }
    }
    while(p1 != NULL){
        insert(p1->element,out);
        p1=p1->next;
    }
    while(p2 != NULL){
        insert(p2->element,out);
        p2=p2->next;
    }
    return out;
}

int main(){
    linkedList *one=(linkedList*)malloc(sizeof(linkedList));
    linkedList *two=(linkedList*)malloc(sizeof(linkedList));
    init(one);
    init(two);

    insert(1,one);
    insert(3,one);
    insert(5,one);

    insert(2,two);
    insert(4,two);
    insert(5,two);
    insert(6,two);
    insert(8,two);
    linkedList *newll=merge_sorted_lists(one,two);
    print(newll);

    return 0;
}