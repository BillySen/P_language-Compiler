#pragma once
#ifndef _STACK_H
#define _STACK_H

/*traget instruction in p-code file*/
enum p_instruction_type
{
	adi,dvi, mpi,sbi,
	equ,
	fjp, tjp, ujp,
	grt,gre,
	ixa, ind,
	lab,lda,lod,loc,ldc,
	rdi,
	sto,stn,stp,
	wri
};

//Error code
enum err_code
{
	stop, Keep, wrong_DivByZero, exception_DataMem, exception_InsMem, 
	exception_StackOverflow, exception_StackEmpty,errUnknownOp
};


/*From the description of assignment: When the stack is not empty, return the data (integer) at the top, and top = top − 1.
When the stack is empty, nothing is popped, and some error message is printed out.*/
int stack_pop();

/*From the description of assignment: When the stack is not full, top = top + 1, and c is saved at the top 
in the data area. When the stack is already full, nothing is pushed, and some error message is printed.*/
int stack_push(int c);

int stack_top();

void print_err(const char *err);

#endif
