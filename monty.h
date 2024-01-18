#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

#define DELIMITER " \n\t"

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern instruction_t operations[];

/**
 * struct Container - container for parsing informations
 * @file: file being processed
 * @data: data to read from the file
 * @extractedArgs: arguments extracted from the data
 * @switcher: list indicator
 *
 * Description: a mini object-oriented approach list to keep
 * stack/queues
 */

typedef struct Container
{
	FILE *file;
	char *data;
	char *extractedArgs;
	bool switcher;
} dtContainer;

extern dtContainer parsingInfo;

/* Function Prototypes */
ssize_t readCmd(char **bfr, size_t *sz, unsigned int *lC, FILE *fl, char **dt);
void execOp(char *ocd, stack_t **stk, short lC, FILE *fl, instruction_t *op);
int execCmd(char *data, stack_t **stack, FILE *file, unsigned int lnCount);
int Exe(char *oc, stack_t **sk, unsigned int lc, FILE *fl, instruction_t *op);
void procFile(FILE *file, char *data, unsigned int line_number);
void errHandler(const char *msg, short lnNumber, stack_t **stack, FILE *file);
void Exit(stack_t **stack, int log);
void freeStack(stack_t **stack);
void clean(stack_t **stack, FILE *file);
void insertNode(stack_t **stack, int n);
void insertQueue(stack_t **stack, int n, const char *errMsg);
void checkPushArgs(const char *args, unsigned int lnCount, stack_t **stack);
void _pushToSorQ(stack_t **stack, unsigned int lnCount);
void pall(stack_t **stack, unsigned int lnCount);
void handleUnk(int lc, char *oc, FILE *fl, char *dt, stack_t **stack);

#endif /* MONTY_H */
