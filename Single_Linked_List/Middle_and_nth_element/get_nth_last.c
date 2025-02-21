#include "sll.h"
/* Function to get the nth node from the last of a linked list*/
int find_nth_last(Slist *head, int pos, int *data) 
{ 
    if(head == NULL){
        return LIST_EMPTY;
    }
    Slist *temp1 = head;
    Slist *temp2 = head;
    
    int count = 0;
    if(pos == 0){
        return FAILURE;
    }
    while(temp2 != NULL){
        while(count < pos){
            if(temp2 == NULL){
                return FAILURE;
            }
            temp2 = temp2->link;
            count++;
        }
        while(temp2 != NULL){
            temp1 = temp1->link;
            temp2 = temp2->link;
        }
    }
    *data = temp1->data;
    return SUCCESS;
} 