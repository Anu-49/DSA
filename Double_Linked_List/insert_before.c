#include "dll.h"

int dl_insert_before(Dlist **head, Dlist **tail, int gdata, int ndata)
{
    if(*head == NULL){
        return LIST_EMPTY;
    }
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL){
        return FAILURE;
    }
    new->data = ndata;
    new->next = NULL;
    new->prev = NULL;
    Dlist *temp = *head;
    if((*head)->data == gdata){
        new->next = *head;
        (*head)->prev = new;
        *head = new;
        return SUCCESS;
    }
    while(temp != NULL){
        if(temp->data != gdata){
            temp = temp->next;
        }
        else{
            new->next = temp;
            new->prev = temp->prev;
            if(temp->prev != NULL){
                temp->prev->next = new;
            }
            temp->prev = new;
            return SUCCESS;
        }
    }
    free(new);
    return DATA_NOT_FOUND;
}