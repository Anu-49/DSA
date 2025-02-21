#include "sll.h"    

//sortList() will sort nodes of the list in ascending order  
int sort(Slist **head) 
{  
    if(*head == NULL){
        return LIST_EMPTY;
    }
    Slist *temp1 = *head;
    Slist *temp2 = NULL;
    int temp3;
    while(temp1 != NULL){
        temp2 = temp1->link;
        while(temp2 != NULL){
            if(temp1->data > temp2->data){
                temp3 = temp1->data;
                temp1->data = temp2->data;
                temp2->data = temp3;
            }
        temp2 = temp2->link;
        }
        temp1 = temp1->link;
    }
    return SUCCESS;
}  
