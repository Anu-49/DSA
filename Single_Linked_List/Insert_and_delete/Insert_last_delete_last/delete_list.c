#include "sll.h"

int sl_delete_list(Slist **head)
{
    //check if list is empty
	if(*head == NULL){
        return FAILURE;
    }
    // traverse through every node and delete the nodes
    Slist *temp;
    while(*head != NULL){
        temp = *head;
        *head = (*head) -> link;
        free(temp);
    }
    return SUCCESS;
}