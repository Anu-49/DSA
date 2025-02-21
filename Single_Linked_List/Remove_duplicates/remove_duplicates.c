#include "sll.h"

//remove duplicate data's from list
int remove_duplicates( Slist **head )
{
    if (*head == NULL) {
        return FAILURE;
    }

    Slist *temp = *head;
    while (temp != NULL) {
        Slist *temp2 = temp;
        while (temp2->link != NULL) {
            if (temp->data == temp2->link->data) {
                Slist *temp3 = temp2->link;
                temp2->link = temp2->link->link;
                free(temp3);
            }
            else{
                temp2 = temp2->link;
            }
        }
        temp = temp->link;
    }

    return SUCCESS;
}