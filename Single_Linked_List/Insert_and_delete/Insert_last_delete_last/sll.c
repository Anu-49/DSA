#include "sll.h"
int main()
{
	int option, data, key;
	Slist *head = NULL; //initialize the header to NULL
	printf("1. Insert last\n2. Delete Last\n3. Delete list\n4. Find node\n5. Print list\n6. Exit\nEnter your choice : ");
    while (1)
	{
		/*ask user options*/
		scanf("%d", &option);
		
		switch (option)
		{
			case 1:
				printf("Enter the number that you want to insert at last: ");
				scanf("%d", &data);
			
                
				/*insert_at_last function call*/
				if (insert_at_last(&head, data) == FAILURE) //pass by reference
				{
					printf("INFO : Insertion Failure\n");
				}
				break;
			case 2:
				/* Delete a last link*/
				if (sl_delete_last(&head) == 1)
				{
					printf("INFO : Delete last Failure\nList is empty\n");
				}
				else
				{
				    printf("INFO : Delete last successfull\n");
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
				printf("Enter the key to find : ");
				scanf("%d", &key);
				int count;
				if ((count = find_node(head, key)) == FAILURE)
				{
					printf("INFO : Failure\nList is empty or Key not found\n");
				}
				else
				{
					printf("%d found in the list at the position %d\n", key, count);
				}
				break;
			case 5:
				/* print list function call*/
				print_list(head);
					break;
			case 6:
				return SUCCESS;
			default: printf("Enter proper choice !!\n");
			
					 break;
		}
	}
}

