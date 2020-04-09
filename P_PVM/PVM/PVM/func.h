#pragma once
#ifndef _FUNC_H
#define _FUNC_H

int get_operand_count(int op);
//void output(const char *file, const p_instruction *insts, int size);
void loop_execute();
int step_run();
int read_instruction(const char *codes, int size);

#endif