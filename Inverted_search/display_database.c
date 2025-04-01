#include"inverted_Search.h"

void display_database( Wlist *head[])
{
    printf("[index]\t\t[word]\t\tfile_count\t\tFile_name\t\tword_count\n");
    for(int i = 0; i < 27; i++)
    {
        if(head[i] != NULL)
        {
            print_word_count(head[i]);
        }
    }
    printf("\n");
}
int print_word_count(Wlist *head)
{
    //traverse through Wlist
    while(head != NULL)
    {
        printf("[%d]\t\t[%s]\t\t%d file/s\t\t" , tolower(head->word[0]) % 97 , head->word , head->file_count);

        Ltable *Thead = head->Tlink;

        //traverse 
        while(Thead)
        {
            printf("File: %s\t\t%d", Thead->file_name , Thead->word_count);
            Thead = Thead->table_link;
        }
        printf("\n");
        head = head->link;
    }
}