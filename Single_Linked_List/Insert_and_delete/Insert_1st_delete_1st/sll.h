#ifndef SLL_H
#define SLL_H
#include <stdio.h>
#include <stdlib.h>

// defining MACROS
#define SUCCESS 0
#define FAILURE -1
#define LIST_EMPTY 1
typedef int data_t;

// declaring a structure for linked list
typedef struct node
{
	data_t data;
	struct node *link;
}Slist;

// function declaration to insert the data/value at first node
int insert_at_first(Slist **head, data_t);

// function declaration to delete the list
int sl_delete_list(Slist **);

// function declaration to delete the data at first node
int sl_delete_first(Slist **);

// function declaration to print the list
void print_list(Slist *head);
#endif