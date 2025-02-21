#include "sll.h"

int sorted_merge( Slist **head1, Slist **head2)
{
    if(*head1 == NULL && *head2 == NULL){
        return LIST_EMPTY;
    }
    sort(head1);
    sort(head2);
    
    if(*head1 == NULL){
        *head1 = *head2;
        return SUCCESS;
    }
    Slist *temp = *head1;
    while(temp->link != NULL){
        temp = temp->link;
    }
    temp->link = *head2;
    sort(head1);
    return SUCCESS;
}