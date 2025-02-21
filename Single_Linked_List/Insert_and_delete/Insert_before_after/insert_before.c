#include "sll.h"

int sl_insert_before(Slist **head, data_t g_data, data_t ndata)
{
    if(*head == NULL){
        return LIST_EMPTY;
    }
    if((*head)->data == g_data){
        Slist *new = malloc(sizeof(Slist));
        if(new == NULL){
            return FAILURE;
        }
        new->data = ndata;
        new->link = *head;
        *head = new;
        return SUCCESS;
    }
    
    Slist *temp = NULL;
    Slist *current = *head;
    while(current != NULL){
        if(current->data == g_data){
            Slist *new = malloc(sizeof(Slist));
            if(new == NULL){
                return FAILURE;
            }
            new->data = ndata;
            new->link = current;
            temp->link = new;
            return SUCCESS;
        }
        temp = current;
        current = current->link;
    }
    return DATA_NOT_FOUND;
}