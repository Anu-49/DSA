#include <stdio.h>
#include <stdlib.h> // For malloc
#include "main.h"

// External global flags (from main.c)
extern int neg1; // Is the first number originally negative?
extern int neg2; // Is the second number originally negative?

// Helper function to compare two NumberList magnitudes
// Returns:
//   1 if num1_head > num2_head
//   -1 if num1_head < num2_head
//   0 if num1_head == num2_head
int compare_lists_magnitude(List *num1_head, List2 *num2_head) {
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


void sub_num(List **head_a, List **tail_a, List2 **head_b, List2 **tail_b, RList **head_r, RList **tail_r)
{
    // Pointers to traverse from the tails (least significant)
    List *t1 = *tail_a;
    List2 *t2 = *tail_b;

    int borrow = 0; // Initialize borrow to 0

    // Determine which number has the larger magnitude
    // This dictates which number is subtracted from which to get a positive difference.
    int comparison_result = compare_lists_magnitude(*head_a, *head_b);
    int result_is_negative = 0; // Flag to determine the final sign of the result

    // Determine the actual numbers to subtract and the final sign
    List *num1_ptr; // Pointer to the number we are subtracting from
    List2 *num2_ptr; // Pointer to the number we are subtracting

    if (comparison_result == 1) { // Magnitude of A > Magnitude of B
        num1_ptr = *tail_a;
        num2_ptr = *tail_b;
        if (neg1 && !neg2) { // (-A) - (+B) = -(A+B) handled by add_num in main
                             // So this path implies +A - +B, or -A - (-B) where |A| > |B| (becomes B-A)
                             // For +A - +B where A > B, result is positive.
                             // For -A - (-B) where |A| > |B|, it's B - A. If B < A, then result is negative.
            result_is_negative = 0; // This will be true if original operation was +A - +B
        } else if (!neg1 && neg2) { // +A - (-B) = A+B handled by add_num in main
            result_is_negative = 0;
        } else { // Case: +A - +B where A > B (result positive), or -A - (-B) where |A| > |B| (result negative)
            result_is_negative = (neg1 && neg2); // If both were neg, -A - (-B) = B - A. If |A|>|B|, B-A is negative
        }

    } else if (comparison_result == -1) { // Magnitude of A < Magnitude of B
        num1_ptr = (List*)*tail_b; // Subtract B - A
        num2_ptr = (List2*)*tail_a;
        result_is_negative = 1; // Always negative if |B| > |A| and we're doing A - B (e.g. 3 - 5)
        if (neg1 && !neg2) { // (-A) - (+B) = -(A+B) handled by add_num in main
            result_is_negative = 1;
        } else if (!neg1 && neg2) { // +A - (-B) = A+B handled by add_num in main
            result_is_negative = 0;
        } else { // Case: +A - +B where B > A (result negative), or -A - (-B) where |B| > |A| (result positive)
            result_is_negative = (!neg1 && !neg2); // If both were pos, A - B. If B > A, result is negative.
        }

    } else { // Magnitudes are equal (comparison_result == 0)
        // If numbers are equal, result is 0
        RList *new_node = malloc(sizeof(RList));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed in sub_num for zero result.\n");
            exit(1);
        }
        new_node->num = 0;
        new_node->prev = NULL;
        new_node->next = NULL;
        *head_r = new_node;
        *tail_r = new_node;
        print_list8(*head_r); // Print "0"
        return; // Done
    }

    // Ensure result list is empty before starting
    *head_r = NULL;
    *tail_r = NULL;

    // Perform subtraction (larger magnitude - smaller magnitude)
    while (num1_ptr != NULL || num2_ptr != NULL || borrow > 0)
    {
        int val1 = num1_ptr ? num1_ptr->num : 0;
        int val2 = num2_ptr ? num2_ptr->num : 0;

        int diff = val1 - val2 - borrow;

        if (diff < 0) {
            diff += 10000; // Add 10000 to borrow from the next segment
            borrow = 1;
        } else {
            borrow = 0;
        }

        RList *new_node = malloc(sizeof(RList));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed in sub_num.\n");
            exit(1);
        }

        new_node->num = diff;
        new_node->prev = NULL;

        // Add to the head of the result list
        if (*head_r == NULL) {
            *head_r = new_node;
            *tail_r = new_node;
            new_node->next = NULL;
        } else {
            new_node->next = *head_r;
            (*head_r)->prev = new_node;
            *head_r = new_node;
        }

        if (num1_ptr) num1_ptr = num1_ptr->prev;
        if (num2_ptr) num2_ptr = num2_ptr->prev;
    }

    // Remove leading zeros from the result (except if the result is just '0')
    while (*head_r != NULL && (*head_r)->num == 0 && (*head_r)->next != NULL) {
        RList *temp = *head_r;
        *head_r = (*head_r)->next;
        (*head_r)->prev = NULL;
        free(temp);
    }

    // Print the sign if necessary
    if (result_is_negative) {
        printf("-");
    }

    // Print the result
    print_list8(*head_r);
}