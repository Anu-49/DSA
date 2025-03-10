/*
Author: Anusha C
The program implements to insert a new data to a sorted linked list.
Also can create a loop or find the loop if already present in the linked list.(Kinda finding if an circular linked list exists or not if last node is pointing to the first node)
OPERATIONS/Functions performed:
Insert_sorted - insert data to a sorted linked list
Find_loop - checks if a loop is present in the linked list or not
Create_loop - a function to create loop by assigning any of the node address to the last node of the list instead of NULL
*/
#include "sll.h"

int main()
{
	int option, data, ret;


	Slist *head = NULL; //initialize the header to NULL

	printf("1. Insert sorted\n2. Find loop\n3. Create loop\n4. Print list\n5. Exit\nEnter Your choice : ");
	while (1)
	{

		/*ask user options*/
		scanf("%d", &option);

		switch (option)
		{
			case 1:
				printf("Enter the data to be inserted : ");
				scanf("%d", &data);
				if (insert_sorted(&head, data) == -1)
				{
					printf("INFO : Insert sorted failure\n");
				}
				else {
				    printf("INFO : Insert sorted SUCCESS\n");
				}
				break;
			case 2:
				/* Function to find the loop */
				if ((ret = find_loop(head)) == LOOP_NOT_FOUND)
				{
					printf("INFO : Loop is not found\n");
				}
				else if (ret == LIST_EMPTY)
				{
					printf("INFO : List is empty\n");
				}
				else
					printf("INFO : Loop found\n");
				break;
			case 3:
				printf("Enter a data to create the loop : ");
				scanf("%d", &data);

				/*insert_at_last function call*/
				if ((ret = create_loop(&head, data)) == LIST_EMPTY) //pass by reference
				{
					printf("INFO : List is empty\n");
				}
				else if (ret == DATA_NOT_FOUND)
				{
					printf("INFO : %d not found at the list\n", data);
				}
				else
				{
					printf("INFO : Loop created successfully\n");
				}
				break;

			case 4:
				/* print list function call*/
				print_list(head);
				break;
			case 5: return SUCCESS;
			default: printf("Enter proper choice !!\n");
					 break;
		}

	}

	return SUCCESS;
}