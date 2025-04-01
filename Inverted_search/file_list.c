#include "inverted_Search.h"

// validate file name list (present or not, if present is it empty or has content, also checks for duplicate filename.)
void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    int i = 1 , empty, ret_val;
    while(argv[i] != NULL)
    {
        empty = isFileEmpty(argv[i]); // checks if the file available or not and for the availabilty of file content
        if(empty == FILE_NOTAVAILABLE) //if file not found
        {
            printf("File : %s is not available.\n" , argv[i]);
            printf("Hence we are not adding that file to the linked list\n");
            i++;
            continue;
        }
        else if(empty == FILE_EMPTY) // if file found but it is empty so not including to our list
        {
            printf("File : %s is not having any content in it.\n" , argv[i]);
            printf("Hence we are not adding that file\n");
            i++;
            continue;
        }

        // if file is available and not empty:
        else
        {
            ret_val = to_create_list_of_files(f_head , argv[i]);

            if(ret_val == SUCCESS) // checks if file found and has content add it to our linked list
            {
                printf("Successfull : Inserting the file name %s into the file linked list\n", argv[i]);
            }
            else if (ret_val == REPEATATION) // checks if duplicate file found
            {
                printf("This file name : %s is repeated. Do not add more than once\n" , argv[i]);
            }
            else // if failed to add to list due to any other issue(for example malloc failure in the func: to_create_list_of_files)
            {
                printf("Adding file %s failed\n", argv[i]);
            }
            // continue by argv[i] incremented for validation of next file
            i++;
            continue;
        }
    }
}

//fun() is used to check file availability and check for file content 
int isFileEmpty(char *filename)
{
    //check for file availability 
    FILE *fptr = fopen(filename , "r"); //open file in read mode
    if(fptr == NULL) // check if file is not available and returns FILE_NOTAVAILABLE
    {
        if(errno == ENOENT)
        {
            return FILE_NOTAVAILABLE;
        }
    }
    // check for content if file is available
    fseek(fptr, 0L , SEEK_END); //fseek to the end of file and check if file empty or not 
    if(ftell(fptr) == 0) // check if file is empty 
    {
        return FILE_EMPTY;
    }
    return SUCCESS;
}

int to_create_list_of_files(Flist **f_head, char *name) //insert last operation
{
    //insert_last() of SLL
    Flist *temp = *f_head; //assigns f_head to temp pointer.

    // check for duplicate
    while(temp != NULL){
        if(strcmp(temp->file_name, name) == 0){
            return REPEATATION;
        }
        // traversing
        temp = temp->link;
    }

    // create new node
    Flist *new = malloc(sizeof(Flist));
    // check if node created or not
    if(new == NULL){ 
        return FAILURE;
    }
    // copies name to filename
    strcpy(new->file_name, name);
    new->link = NULL;

    // checks if list is empty and adds new filename.
    if(*f_head == NULL){
        *f_head = new;
        return SUCCESS;
    }
    // inserting at last
    temp = *f_head;
    while(temp->link != NULL){
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}
