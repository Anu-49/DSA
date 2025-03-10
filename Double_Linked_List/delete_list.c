#include "dll.h"

int dl_delete_list(Dlist **head, Dlist **tail)
{
    if(*head == NULL){
        return FAILURE;
    }
    Dlist *temp = *head;
    Dlist *temp1 = NULL;
    while(temp != NULL){
        temp1 = temp->next;
        free(temp);
        temp = temp1;
    }
    *head = NULL;
    *tail = NULL;
    return SUCCESS;
}