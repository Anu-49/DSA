#include "sll.h"

/* Function to reverse the given single linked list using iteration method*/
int reverse_iter(Slist **head) 
{ 
    if(*head == NULL){
        return LIST_EMPTY;
    }
    Slist *temp = *head;
    Slist *p = NULL;
    Slist *n = NULL;
    while(temp != NULL){
        n = temp->link;
        temp->link = p;
        p = temp;
        temp = n;
    }
    *head = p;
    return SUCCESS;
} 

