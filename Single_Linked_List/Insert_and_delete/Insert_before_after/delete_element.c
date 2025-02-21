#include "sll.h"

int sl_delete_element(Slist **head, data_t data)
{
    if (*head == NULL) {
        return LIST_EMPTY;
    }

    if((*head)->data == data){
        Slist *temp = *head;
        *head = (*head)->link;
        free(temp);
        return SUCCESS;
    }

    Slist *temp2 = NULL;
    Slist *current = *head;
    while (current != NULL) {
        if(current->data == data) {
            temp2->link = current->link;
            free(current);
            return SUCCESS;
        }
        temp2 = current;
        current = current->link;
    }
    return DATA_NOT_FOUND;
}