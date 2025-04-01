#include "inverted_Search.h"

extern char* fname;

int insert_at_last(Wlist **head, data_t *data)
{
    //create node
    Wlist *new = malloc(sizeof(Wlist));
    if(new == NULL)
    {
        return FAILURE;
    }
    new->file_count = 1;
    strcpy(new->word , data);
    new->Tlink = NULL;
    new->link = NULL;

    //call fun() to update Ltable node
    update_link_table(&new);

    //check list is empty or not 
    if(*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    //not empty
    Wlist *temp = *head;
    //traverse 
    while(temp->link)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}


int update_link_table(Wlist *head[])
{
    //create a node
    Ltable *new = malloc(sizeof(Ltable));

    if(new == NULL)
    {
        return FAILURE;
    }

    new->word_count = 1;
    strcpy(new->file_name , fname); 
    new->table_link = NULL;

    (*head)->Tlink = new;
    return SUCCESS; 
}