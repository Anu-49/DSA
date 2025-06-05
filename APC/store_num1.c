#include <stdio.h>
#include <stdlib.h> // For atoi, malloc
#include <string.h> // For strlen
#include "main.h"

void store_num1(List **head, List **tail, char str1[])
{
    int len1 = strlen(str1);
    if (len1 == 0) { // Handle empty string case (e.g., if only '-' was passed)
        *head = NULL;
        *tail = NULL;
        return;
    }

    int j = len1 - 1; // Start from the last character
    char str_segment[5]; // Buffer to hold 4 digits + null terminator

    *head = NULL; // Initialize list as empty
    *tail = NULL;

    while (j >= 0) {
        int k;
        // Extract up to 4 digits from right to left
        for (k = 0; k < 4 && j >= 0; k++, j--) {
            str_segment[3 - k] = str1[j]; // Store in reverse order within segment buffer
        }

        // Pad with leading zeros if the segment has fewer than 4 digits
        while (k < 4) {
            str_segment[3 - k] = '0';
            k++;
        }
        str_segment[4] = '\0'; // Null-terminate the segment string

        int num_segment = atoi(str_segment); // Convert segment string to integer

        // Allocate memory for a new node
        List *new_node = malloc(sizeof(List));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed in store_num1.\n");
            // Free any partially built list before exiting
            free_list(head);
            exit(1);
        }

        new_node->num = num_segment;
        new_node->prev = NULL; // New node will become the new head (most significant)

        // Add the new node to the front of the list
        if (*head == NULL) {
            *head = new_node;
            *tail = new_node;
            new_node->next = NULL;
        } else {
            new_node->next = *head;
            (*head)->prev = new_node;
            *head = new_node;
        }
    }
}