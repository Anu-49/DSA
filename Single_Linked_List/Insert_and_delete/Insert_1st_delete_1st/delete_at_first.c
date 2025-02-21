#include "sll.h"
// function to delete the first node element of the SLL
int sl_delete_first(Slist **head)
{
    // check if the list is empty
    if(*head == NULL){
        return FAILURE;
    }
    // traverse to the first node and free the temp memory (delete first)
    Slist *temp = *head;
    *head = (*head)->link;
    free(temp);
    return SUCCESS;
}