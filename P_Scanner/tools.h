#ifndef _TOOLS_H
#define _TOOLS_H
#include "token.h"


bool is_num(char c);
bool is_integer(char ch);
bool is_letter(char c);
bool is_operator(char c);
bool is_space(char c);
bool is_sign(char c);
bool find_char(char *c);
bool find_digit(char *c);
bool match_keyword(char* c);
bool match_two_character_operator(char* c);


char *readFile(char *fileName);
//void add_to_token_list(List *list, Token *token);

#endif // !_TOOLS_H
