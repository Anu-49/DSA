#include "dll.h"

int dl_delete_first(Dlist **head, Dlist **tail)
{
    if(*head == NULL){
        return FAILURE;
    }
    if((*head)->next == NULL){
        free(*head);
        *head = NULL;
        *tail = NULL;
        return SUCCESS;
    }
    Dlist *temp = *head;
    *head = temp->next;
    free(temp);
    (*head)->prev = NULL;
    return SUCCESS;
}