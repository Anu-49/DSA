#include "sll.h"

/* Function to create the loop */
int create_loop(Slist **head, data_t data)
{
    if(*head == NULL){
        return LIST_EMPTY;
    }
    Slist *temp = *head;
    Slist *address = NULL;
    
    while(temp->link != NULL){
        if(temp->data == data){
            address = temp;
        }
        temp = temp->link;
    }
    
    if(temp->data == data){
        address = temp ;
    }
    if(address != NULL){
        temp->link = address;
        return SUCCESS;
    }
    return DATA_NOT_FOUND;

}