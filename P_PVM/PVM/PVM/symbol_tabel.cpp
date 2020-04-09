#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "symbol_table.h"

void sym_insert( const char *string, int pos )
{
	struct symbol sym;
	sym.string = strdup( string );
	sym.mem_pos = pos;
	syms[sym_pos++] = sym;
}

int sym_lookup( const char *string )
{
	int i;
	for( i = 0; i < sym_pos; ++ i )
	{
		if( strcmp( string, syms[i].string ) == 0 )
		{
			return syms[i].mem_pos;
		}
	}
	return -1;
}

void symboltable_clear()
{
	int i;
	for( i = 0; i < sym_pos; ++ i )
	{
		free( syms[i].string );
	}
}
