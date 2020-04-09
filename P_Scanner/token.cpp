#include <string>
#include <iostream>
#include "token.h"

int indexOfToken = 0;
Token token_buffer[256];


/* Intuitive table of relative description between signs and representitive words                   
NUM:												data type
STRING:												data type
ID:													variable name and function name 
VOID,IF,WHILE,FOR,ELSE,RETURN,SWICH,CASE:			keywords (corresponding to lower case)  
LPAR,RPAR,LBCT,RBCT:								left and right parentheses/brackets "("  ")" "[" "]"
ASSIN:												equal "="
SEMI:												semicolon ";"   
COL:                  								colon ":"
COM:												comma ","
NVG:												negative sign "-"  
PLUS,MINUS,MULTI,DIV,MOD,GRETER,LESS,QUES,NOT:	    operator  + - * / % > < ? !(single character)
ANNOT:												annotation  "/ *"  "* /"  "//"
GREATER_OR_EQUAL,LESS_OR_EQUAL,UNEQUAL,EQUAL_EQUAL:	>=, <=, != ,==
FUNC_START,FUNC_END:								start and end signs of function  "-->"  ":)"
ENTER:												newline "\n"
*/

char *tokentype_namelist[] = { "ID", "NUMBER", "STRING",
				   "VOID", "IF", "WHILE","FOR", "ELSE", "RETURN",
				   "LPAR", "RPAR","LBCT","RBCT", "ASSIN", "SEMI", "COL", "COM", "NVG",
    		       "PLUS", "MINUS", "MULTI", "DIV", "MOD","GREATER","LESS" ,"QUES","NOT",
			   	   "ANNOT_START", "ANNOT_END", "ANNOTATION",
				   "GRETER_OR_EQUAL","LESS_OR_EQUAL","UNEQUAL","EQUAL_EQUAL",
				   "FUNC_START","FUNC_END",
				   "ENTER","NVG_NUM","KEYWORD",
                   "OTHER","TRAP","ERROR"};

char *keyWord[7] = { "void","if","while","for","else","return","num" };
char *two_character_operator[4] = { ">=","<=","==","!=" };
//char *single_operator[] = { "=","+","%","*","/","-",">","<" };



void setTokenBuffer(char* type, char* value) {
	int i = 0;
	for(i = 0; i < sizeof(tokentype_namelist)/ sizeof(tokentype_namelist[0]); i++)
	{
		if (strcmp(type, tokentype_namelist[i]) == 0) 
			break;
	}

	if(i < sizeof(tokentype_namelist) / sizeof(tokentype_namelist[0]))
	{
		token_buffer[indexOfToken].type = (TokenType)i;//select type from TokenType to token_buffer's type
		strcpy(token_buffer[indexOfToken].value, value);
		if(indexOfToken < sizeof(token_buffer) / sizeof(Token))
		   indexOfToken ++;
	}
}
