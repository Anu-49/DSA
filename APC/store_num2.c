#include <stdio.h>
#include <stdlib.h> // For atoi, malloc
#include <string.h> // For strlen
#include "main.h"

void store_num2(List2 **head2, List2 **tail2, char str2[])
{
    int len2 = strlen(str2);
    if (len2 == 0) { // Handle empty string case
        *head2 = NULL;
        *tail2 = NULL;
        return;
    }

    int j = len2 - 1; // Start from the last character
    char str_segment[5]; // Buffer to hold 4 digits + null terminator

    *head2 = NULL; // Initialize list as empty
    *tail2 = NULL;

    while (j >= 0) {
        int k;
        // Extract up to 4 digits from right to left
        for (k = 0; k < 4 && j >= 0; k++, j--) {
            str_segment[3 - k] = str2[j]; // Store in reverse order within segment buffer
        }

        // Pad with leading zeros if the segment has fewer than 4 digits
        while (k < 4) {
            str_segment[3 - k] = '0';
            k++;
        }
        str_segment[4] = '\0'; // Null-terminate the segment string

        int num_segment = atoi(str_segment); // Convert segment string to integer

        // Allocate memory for a new node
        List2 *new_node = malloc(sizeof(List2)); // Using sizeof(List2) for consistency
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed in store_num2.\n");
            // Free any partially built list before exiting
            free_list2(head2);
            exit(1);
        }

        new_node->num = num_segment;
        new_node->prev = NULL; // New node will become the new head

        // Add the new node to the front of the list
        if (*head2 == NULL) {
            *head2 = new_node;
            *tail2 = new_node;
            new_node->next = NULL;
        } else {
            new_node->next = *head2;
            (*head2)->prev = new_node;
            *head2 = new_node;
        }
    }
}