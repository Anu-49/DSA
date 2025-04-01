/* 
===================================================================================================================
Documentation:
Name: Anusha C
Date: 01-02-2025

Inverted Search DSA Project:
This project implements an inverted search mechanism to efficiently search for words within a set of files. The main components of the project include creating a database from a list of files, inserting words into a word list, updating the word count and file links, saving the database to a file, and searching for words in the database.

Project Structure:
    main.c: Program starts here based on user's input.
    file_list.c: file validation is done in this function.
    create_database.c: function creates and manage the database.
    insert_last.c: function inserts words at the end of word list.
    display_database.c: display the file names, words and word count along with the index.
    update_database.c: function updates the words and it's counts in the database.
    search.c: this function is to search for a word in database.
    save_database.c: save the data inside a new file.

===================================================================================================================
Input:  
./a.out file1.txt file2.txt

Output: 
File : file1.txt is not having any content in it.
Hence we are not adding that file
Successfull : Inserting the file name file2.txt into the file linked list
Select your choice among following options:
1. Create DATABASE
2. Display Database
3. Update DATABASE
4. Search
5. Save Database
6. Exit
Enter your choice:
1
Creation of database successfull for file: file2.txt
Do you want to continue ?? (Enter y/Y for yes and n/N for no) 
y
Select your choice among following options:
1. Create DATABASE
2. Display Database
3. Update DATABASE
4. Search
5. Save Database
6. Exit
Enter your choice:
2
[index]         [word]          file_count              File_name               word_count
[0]             [Are]           1 file/s                File: file2.txt         1
[3]             [doing]         1 file/s                File: file2.txt         2
[5]             [fine?]         1 file/s                File: file2.txt         1
[7]             [Hello]         1 file/s                File: file2.txt         1
[7]             [Hi!!]          1 file/s                File: file2.txt         1
[8]             [I'm]           1 file/s                File: file2.txt         1
[24]            [you]           1 file/s                File: file2.txt         1

Do you want to continue ?? (Enter y/Y for yes and n/N for no) 
y
Select your choice among following options:
1. Create DATABASE
2. Display Database
3. Update DATABASE
4. Search
5. Save Database
6. Exit
Enter your choice:
3
Enter the file name to update the database
file2.txt
This file name : file2.txt is repeated. Do not add more than once
Do you want to continue ?? (Enter y/Y for yes and n/N for no) 
y
Select your choice among following options:
1. Create DATABASE
2. Display Database
3. Update DATABASE
4. Search
5. Save Database
6. Exit
Enter your choice:
3
Enter the file name to update the database
file3.txt
Successfull : Inserting the file name file3.txt into the file linked list
Creation of database successfull for file: file3.txt
Do you want to continue ?? (Enter y/Y for yes and n/N for no) 
y
Select your choice among following options:
1. Create DATABASE
2. Display Database
3. Update DATABASE
4. Search
5. Save Database
6. Exit
Enter your choice:
2
[index]         [word]          file_count              File_name               word_count
[0]             [Are]           1 file/s                File: file2.txt         1
[0]             [An]            1 file/s                File: file3.txt         1
[0]             [an]            1 file/s                File: file3.txt         1
[3]             [doing]         1 file/s                File: file2.txt         2
[5]             [fine?]         1 file/s                File: file2.txt         1
[7]             [Hello]         1 file/s                File: file2.txt         1
[7]             [Hi!!]          1 file/s                File: file2.txt         1
[8]             [I'm]           1 file/s                File: file2.txt         1
[8]             [inverted]              1 file/s                File: file3.txt         1
[8]             [index]         1 file/s                File: file3.txt         2
[8]             [is]            1 file/s                File: file3.txt         1
[24]            [you]           1 file/s                File: file2.txt         1

Do you want to continue ?? (Enter y/Y for yes and n/N for no) 
y
Select your choice among following options:
1. Create DATABASE
2. Display Database
3. Update DATABASE
4. Search
5. Save Database
6. Exit
Enter your choice:
4
Enter the search word
you
Word you is present 1 files
In file : file2.txt  1 times
Do you want to continue ?? (Enter y/Y for yes and n/N for no) 
y
Select your choice among following options:
1. Create DATABASE
2. Display Database
3. Update DATABASE
4. Search
5. Save Database
6. Exit
Enter your choice:
5
Enter the file name to be saved in the database
saved_01.txt
Database saved successfully: saved_01.txt
Do you want to continue ?? (Enter y/Y for yes and n/N for no) 
y
Select your choice among following options:
1. Create DATABASE
2. Display Database
3. Update DATABASE
4. Search
5. Save Database
6. Exit
Enter your choice:
6

anushac@DESKTOP-6PEL4LD:~/C_program/DSA/projects/inverted_search$ cat saved_01.txt
#0; Are; 1; file2.txt; 1; #
#0; An; 1; file3.txt; 1; #
#0; an; 1; file3.txt; 1; #
#3; doing; 1; file2.txt; 2; #
#5; fine?; 1; file2.txt; 1; #
#7; Hello; 1; file2.txt; 1; #
#7; Hi!!; 1; file2.txt; 1; #
#8; I'm; 1; file2.txt; 1; #
#8; inverted; 1; file3.txt; 1; #
#8; index; 1; file3.txt; 2; #
#8; is; 1; file3.txt; 1; #
#24; you; 1; file2.txt; 1; #
===================================================================================================================
*/

#include "inverted_Search.h"

int main(int argc , char *argv[])
{
    system("clear");

    //validate CLA 
    if( argc <= 1 )
    {
        printf("Enter the valid number of arguments\n");
        printf("For example: ./main.exe file1.txt file2.txt .......\n");
        return 0;
    }

    //create file linked list 
    //declare head pointer 
    Flist *f_head = NULL;

    //validation of files 
    file_validation_n_file_list(&f_head ,argv);

    if(f_head == NULL)
    {
        printf("No files added to file linked list\n");
        printf("Hence the process got terminated\n");
        return 2;
    }

// User's choice
    int choice;
    char y_or_n;
    Wlist *head[27] = {NULL};
    do{
        printf("Select your choice among following options:\n1. Create DATABASE\n2. Display Database\n3. Update DATABASE\n4. Search\n5. Save Database\n6. Exit\nEnter your choice:\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: 
                // create a database based on files present and it's content.
                create_database(f_head , head);
                break;
            case 2:
                // display the content of database
                display_database(head);
                break;
            case 3:
                // update the database
                update_database(head , &f_head);
                break;
            case 4:
                // search for a word inside the database
                char word[WORD_SIZE];
                printf("Enter the search word\n");
                scanf("%s" , word);
                int index = tolower(word[0]) % 97;
                search(head[index] , word);
                break;
            case 5:
                // save the database
                save_database(head);
                break;
            case 6:
                return 0;
                break;
            default:
                break;
        }
        printf("Do you want to continue ?? (Enter y/Y for yes and n/N for no) \n");
        getchar();
        scanf("%c", &y_or_n);
    }while(y_or_n == 'y' || y_or_n == 'Y');
}
