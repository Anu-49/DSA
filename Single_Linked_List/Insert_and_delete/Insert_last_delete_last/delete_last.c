#include "sll.h"

int sl_delete_last(Slist **head)
{
    // check if list is empty or not
    if(*head == NULL){
        return LIST_EMPTY;
    }
    Slist *temp = *head;
    Slist *prev = NULL;
    // traverse through the list till the end of list
    while(temp->link!=NULL){
        prev = temp;
        temp = temp->link;
    }
    // If the list has more than one node
    if (prev != NULL) {
        prev->link = NULL;
    } 
    // If the list has only one node
    else {
        *head = NULL;
    }
    // Free the memory allocated to the last node
    free(temp);
    return SUCCESS;
}