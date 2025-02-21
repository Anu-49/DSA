/*
This program allows the user to manage a linked list with ease. It provides the following functionalities:

1. **Insert**: Takes an integer input from the user and inserts it at the beginning of the linked list, making it the first node.
2. **Delete First Node**: Removes the element at the first node when called, ensuring efficient deletion.
3. **Delete Entire List**: Clears all nodes in the linked list, resulting in an empty list.

These functions facilitate basic linked list operations, ideal for educational purposes or simple data structure manipulations.
*/


#include "sll.h"
int main()
{
	int option, data, key;
	Slist *head = NULL; //initialize the header to NULL
	printf("1. Insert first\n2. Delete first\n3. Delete list\n4. Print list\n5. Exit\nEnter your choice : ");
    while (1)
	{
		/*ask user options*/
		scanf("%d", &option);
		
		switch (option)
		{
			case 1:
				/*To insert the element at first */
				printf("Enter the element you have to insert at the first : ");
				scanf("%d", &data);
				
				if (insert_at_first(&head, data) == -1)
				{
					printf("INFO : Insertion Failure\n");
				}
				break;
            case 2:
				/*To delete first node */
				if (sl_delete_first(&head))
				{
					printf("INFO : Delete first Failure\n List is empty\n");
				}
				else
				{
				    printf("INFO : Delete first successfull\n");
				}
				break;
			case 3:
				/* Delete list */
				if (sl_delete_list(&head) == -1)
				{
					printf("INFO : Delete list Failure\nList is empty\n");
				}
				else
				{
					printf("INFO : Delete list Successfull\n");
				}
				break;
			case 4:
				/* print list function call*/
				print_list(head);
				break;
			case 5:
				return SUCCESS;
			default: 
                printf("Enter proper choice !!\n");
			    break;
		}
	}
}

