#include "sll.h"

int sl_insert_nth(Slist **head, data_t data, data_t n)
{
    if (*head == NULL && n!=1) {
        return LIST_EMPTY;
    }
    if(n == 1){
	    Slist *new = malloc(sizeof(Slist));
	    if (new == NULL){
		    return FAILURE;
	    }
	    new->data = data;
	    new->link = NULL;
	    if (*head == NULL){
		    *head = new;
		    return SUCCESS;
	    }
	    else{
		    Slist *temp = *head;
		    *head = new;
		    new->link = temp;
	    }
    }
    Slist *temp = *head;
    int count = 1;
    while(temp != NULL && count < n-1){
        temp = temp->link;
        count++;
    }
    
    if(temp == NULL){
        return POSITION_NOT_FOUND;
    }
    Slist *new = (Slist*)malloc(sizeof(Slist));
    if(new == NULL){
        return FAILURE;
    }
    new->data = data;
    new->link = temp->link;
    temp->link = new;

    return SUCCESS;
}