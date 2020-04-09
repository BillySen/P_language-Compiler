#pragma once
#ifndef _SYMBOL_TABLE_H
#define _SYMBOL_TABLE_H

#define SIZE (256)

struct symbol
{
	char *string;
	int mem_pos;
};

struct symbol syms[SIZE];
static int sym_pos = 0;

int sym_lookup(const char *string);
void sym_insert(const char *string, int loc);

void symboltable_clear();


#endif