#include "monty.h"

/**
 * errHandler - Handles errors by printing an error message, cleaning up,
 *              and exiting the program with EXIT_FAILURE.
 * @msg: The error message
 * @lnNumber: Line number where the error occurred
 * @stack: Double pointer to the stack
 * @file: File being processed
 */

void errHandler(const char *msg, short lnNumber, stack_t **stack, FILE *file)
{
	const char *errMsg = "L%d: %s\n";

	/* Print error message with line number */
	fprintf(stderr, errMsg, lnNumber, msg);

	/* Clean up and exit with failure */
	clean(stack, file);
	exit(EXIT_FAILURE);
}

/**
 * Exit - Cleans up resources, exits the program with a specified code.
 * @stack: Double pointer to the stack
 * @log: Exit code
 */

void Exit(stack_t **stack, int log)
{
	/* Free the stack if it exists */
	if (stack != NULL)
	{
		freeStack(stack);
		*stack = NULL;
	}

	/* Free extracted arguments */
	if (parsingInfo.extractedArgs)
		free(parsingInfo.extractedArgs);

	/* Free data buffer */
	if (parsingInfo.data)
	{
		free(parsingInfo.data);
		parsingInfo.data = NULL;
	}

	/* Clean up and exit with the specified code */
	clean(stack, parsingInfo.file);
	exit(log);
}

/**
 * freeStack - Frees the entire stack.
 * @stack: Double pointer to the stack
 */

void freeStack(stack_t **stack)
{
	while (stack && *stack)
	{
		stack_t *st = (*stack)->next;

		free(*stack);
		*stack = st;
	}
}

/**
 * clean - Cleans up resources, including freeing extracted arguments,
 *         data buffer, closing the file, and freeing the entire stack.
 * @stack: Double pointer to the stack
 * @file: File being processed (unused in this function)
 */

void clean(stack_t **stack, FILE *file)
{
	/* Unused parameter to avoid compilation warnings */
	(void)file;

	/* Free extracted arguments */
	if (parsingInfo.extractedArgs)
		free(parsingInfo.extractedArgs);

	/* Free data buffer */
	if (parsingInfo.data)
		free(parsingInfo.data);

	/* Close the file if it exists */
	if (parsingInfo.file)
	{
		fclose(parsingInfo.file);
		parsingInfo.file = NULL;
	}

	/* Free the entire stack */
	freeStack(stack);
}
