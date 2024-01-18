#include "monty.h"

/**
 * handleUnk - Handles an unknown instruction by printing an error message,
 *              cleaning up, and exiting the program with EXIT_FAILURE.
 * @lc: Line number where the unknown instruction occurred
 * @oc: Opcode of the unknown instruction
 * @fl: File being processed
 * @dt: Data buffer
 * @stack: Double pointer to the stack
 */

void handleUnk(int lc, char *oc, FILE *fl, char *dt, stack_t **stack)
{
	fprintf(stderr, "L%d: unknown instruction %s\n", lc, oc);
	fclose(fl);
	free(dt);
	freeStack(stack);
	exit(EXIT_FAILURE);
}

/**
 * insertNode - Inserts a new node at the beginning of the stack.
 * @stack: Double pointer to the stack
 * @n: Integer value for the new node
 */

void insertNode(stack_t **stack, int n)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		clean(stack, parsingInfo.file);
		exit(EXIT_FAILURE);
	}

	new_node->n = n;
	new_node->next = (*stack);
	new_node->prev = NULL;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	(*stack) = new_node;
}

/**
 * insertQueue - Inserts a new node at the end of the stack.
 * @stack: Double pointer to the stack
 * @n: Integer value for the new node
 * @errMsg: Error message in case of malloc failure
 */

void insertQueue(stack_t **stack, int n, const char *errMsg)
{
	stack_t *new_node, *prev_node;

	new_node = (stack_t *)malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		if (parsingInfo.extractedArgs)
		{
			free(parsingInfo.extractedArgs);
			parsingInfo.extractedArgs = NULL;
		}
		write(STDERR_FILENO, errMsg, strlen(errMsg));
		clean(stack, parsingInfo.file);
		exit(EXIT_FAILURE);
	}

	new_node->n = n;
	new_node->next = NULL;
	if ((*stack) == NULL)
	{
		(*stack) = new_node;
		new_node->prev = NULL;
	}
	else
	{
		prev_node = (*stack);

		while (prev_node->next != NULL)
			prev_node = prev_node->next;

		prev_node->next = new_node;
		new_node->prev = prev_node;
	}

	if (parsingInfo.extractedArgs)
	{
		free(parsingInfo.extractedArgs);
		parsingInfo.extractedArgs = NULL;
	}
}

/**
 * checkPushArgs - Checks if the arguments for the push instruction are valid.
 * @args: Arguments for the push instruction
 * @lnCount: Line number in the file
 * @stack: Double pointer to the stack
 */

void checkPushArgs(const char *args, unsigned int lnCount, stack_t **stack)
{
	int j = 0;

	if (args == NULL || args[0] == '\0')
	{
		fprintf(stderr, "L%d: usage: push integer\n", lnCount);
		clean(stack, parsingInfo.file);
		exit(EXIT_FAILURE);
	}

	j = (args[0] == '-') ? 1 : 0;

	while (args[j] != '\0')
	{
		if (args[j] < '0' || args[j] > '9')
		{
			fprintf(stderr, "L%d: usage: push integer\n", lnCount);
			clean(stack, parsingInfo.file);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

/**
 * _pushToSorQ - Handles the push instruction by checking arguments,
 *               converting to an integer, and inserting into the stack.
 * @stack: Double pointer to the stack
 * @lnCount: Line number in the file (unused in this function)
 */

void _pushToSorQ(stack_t **stack, unsigned int lnCount)
{
	int n = 0;
	(void)lnCount;

	checkPushArgs(parsingInfo.extractedArgs, lnCount, stack);

	n = atoi(parsingInfo.extractedArgs);

	if (parsingInfo.switcher == 0)
		insertNode(stack, n);
	else
		insertQueue(stack, n, "Error: malloc failed\n");

	if (parsingInfo.extractedArgs)
	{
		free(parsingInfo.extractedArgs);
		parsingInfo.extractedArgs = NULL;
	}
}
