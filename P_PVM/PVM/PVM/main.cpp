/**************************************************
***												  *                                  
@Project:  P-code virtual machine                 *
@Author:   LEI RUIJIA                             *
@E-mail:   1709853ui011001@student.must.edu.mo    *
@ID:       1709853U-I011-0012					  *
@Date:     2020/01/07							  *
***												  *
***************************************************/
#include <iostream>
#include "stack.h"
#include "func.h"
#include "symbol_table.h"

#define DATA_SIZE  1024
#define CODE_SIZE  1024

/*op_type is the instruction type，arg is the corresponding operand number*/
typedef struct p_instruction 
{
	int op_type;
	int arg;
} p_instruction;


int data_mem[1024];//data memory
p_instruction ins_mem[1024];//the memory of instruction
int PC;//the register of instruction pointer

void output(const char *file, const p_instruction *insts, int size);


/*TRANS(t) is used to modify the value of codes and size, store the operation code and relative op number into ins_mem p_instruction array*/
#define TRANS( t ) codes+=sizeof(t); size-=sizeof(t)


int get_operand_count(int op)
{
	int refer;
	switch (op)
	{
	case adi:
	case dvi:
	case equ:
	case fjp:
	case tjp:
	case ujp:
	case grt:
	case gre:
	case ixa:
	case ind:
	case lab:
	case lda:
	case lod:
	case loc:
	case ldc:
	case mpi:
	case rdi:
	case sto:
	case stn:
	case sbi:
	case stp:
	case wri:
		refer = 1;
		break;
	default:
		refer = 0;
	}
	return refer;
}

/* read codes into the ins_mem */
int read_instruction(const char *codes, int size)
{
	int ins_number, loc = 0;
	p_instruction ins;
	while (size > 0 && loc < CODE_SIZE)
	{
		/* op in the code file */
		ins.op_type = *codes;
		TRANS(char);
		ins_number = get_operand_count(ins.op_type);
		if (ins_number > 0) /* has arg */
		{
			ins.arg = *(int*)codes;
			TRANS(int);
		}
		else
		{
			ins.arg = 0;
		}
		ins_mem[loc++] = ins;
	}
	return 1;
}

void loop_execute()
{
	int refer = Keep;
	while (refer == Keep)
	{
		refer = step_run();
	}
}


int step_run()
{
	p_instruction *inst = &ins_mem[PC++];
	int refer = Keep;
	int input;

	switch (inst->op_type)
		{
		//stop
		case stp:
		{
			refer = stp;
		}
		break;
		//read
		case rdi:
		{
			printf("input:");
			scanf("%d", &input);
			stack_push(input);
		}
		break;
		//write
		case wri:
		{
			int i = stack_pop();
			printf("output:%d\n", i);
		}
		break;
		case adi:
		{
			int y = stack_pop();
			int x = stack_pop();
			stack_push(x + y);
		}
		break;
		case sbi:
		{
			int y = stack_pop();
			int x = stack_pop();
			stack_push(x - y);
		}
		break;
		case mpi:
		{
			int y = stack_pop();
			int x = stack_pop();
			stack_push(x * y);
		}
		break;
		case dvi:
		{
			int y = stack_pop();
			int x = stack_pop();
			if (y == 0)
			{
				return wrong_DivByZero;
			}
			stack_push(x / y);
		}
		break;

		/*loading*/
		case ldc:
		{
			int c = stack_pop();
		    stack_push(c);
		}
		break;
        //load address
		case lda:
		{
			int addr = stack_pop();
			if (addr < 0 || addr >= DATA_SIZE)
			{
				print_err("data memory access error");
				return exception_DataMem;
			}
			else
			{
				stack_push(data_mem[addr]);
			}
		}
		//lod x ; load the value, push the value of x
		case lod:
		{
			int x = stack_pop();
			if (x < 0 || x >= DATA_SIZE)
			{
				print_err("data memory access error");
				return exception_DataMem;
			}
			else
			{
				stack_push(x);
			}
		}
		break;
		case sto:
		{
			int val = stack_pop();
			int addr = stack_pop();
			if (addr < 0 || addr >= DATA_SIZE)
			{
				print_err("data memory access error");
				return exception_DataMem;
			}
			else
			{
				data_mem[addr] = val;
			}
		}
		case stn:
		{
			int val = stack_pop();
			int addr = stack_pop();
			if (addr < 0 || addr >= DATA_SIZE)
			{
				print_err("data memory access error");
				return exception_DataMem;
			}
			else
			{
				data_mem[addr] = val;
				stack_push(addr);
			}
		}
		break;

		/*arithmetic*/
		case grt:
		{
			int y = stack_pop();
			int x = stack_pop();
			if (x > y) 
			{
				stack_push(1);
			}
			else 
			{
				stack_push(0);
			}
		}
		case equ:
		{
			int y = stack_pop();
			int x = stack_pop();
			if (x == y)
			{
				stack_push(1);
			}
			else
			{
				stack_push(0);
			}
		}
		case gre:
		{
			int y = stack_pop();
			int x = stack_pop();
			if (x >= y)
			{
				stack_push(1);
			}
			else
			{
				stack_push(0);
			}
		}
		/*label and jump*/
		case lab:
		{
			return Keep;
		}
		//unconditional
		case ujp:
		{
			PC = inst->arg;
		}
		break;
		//true jump
		case tjp:
		{
			int x = stack_pop();
			if (x == 1)
			{
				PC = inst->arg;
			}
		}
		break;
		//false jump
		case fjp:
		{
			int x = stack_pop();
			if (x == 0)
			{
				PC = inst->arg;
			}
		}
		break;
		/*addressing*/
		case ind:
		{
			int cons = stack_pop();//constant
			int addr = stack_pop();
			if (addr < 0 || addr >= DATA_SIZE)
			{
				print_err("data memory access error");
				return exception_DataMem;
			}
			else
			{
				data_mem[addr] = addr+cons;
			}
		}
		break;
		case ixa:
		{
			int cons_a = stack_pop();//constant
			int addr = stack_pop();
			if (addr < 0 || addr >= DATA_SIZE)
			{
				print_err("data memory access error");
				return exception_DataMem;
			}
			else
			{
				data_mem[addr] = addr + cons_a;
			}
		}
		break;
		default:
			refer = errUnknownOp;
		}
	return refer;
}

int main(int argc, char **argv)
{
	FILE *fp;
	char *buf;
	int size;
	printf("Please input the file name:");
	char *name;
	scanf("%s", &name);
	if (argc < 2)
	{
		print_err("Usage: file not found");
		exit(-1);
	}

	fp = fopen(name, "rb");

	if (fp == 0) 
	{
		print_err("Open file failed");
		exit(-1);
	}

	//get the size of file
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buf = (char*)malloc(size);
	fread(buf, size, 1, fp);

	read_instruction(buf, size);

	if (argc > 2)
	{
		int f = atoi(argv[2]);
		if (f)
		{
			output(argv[1], ins_mem, CODE_SIZE);
		}
	}
	
	//execute instruction
	loop_execute();	
	
	//clear real memory
	free(buf);
	fclose(fp);
	symboltable_clear();

	return 0;
}