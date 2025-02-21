#include "sll.h"

void print_list(Slist *head)
{
	// checks if the list is empty 
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
		return;
	}
	// traverse and print the list elements
    while (head)		
	{
	    printf("%d -> ", head -> data);
	    head = head -> link;
    }

    printf("NULL\n");
}