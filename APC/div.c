#include <stdio.h>
#include <stdlib.h> // For malloc, free
#include <string.h> // For sprintf, etc.
#include "main.h"

// Helper function to compare two NumberList magnitudes
// Returns:
//   1 if num1_head > num2_head
//   -1 if num1_head < num2_head
//   0 if num1_head == num2_head
int compare_lists_magnitude_div(List *num1_head, List2 *num2_head) {
    int len1 = 0;
    List *temp1 = num1_head;
    while (temp1 != NULL) {
        len1++;
        temp1 = temp1->next;
    }

    int len2 = 0;
    List2 *temp2 = num2_head;
    while (temp2 != NULL) {
        len2++;
        temp2 = temp2->next;
    }

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    // If lengths are equal, compare digit by digit from most significant
    temp1 = num1_head;
    temp2 = num2_head;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->num > temp2->num) return 1;
        if (temp1->num < temp2->num) return -1;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return 0; // Numbers are equal
}


void div_num(List **head_a, List **tail_a, List2 **head_b, List2 **tail_b, RList **head_r, RList **tail_r)
{
    // Calculate lengths of the numbers
    int len1 = 0;
    List *temp1 = *head_a;
    while (temp1 != NULL) {
        len1++;
        temp1 = temp1->next;
    }

    int len2 = 0;
    List2 *temp2 = *head_b;
    while (temp2 != NULL) {
        len2++;
        temp2 = temp2->next;
    }

    // Check if the dividend is smaller than the divisor in magnitude
    // If so, the quotient is 0.
    if (compare_lists_magnitude_div(*head_a, *head_b) == -1) {
        printf("0\n");
        return;
    }

    // Convert divisor linked list to a `long int`. This is a limitation.
    // For truly arbitrary precision, a long division algorithm on linked lists is needed.
    List2 *current_divisor_node = *head_b;
    long long divisor = 0; // Using long long for potentially larger divisors
    while (current_divisor_node != NULL) {
        divisor = divisor * 10000 + current_divisor_node->num; // Build the divisor number
        current_divisor_node = current_divisor_node->next;
    }

    // Initialize result list
    *head_r = NULL;
    *tail_r = NULL;

    // Dummy head for easier result list building (will be removed later)
    RList *dummy_head = (RList *)malloc(sizeof(RList));
    if (dummy_head == NULL) {
        fprintf(stderr, "Memory allocation failed for dummy_head in div_num.\n");
        exit(1);
    }
    dummy_head->num = 0; // Placeholder
    dummy_head->next = NULL;
    dummy_head->prev = NULL;
    *head_r = dummy_head;
    *tail_r = dummy_head;

    List *current_dividend_node = *head_a;
    long long current_remainder = 0; // Accumulates dividend segments

    // Flag to track if significant digits have been added to the result
    int has_significant_digit = 0;

    while (current_dividend_node != NULL) {
        // Append the next 4-digit segment of the dividend to the current remainder
        current_remainder = current_remainder * 10000 + current_dividend_node->num;

        // Calculate the quotient digit for the current remainder
        long long quotient_digit = current_remainder / divisor;
        // Update the remainder
        current_remainder = current_remainder % divisor;

        // Add the quotient digit to the result list only if it's significant
        // or if we have already started adding significant digits.
        if (has_significant_digit || quotient_digit > 0) {
            has_significant_digit = 1; // Mark that we've found a non-zero digit
            RList *new_node = (RList *)malloc(sizeof(RList));
            if (new_node == NULL) {
                fprintf(stderr, "Memory allocation failed for new_node in div_num.\n");
                // Clean up any partially built list
                free_rlist(head_r); // This will free dummy_head too if it's the only one
                exit(1);
            }
            new_node->num = (int)quotient_digit;
            new_node->next = NULL;
            new_node->prev = *tail_r; // Link to previous tail

            (*tail_r)->next = new_node; // Link previous tail to new node
            *tail_r = new_node;         // Update tail to new node
        }
        current_dividend_node = current_dividend_node->next;
    }

    // After processing, remove the dummy head if it's not the only node
    if (*head_r == dummy_head && dummy_head->next != NULL) {
        *head_r = dummy_head->next;
        (*head_r)->prev = NULL;
        free(dummy_head);
    } else if (*head_r == dummy_head && dummy_head->next == NULL) {
        // If dummy_head is the only node, and has_significant_digit is 0, means result is 0
        // (e.g., if dividend is smaller than divisor).
        // In this case, we just need a single '0' node.
        if (!has_significant_digit) {
            dummy_head->num = 0; // Ensure it's 0 if nothing was added
        }
        // If has_significant_digit is true, but somehow only dummy_head remains, means error or 0.
        // The check `if (compare_lists_magnitude_div(...) == -1)` at the start should catch most.
    }


    // If no significant digits were added (e.g., 1 / 5 = 0), ensure result is "0"
    if (!has_significant_digit && *head_r == NULL) {
        RList *zero_node = malloc(sizeof(RList));
        if (zero_node == NULL) {
            fprintf(stderr, "Memory allocation failed for zero_node in div_num.\n");
            exit(1);
        }
        zero_node->num = 0;
        zero_node->prev = NULL;
        zero_node->next = NULL;
        *head_r = zero_node;
        *tail_r = zero_node;
    } else if (!has_significant_digit && *head_r != NULL && (*head_r)->num == 0 && (*head_r)->next == NULL) {
        // Result was zero, but a single zero node already exists (e.g. from dummy_head becoming actual result)
        // No action needed, it's already correct.
    }


    // Print the final result using the optimized print function
    print_list8(*head_r);
}


// This print function is specifically for the final result,
// handling leading zeros within 4-digit segments
void print_list8(RList *head) {
    if (!head) {
        printf("0\n"); // If list is empty, print 0
        return;
    }

    // Skip any true leading zeros (e.g., 0005, print 5)
    while (head != NULL && head->num == 0 && head->next != NULL) {
        head = head->next;
    }

    // Create a string buffer to store the result.
    // Assuming max 1000 segments, each 4 digits + null + potential sign.
    // 1000 * 4 + 1 + 1 = 4002. Using 5000 for safety.
    char buffer[5000];
    char *ptr = buffer; // Pointer to current position in buffer
    int first_segment = 1; // Flag to indicate the first segment being printed

    while (head != NULL) {
        if (first_segment) {
            // For the very first segment, print without leading zeros
            ptr += sprintf(ptr, "%d", head->num);
            first_segment = 0;
        } else {
            // For subsequent segments, print with leading zeros if necessary
            // e.g., if segment is 5, print "0005"
            ptr += sprintf(ptr, "%04d", head->num);
        }
        head = head->next;
    }
    printf("%s\n", buffer);
}