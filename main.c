#include "monty.h"

/* Global Variable */
dtContainer parsingInfo = {NULL, NULL, NULL, false};

/**
 * main - The main function of the Monty interpreter
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: Always 0 (Success)
 */

int main(int argc, char **argv)
{
	FILE *file;

	/* Initialize an empty stack */
	stack_t *stack = NULL;

	/* Check if the correct number of command-line arguments is provided */
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	/* Open the specified file for reading */
	file = fopen(argv[1], "r");

	/* Check if the file opening was successful */
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* Process the file contents */
	procFile(file, NULL, 0);

	/* Close the file */
	fclose(file);

	/* Perform cleanup and exit with success */
	Exit(&stack, EXIT_SUCCESS);

	return (0);
}
