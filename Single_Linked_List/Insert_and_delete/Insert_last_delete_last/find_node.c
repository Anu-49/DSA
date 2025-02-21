#include "sll.h"

int find_node(Slist *head, data_t data)
{
	if(head==NULL){
	    return FAILURE;
	}
	int count = 1;
	Slist *temp = head;
	while (temp != NULL){
	    if (temp->data == data){
	        return count;
	    }
	    temp = temp->link;
	    count++;
	}
	return FAILURE;
}
