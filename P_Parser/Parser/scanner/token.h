//Pan Wenxi, 0010

#ifndef TOKEN_H
#define TOKEN_H


#define NUM "NUM"
#define ARRAY "ARRAY"
#define ID "ID" 
#define STARTFUNC "STARTFUNC"
#define ENDFUNC "ENDFUNC"
#define STRING "STRING" 
#define SEMI "SEMI"
#define COMMA "COMMA"
#define IF "IF"
#define ELSE "ELSE"
#define WHILE "WHILE"
#define RETURN "RETURN"
#define ENTER "ENTER"
#define NUMT "NUMT"
#define VOIDT "VOIDT"
#define ADD "ADD"
#define SUB "SUB"
#define MUL "MUL"
#define DIV "DIV"
#define MOD "MOD"
#define ASSIGN "ASSIGN"
#define NEG "NEG"
#define GT "GT"
#define GE "GE"
#define LT "LT"
#define LE "LE"
#define EQ "EQ"
#define NEQ "NEQ"
#define AND "AND"
#define OR "OR"
#define NOT "NOT"
#define ADDR "ADDR"
#define PTR "PTR"
#define LPAR "LPAR"
#define RPAR "RPAR"
#define LSQBR "LSQBR"
#define RSQBR "RSQBR"
#define LCUBR "LCUBR"
#define RCUBR "RCUBR"
#define ERROR "    ERROR"


struct Token
{
	int line;
	char type[10];
	char val[100];
};


#endif
