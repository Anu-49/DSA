#include "sll.h"
// function definition to insert the element at the first node
int insert_at_first(Slist **head, data_t data)
{
    // create  new node
    Slist *new = malloc(sizeof(Slist));
    if(new == NULL){
        return FAILURE;
    }
    // point the head to the new node (insert at first)
    new->data = data;
    new->link = *head;
    *head = new;
    return SUCCESS;
}