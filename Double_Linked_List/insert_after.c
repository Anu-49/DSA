#include "dll.h"

int dl_insert_after(Dlist **head, Dlist **tail, int gdata, int ndata)
{
    if(*head==NULL){
        return LIST_EMPTY;
    }
    Dlist *temp = *head;
    while(temp!=NULL){
        if(temp->data != gdata){
            temp = temp->next;
        }
        else{
            Dlist *new= malloc(sizeof(Dlist));
            if(new==NULL){
                return FAILURE;
            }
            new->data = ndata;
            new->next = temp->next;
            new->prev = temp;
            if(*tail!=temp){
                temp->next->prev = new;
            }
            else{
                *tail = new;
            }
            temp->next = new;
            return SUCCESS;
        }
    }
    return DATA_NOT_FOUND;
}