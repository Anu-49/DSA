#include "inverted_Search.h"

char *fname;

int create_database(Flist *f_head, Wlist *head[])
{
    //traverse through the FLL
    while(f_head)
    {
        read_datafile(f_head , head , f_head->file_name);
        f_head = f_head->link;
    }
}

// fun() is to read the content of each file 
Wlist * read_datafile(Flist *file, Wlist *head[], char *filename)
{
    int flag = 1;
    // open file in read mode
    fname = filename;
    FILE *fptr = fopen(filename , "r");
    if(fptr == NULL)
    {
	    printf("Error in opening the file: %s\n", filename);
    }
    //declare an array to store the scanned word 
    char word[WORD_SIZE];
    // scan the words from file till end of file
    while(fscanf(fptr , "%s" , word) != EOF)
    {
        //find index
        int index =  tolower(word[0]) % 97;
        //if index other than alphabets index is 26
        if(!(index >= 0 && index <= 25))
        {
            index = 26;
        }

    //If list is empty not necessary to check if words are repeated.
    // If list is not empty then we should check for words repeatency 
        if(head[index] != NULL)
        {
            Wlist *temp = head[index];
            // compare each node word with new word 
            while(temp)
            {
                // comparing words
                if(!(strcmp(temp->word , word)))
                {
                    // when words are repeated update word count
                    // should check if word repeated in same file or new file.
                    update_word_count(&temp , filename);
                    flag = 0;
                    break;
                }
                temp = temp->link;
            }
        }

        // insert last will be called only when words are not repeated 
        if(flag == 1)
        {
            insert_at_last(&head[index] , word);
        }
    }
    printf("Creation of database successfull for file: %s\n", filename);
}

// function updates word count
int update_word_count(Wlist ** head, char * file_name)
{
    // check filenames are same or not 
    // traverse to check if filename already exists or not in Ltable
    Ltable *temp = (*head)->Tlink;
    Ltable *prev = NULL;
    while(temp){
        // compare file name if same : increment word_count
        if(strcmp(temp->file_name, file_name) == 0)
        {
            temp->word_count++;
            return SUCCESS;
        }
        prev = temp;
        temp = temp->table_link;
    }

    // Increment file_count in the main word node
    (*head)->file_count++;

    // if different : increment file_count , create Ltable node (insert at the end )
    Ltable *new_Ltable_node = malloc(sizeof(Ltable));
    if (!new_Ltable_node)
    {
        printf("Memory allocation for new_Ltable_node failed!\n");
        return FAILURE;  // Return error if malloc fails
    }

    // Initialize the new node updating Ltable value
    strcpy(new_Ltable_node->file_name, file_name);  // Copy the filename
    new_Ltable_node->word_count = 1;                // Set initial count
    new_Ltable_node->table_link = NULL;

    // update links new and prev link
    prev->table_link = new_Ltable_node;
    
    return SUCCESS;
}