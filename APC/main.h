#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h> // For malloc, free, exit

// Define constants for success/failure (though not strictly used in current main)
#define SUCCESS 0
#define FAILURE -1

// A single struct definition for number segments.
// Each node stores up to 4 digits (0-9999).
typedef struct node {
    int num;
    struct node *prev;
    struct node *next;
} NumberList;

// Use this common struct for all list types for consistency
typedef NumberList List;
typedef NumberList List2;
typedef NumberList RList;

// Global flags to track negative numbers.
// Declared here, defined in main.c, and used in other .c files.
extern int neg1;
extern int neg2;
extern int both_neg;

// Function prototypes for storing numbers into linked lists
void store_num1(List **head, List **tail, char str1[]);
void store_num2(List2 **head2, List2 **tail2, char str2[]);

// Function prototypes for printing linked lists (for debugging or results)
void print_list(List *head);     // Generic print for List type
void print_list2(List2 *head2);   // Generic print for List2 type
void print_list3(RList *head);   // Specific print for result list, might need refinement
void print_list4(RList *head);   // Another generic print for RList type
void print_list8(RList *head);   // Optimized print for final results (handles leading zeros)

// Function prototypes for arithmetic operations
void add_num(List **head_a, List **tail_a, List2 **head_b, List2 **tail_b, RList **head_r, RList **tail_r);
void sub_num(List **head_a, List **tail_a, List2 **head_b, List2 **tail_b, RList **head_r, RList **tail_r);
void multi_num(List **head_a, List **tail_a, List2 **head_b, List2 **tail_b, RList **head_r, RList **tail_r);
void div_num(List **head_a, List **tail_a, List2 **head_b, List2 **tail_b, RList **head_r, RList **tail_r);

// Helper functions for memory management
void free_list(List **head);
void free_list2(List2 **head2);
void free_rlist(RList **head3);

#endif // MAIN_H