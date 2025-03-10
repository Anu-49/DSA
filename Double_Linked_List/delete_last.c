#include "dll.h"

int dl_delete_last(Dlist **head, Dlist **tail)
{
    if(*head == NULL){
        return FAILURE;
    }
    if(*head == *tail){
        Dlist *temp1 = *head;
        free(temp1);
        *head = NULL;
        *tail = NULL;
        return SUCCESS;
    }
    Dlist *temp = *tail;
    (temp->prev)->next = NULL; 
    free(temp);
    return SUCCESS;
}