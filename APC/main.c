#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// Global flags for tracking negative numbers
int neg1 = 0; // Set if the first operand is negative
int neg2 = 0; // Set if the second operand is negative
int both_neg = 0; // Set if both operands are negative

// Helper function to free a List
void free_list(List **head) {
    List *current = *head;
    while (current != NULL) {
        List *next = current->next;
        free(current);
        current = next;
    }
    *head = NULL; // Ensure head is NULL after freeing
}

// Helper function to free a List2
void free_list2(List2 **head2) {
    List2 *current = *head2;
    while (current != NULL) {
        List2 *next = current->next;
        free(current);
        current = next;
    }
    *head2 = NULL; // Ensure head2 is NULL after freeing
}

// Helper function to free an RList
void free_rlist(RList **head3) {
    RList *current = *head3;
    while (current != NULL) {
        RList *next = current->next;
        free(current);
        current = next;
    }
    *head3 = NULL; // Ensure head3 is NULL after freeing
}

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 4) {
        printf("Usage: %s <num1> <operator> <num2>\n", argv[0]);
        printf("Example: %s 12345 + 67890\n", argv[0]);
        return 1; // Exit with error code
    }

    char *str1_arg = argv[1];    // First number string from CLI
    char operator = argv[2][0]; // Operator (first char of second arg) from CLI
    char *str2_arg = argv[3];    // Second number string from CLI

    // Reset global flags for each calculation
    neg1 = 0;
    neg2 = 0;
    both_neg = 0;

    // Pointers to the actual number strings (after stripping potential '-' sign)
    char *actual_str1 = str1_arg;
    char *actual_str2 = str2_arg;

    // Check and handle negative signs for the first number
    if (str1_arg[0] == '-') {
        neg1 = 1;
        actual_str1 = str1_arg + 1; // Move past the '-'
    }
    // Check and handle negative signs for the second number
    if (str2_arg[0] == '-') {
        neg2 = 1;
        actual_str2 = str2_arg + 1; // Move past the '-'
    }
    // Set both_neg flag if both are negative
    if (neg1 && neg2) {
        both_neg = 1;
    }

    // Initialize linked list heads and tails
    List *head = NULL;
    List *tail = NULL;
    store_num1(&head, &tail, actual_str1); // Store first number

    List2 *head2 = NULL;
    List2 *tail2 = NULL;
    store_num2(&head2, &tail2, actual_str2); // Store second number

    RList *head3 = NULL; // Head for the result list
    RList *tail3 = NULL; // Tail for the result list

    // Basic validation: ensure numbers were successfully stored
    if (head == NULL || head2 == NULL) {
        printf("Error: Invalid number format for one or both operands.\n");
        free_list(&head);
        free_list2(&head2);
        return 1;
    }

    printf("Result : "); // Prefix for the result output

    switch (operator)
    {
        case '+':
        {
            // Case 1: Both numbers negative (e.g., -5 + -3 = -(5+3))
            if (both_neg) {
                printf("-");
                add_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            }
            // Case 2: First negative, second positive (e.g., -5 + 3 = 3 - 5)
            // Case 3: First positive, second negative (e.g., 5 + -3 = 5 - 3)
            // In both cases, it becomes a subtraction of magnitudes.
            else if (neg1 || neg2) {
                // The `sub_num` function determines the final sign based on magnitudes
                // so we don't print '-' here. `sub_num` will handle it.
                sub_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            }
            // Case 4: Both numbers positive (e.g., 5 + 3)
            else {
                add_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            }
            break;
        }
        case '-':
        {
            // Case 1: First negative, second negative (e.g., -5 - (-3) = -5 + 3 = 3 - 5)
            if (both_neg) {
                // Perform subtraction of magnitudes (B - A), then handle sign
                // Temporarily swap head/tail pointers to perform B - A.
                // This is a "trick" assuming sub_num takes the first pair as 'A' and second as 'B'.
                // A more robust solution for swapping would be to copy lists.
                List *temp_head = head;
                List *temp_tail = tail;
                head = (List*)head2;
                tail = (List*)tail2;
                head2 = (List2*)temp_head;
                tail2 = (List2*)temp_tail;
                sub_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            }
            // Case 2: First negative, second positive (e.g., -5 - 3 = -(5 + 3))
            else if (neg1) {
                printf("-");
                add_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            }
            // Case 3: First positive, second negative (e.g., 5 - (-3) = 5 + 3)
            else if (neg2) {
                add_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            }
            // Case 4: Both positive (e.g., 5 - 3)
            else {
                // The `sub_num` function will handle printing '-' if num2 > num1
                sub_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            }
            break;
        }
        case '*':
        {
            // If either number is zero, the result is zero
            if ((head->num == 0 && head->next == NULL) || (head2->num == 0 && head2->next == NULL)) {
                printf("0\n");
            } else {
                // Determine the sign of the product: if one is negative, result is negative.
                if ((neg1 && !neg2) || (!neg1 && neg2)) {
                    printf("-");
                }
                multi_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            }
            break;
        }
        case '/':
        {
            // Division by zero check
            if (head2->num == 0 && head2->next == NULL) { // Check if divisor is '0'
                printf("Error: Division by zero\n");
                // Free memory and exit before returning
                free_list(&head);
                free_list2(&head2);
                // head3 might not be allocated yet, so no need to free it here
                return 1;
            }

            // Determine the sign of the quotient: if one is negative, result is negative.
            if ((neg1 && !neg2) || (!neg1 && neg2)) {
                printf("-");
            }
            div_num(&head, &tail, &head2, &tail2, &head3, &tail3);
            break;
        }
        default:
        {
            printf("Error: Invalid operator '%c'\n", operator);
        }
    }

    // Free all dynamically allocated memory to prevent leaks
    free_list(&head);
    free_list2(&head2);
    free_rlist(&head3);

    return 0; // Successful execution
}