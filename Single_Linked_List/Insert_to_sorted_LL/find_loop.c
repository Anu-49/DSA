#include "sll.h"

/* Function for finding the loop in the link */
int find_loop(Slist *head)
{
    if(head == NULL){
        return LIST_EMPTY;
    }
    Slist *slow = head;
    Slist *fast = head;
    while(fast != NULL && fast->link != NULL){
        slow = slow->link;
        fast = fast->link->link;
        if(slow == fast){
            return SUCCESS;
        }
    }
    return LOOP_NOT_FOUND;
}