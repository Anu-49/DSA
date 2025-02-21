#include "sll.h"

int sl_delete_list(Slist **head)
{
    // check if list is empty or not
	if(*head == NULL){
        return FAILURE;
    }
    // assign every node to temp one by one and free the temp memory to delete list
    Slist *temp;
    while(*head != NULL){
        temp = *head;
        *head = (*head) -> link;
        free(temp);
    }
        return SUCCESS;
}