#include "sll.h"

void print_list(Slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
		return;
	}
    while (head)		
	{
	    printf("%d -> ", head -> data);
	    head = head -> link;
    }

    printf("NULL\n");
}