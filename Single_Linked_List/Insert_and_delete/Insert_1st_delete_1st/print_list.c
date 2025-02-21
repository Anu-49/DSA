#include "sll.h"

void print_list(Slist *head)
{
	// check if list is empty or not
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
		return;
	}
	// if list is not empty traverse through the list and print the elements
    while (head)		
	{
	    printf("%d -> ", head -> data);
	    head = head -> link;
    }
// print NULL at the end of the list
    printf("NULL\n");
}