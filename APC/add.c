#include <stdio.h>
#include <stdlib.h> // For malloc
#include "main.h"

void add_num(List **head_a, List **tail_a, List2 **head_b, List2 **tail_b, RList **head_r, RList **tail_r)
{
    // Start from the tails of the input lists (least significant digits)
    List *temp1 = *tail_a;
    List2 *temp2 = *tail_b;
    int carry = 0; // Initialize carry to 0

    // Ensure result list is empty before starting
    *head_r = NULL;
    *tail_r = NULL;

    // Loop until both numbers are processed and there's no remaining carry
    while (temp1 != NULL || temp2 != NULL || carry > 0)
    {
        int sum = 0; // Initialize sum for the current segment

        // Add segment from the first number if available
        if (temp1 != NULL) {
            sum += temp1->num;
            temp1 = temp1->prev; // Move to the previous segment
        }

        // Add segment from the second number if available
        if (temp2 != NULL) {
            sum += temp2->num;
            temp2 = temp2->prev; // Move to the previous segment
        }

        sum += carry; // Add the carry from the previous segment

        // Check for carry to the next segment
        if (sum >= 10000) {
            carry = 1;         // Carry is 1 for the next segment
            sum -= 10000;      // Current segment value
        } else {
            carry = 0;         // No carry
        }

        // Create a new node for the result list
        RList *new_node = malloc(sizeof(RList));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed in add_num.\n");
            exit(1);
        }

        new_node->num = sum;
        new_node->prev = NULL; // New nodes are always added to the head (most significant)

        // Add the new node to the front of the result list (building in reverse order of processing)
        if (*head_r == NULL) {
            *head_r = new_node;
            *tail_r = new_node;
            new_node->next = NULL;
        } else {
            new_node->next = *head_r;
            (*head_r)->prev = new_node;
            *head_r = new_node;
        }
    }

    // Print the final result using the optimized print function
    print_list8(*head_r);
}