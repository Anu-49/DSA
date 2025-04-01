#include "inverted_Search.h"

int update_database( Wlist *head[], Flist **f_head)
{
    char file_name[FNAME_SIZE];
    printf("Enter the file name to update the database\n");
    scanf("%s" , file_name);
    // validate the file name 
    // add to the file linked list 
    int empty = isFileEmpty(file_name); // checks if the file available or not and for the availabilty of file content
        if(empty == FILE_NOTAVAILABLE) //if file not found
        {
            printf("File : %s is not available.\n" , file_name);
            printf("Hence we are not adding that file to the linked list\n");
            return 0;
        }
        else if(empty == FILE_EMPTY) // if file found but it is empty so not including to our list
        {
            printf("File : %s is not having any content in it.\n" ,file_name);
            printf("Hence we are not adding that file\n");
            return 0;
        }

        // if file is available and not empty:
        else
        {
            int ret_val = to_create_list_of_files(f_head , file_name);
            if(ret_val == SUCCESS) // checks if file found and has content add it to our linked list
            {
                printf("Successfull : Inserting the file name %s into the file linked list\n",file_name);
            }
            else if (ret_val == REPEATATION) // checks if duplicate file found
            {
                printf("This file name : %s is repeated. Do not add more than once\n" ,file_name);
                return 0;
            }
            else // if failed to add to list due to any other issue(for example malloc failure in the func: to_create_list_of_files)
            {
                printf("Adding file %s failed\n", file_name);
                return 0;
            }
        }

    Flist *file_temp = *f_head;
    while(file_temp)
    {
        if(!(strcmp(file_temp->file_name, file_name)))
        {
            create_database(file_temp , head);
            return 0;
        }
        file_temp = file_temp->link;
    } 
    printf("Updated database successfully\n"); 
}
