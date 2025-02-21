#include "sll.h"

int sl_delete_last(Slist **head)
{
    if(*head == NULL){
        return LIST_EMPTY;
    }
    Slist *temp = *head;
    Slist *prev = NULL;
    while(temp->link!=NULL){
        prev = temp;
        temp = temp->link;
    }
    if(prev!=NULL){
        prev->link = NULL;
    }
    else{
        *head = NULL;
    }
    free(temp);
    return SUCCESS;
}