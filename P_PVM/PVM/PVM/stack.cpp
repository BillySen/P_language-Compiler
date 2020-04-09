#include <string>
#include <iostream>
#include "stack.h"

#define POP_ERR  (-1)
#define STACK_SIZE 1024


void print_err(const char *err)
{
	fprintf(stderr, err);
}


/* the definition of stack */
int stack[STACK_SIZE];//the area stack operation
int stack_pos = 0;//index of stack

/*stack function*/
/**/
int stack_push(int i)
{
	if (stack_pos >= STACK_SIZE)
	{
		print_err("stack overflow");
		return -1;
	}
	stack[stack_pos++] = i;
	return 0;
}

/**/
int stack_pop()
{
	if (stack_pos == 0)
	{
		print_err("stack empty");
		return POP_ERR;
	}
	return stack[--stack_pos];
}