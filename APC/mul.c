#include <stdio.h>
#include <stdlib.h> // For malloc, calloc, free
#include "main.h"

void multi_num(List **head_a, List **tail_a, List2 **head_b, List2 **tail_b, RList **head_r, RList **tail_r)
{
    // Handle multiplication by zero edge case early
    if (((*head_a)->num == 0 && (*head_a)->next == NULL) || ((*head_b)->num == 0 && (*head_b)->next == NULL)) {
        RList *new_node = malloc(sizeof(RList));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed for zero result in multi_num.\n");
            exit(1);
        }
        new_node->num = 0;
        new_node->prev = NULL;
        new_node->next = NULL;
        *head_r = new_node;
        *tail_r = new_node;
        print_list8(*head_r);
        return;
    }

    // Calculate lengths of the input numbers
    int len1 = 0;
    List *temp1_len = *head_a;
    while (temp1_len != NULL) {
        len1++;
        temp1_len = temp1_len->next;
    }

    int len2 = 0;
    List2 *temp2_len = *head_b;
    while (temp2_len != NULL) {
        len2++;
        temp2_len = temp2_len->next;
    }

    // Create a result array to store intermediate products.
    // The maximum length of product is sum of lengths of operands.
    // Each element in result_array will hold a 4-digit segment.
    int result_size = len1 + len2;
    // Use calloc to initialize all elements to zero
    int *result_array = (int *)calloc(result_size, sizeof(int));
    if (result_array == NULL) {
        fprintf(stderr, "Memory allocation failed for result_array in multi_num.\n");
        exit(1);
    }

    // Pointers to traverse the numbers from their tails (least significant)
    List *current_a = *tail_a;
    int i = 0; // Index for result_array for current_a segment

    while (current_a != NULL) {
        List2 *current_b = *tail_b;
        int j = 0; // Index for result_array for current_b segment

        while (current_b != NULL) {
            // Multiply corresponding segments and add to the appropriate position
            // (i+j) represents the position in the result_array from the right (least significant)
            result_array[i + j] += current_a->num * current_b->num;
            current_b = current_b->prev;
            j++;
        }
        current_a = current_a->prev;
        i++;
    }

    // Process carries through the result_array from right to left
    int carry = 0;
    for (int k = 0; k < result_size; k++) {
        result_array[k] += carry;
        carry = result_array[k] / 10000;  // Calculate carry to the next segment
        result_array[k] %= 10000;         // Get the value for the current segment
    }

    // Ensure result list is empty before building
    *head_r = NULL;
    *tail_r = NULL;

    // Build the result linked list from the result_array
    // Iterate from the most significant end of the array
    int first_digit_found = 0; // Flag to handle leading zeros of the entire number

    // Skip leading zeros in result_array from the most significant end
    int start_idx = result_size - 1;
    while (start_idx >= 0 && result_array[start_idx] == 0 && start_idx > 0) {
        start_idx--;
    }

    for (int k = start_idx; k >= 0; k--) {
        RList *new_node = malloc(sizeof(RList));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed in multi_num while building result list.\n");
            free(result_array); // Clean up allocated array
            exit(1);
        }

        new_node->num = result_array[k];
        new_node->prev = NULL; // New nodes are added to the head
        new_node->next = *head_r;

        if (*head_r != NULL) {
            (*head_r)->prev = new_node;
        } else {
            *tail_r = new_node; // If first node, it's also the tail
        }
        *head_r = new_node;
    }

    free(result_array); // Free the temporary array

    // Print the final result using the optimized print function
    print_list8(*head_r);
}