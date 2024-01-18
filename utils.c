#include "monty.h"

/**
 * readCmd - Reads a command from a file and extracts data.
 * @bfr: Pointer to the buffer to store the data
 * @sz: Pointer to the size of the buffer
 * @lC: Pointer to the line count
 * @fl: File to read from
 * @dt: Pointer to store the extracted data
 * Return: The number of characters read (including the newline character),
 *         or 0 if the end of the file is reached, or -1 on failure.
 */

ssize_t readCmd(char **bfr, size_t *sz, unsigned int *lC, FILE *fl, char **dt)
{
	ssize_t readdt;
	*bfr = NULL;

	readdt = getline(bfr, sz, fl);

	if (readdt > 0)
	{
		(*lC)++;
		return (readdt);
	}
	else if (readdt == -1)
	{
		if (*bfr)
		{
			free(*bfr);
			*bfr = NULL;
		}

		if (*dt)
		{
			free(*dt);
			*dt = NULL;
		}
		Exit(NULL, EXIT_FAILURE);
	}

	return (0);
}

/**
 * execOp - Executes an operation based on the given opcode.
 * @ocd: Opcode to execute
 * @stk: Pointer to the stack
 * @lC: Line number in the file
 * @fl: File being processed
 * @op: Array of operations and their corresponding functions
 */

void execOp(char *ocd, stack_t **stk, short lC, FILE *fl, instruction_t *op)
{
	unsigned int i = 0;

	if (ocd)
	{
		while (op[i].opcode)
		{
			if (strcmp(ocd, op[i].opcode) == 0)
			{
				op[i].f(stk, lC);
				return;
			}
			i++;
		}
	}
	else
		errHandler("NULL opcode", lC, stk, fl);

	errHandler("unknown instruction", lC, stk, fl);
}

/**
 * execCmd - Executes a command based on the given opcode.
 * @data: Data containing the command and arguments
 * @stack: Pointer to the stack
 * @file: File being processed
 * @lnCount: Line number in the file
 * Return: 0 on success, 1 if opcode is unknown, -1 on failure.
 */

int execCmd(char *data, stack_t **stack, FILE *file, unsigned int lnCount)
{
	instruction_t operations[] = {
		{"push", _pushToSorQ},
		{"pall", pall},
		{NULL, NULL}
	};

	char *opcode = strtok(data, DELIMITER);
	char *extractedArgs = strtok(NULL, DELIMITER);
	int exec;

	if (extractedArgs)
	{
		parsingInfo.extractedArgs = strdup(extractedArgs);
		if (parsingInfo.extractedArgs == NULL)
		{
			fprintf(stderr, "Error: strdup failed\n");
			clean(stack, file);
			Exit(NULL, EXIT_FAILURE);
		}
	}
	else
		parsingInfo.extractedArgs = NULL;

	exec = Exe(opcode, stack, lnCount, file, operations);

	if (exec == 1)
		handleUnk(lnCount, opcode, file, data, stack);

	if (parsingInfo.extractedArgs)
	{
		free(parsingInfo.extractedArgs);
		parsingInfo.extractedArgs = NULL;
	}

	return (exec);
}

/**
 * Exe - Executes a command based on the given opcode.
 * @oc: Opcode to execute
 * @sk: Pointer to the stack
 * @lc: Line number in the file
 * @fl: File being processed
 * @op: Array of operations and their corresponding functions
 * Return: 0 on success, 1 if opcode is unknown.
 */

int Exe(char *oc, stack_t **sk, unsigned int lc, FILE *fl, instruction_t *op)
{
	unsigned short i = 0;
	(void)fl;

	while (op[i].opcode && oc)
	{
		if (strcmp(oc, op[i].opcode) == 0)
		{
			op[i].f(sk, lc);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * procFile - Processes the contents of a file, executing commands.
 * @file: File to process
 * @data: Data to read from the file
 * @line_number: Line number in the file
 */

void procFile(FILE *file, char *data, unsigned int line_number)
{
	size_t size = 0;
	stack_t *stack = NULL;
	ssize_t readdt = 1;

	while (readdt > 0)
	{
		data = NULL;
		readdt = readCmd(&data, &size, &line_number, file, &data);
		line_number++;

		if (readdt > 0)
		{
			execCmd(data, &stack, file, line_number);
			free(data);
		}
	}

	freeStack(&stack);
}
