#include "sll.h"

int insert_at_last(Slist **head, data_t data)
{
    // create a node
    Slist *new = malloc(sizeof(Slist));
    if(new == NULL){
        return FAILURE;
    }
    // assign data to the new node created
    new->data = data;
    new->link = NULL;
    if(*head == NULL){
        *head = new;
        return SUCCESS;
    }
    // traverse to the end of list to add node at the end of list
    Slist *temp = *head;
    while(temp->link!=NULL){
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}