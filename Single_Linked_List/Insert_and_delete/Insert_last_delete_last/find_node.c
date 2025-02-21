#include "sll.h"

int find_node(Slist *head, data_t data)
{
	// returns failure if list is empty
	if(head==NULL){
	    return FAILURE;
	}

	// returns count - node at which the data is found
	int count = 1;
	Slist *temp = head;
	// traverse through all the nodes to find the node with user entered data
	while (temp != NULL){
	    if (temp->data == data){
	        return count;
	    }
	    temp = temp->link;
	    count++;
	}
	return FAILURE;
}
