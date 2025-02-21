#include "sll.h"
/* Function to get the middle of the linked list*/
int find_mid(Slist *head, int *mid) 
{ 
    if(head == NULL){
        return LIST_EMPTY;
    }
    Slist *fast_ptr = head;
    Slist *slow_ptr = head;
    while(fast_ptr != NULL && fast_ptr->link != NULL){
        slow_ptr = slow_ptr->link;
        fast_ptr = fast_ptr->link->link;
    }
    *mid = slow_ptr->data;
    return SUCCESS;
} 
