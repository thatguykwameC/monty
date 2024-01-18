#include "monty.h"

/**
 * pall - Prints all elements in the stack
 * @stack: Double pointer to the stack
 * @lnCount: Line number in the file (unused in this function)
 *
 * Description: This function prints all the elements in the given stack.
 * If the stack is empty, it does nothing.
 * It then frees the entire stack.
 */

void pall(stack_t **stack, unsigned int lnCount)
{
	/* Initialize a pointer to the head of the stack */
        stack_t *head = NULL;

	/* Unused parameter to avoid compilation warnings */
	(void)lnCount;

	/* Set the head to the current top of the stack */
	head = *stack;

	/* If the stack is empty, do nothing */
	if (head == NULL)
		return;

	/* Iterate through the stack and print each element */
	while (head)
	{
		printf("%d\n", head->n);
		head = head->next;
	}

	/* Free the entire stack */
	freeStack(stack);
}
