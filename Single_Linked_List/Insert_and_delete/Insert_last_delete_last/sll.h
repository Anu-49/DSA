#ifndef SLL_H
#define SLL_H
#include <stdio.h>
#include <stdlib.h>
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

// function declaration to find node with particular element 
int find_node(Slist *head, data_t key);

// function declaration to delete the node at the end of the list
int insert_at_last(Slist **head, data_t );

// function declaration to delete all the nodes of the list
int sl_delete_list(Slist **);

// function declaration to delete the node at the end of the list
int sl_delete_last(Slist **);

// function declaration to print all the nodes
void print_list(Slist *head);
#endif