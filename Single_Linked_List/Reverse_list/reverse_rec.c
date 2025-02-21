#include "sll.h"

/* Function to reverse the given single linked list using recursive method*/
int reverse_recursive(Slist ** head)
{
    if(*head == NULL){
        return LIST_EMPTY;
    }
    if((*head)->link == NULL){
        return SUCCESS;
    }
    Slist *temp = (*head)->link;
    reverse_recursive(&temp);
    (*head)->link->link = *head;
    (*head)->link = NULL;
    *head = temp;
    
    return SUCCESS;
}