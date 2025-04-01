#include "inverted_Search.h"

int save_database( Wlist *head[])
{
    char file_name[FNAME_SIZE];
    printf("Enter the file name to be saved in the database\n");
    scanf("%s" , file_name);

    //open file
    FILE *fptr = fopen(file_name , "w");

    if(fptr == NULL){
        printf("Error in opening file\n");
        return 0;
    }

    for(int i = 0; i < 27; i++)
    {
        if(head[i] != NULL)
        {
            write_databasefile(head[i] , fptr, i);
        }
    }
    printf("Database saved successfully: %s\n", file_name);
    fclose(fptr);
}

void write_databasefile(Wlist *head, FILE *databasefile, int index)
{
    //5.......TODO.......
    // #[index] : [word] : [file_count] : [file_name] : [word_count]
    Wlist *temp = head;
    while(temp != NULL){
        fprintf(databasefile, "#%d; %s; %d; ", index, temp->word, temp->file_count);
        Ltable * Ltemp = temp->Tlink;
        while(Ltemp != NULL){
            fprintf(databasefile, "%s; %d; ", Ltemp->file_name, Ltemp->word_count);
            Ltemp = Ltemp->table_link;
        }
        fprintf(databasefile, "#\n");
        temp = temp->link;
    } 
}