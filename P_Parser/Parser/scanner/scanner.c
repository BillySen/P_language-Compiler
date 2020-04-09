#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tools.h"
#include "automata.h"


struct Node *scanner()
{
	//create list
	struct Node *first = emptyNode();
	struct Node *node = first;
	struct Token t;
	char ch;
	int token_line = 1;
	int error_count = 0;
	char token_s[100];
	fpos_t pos;
	while (1)
	{
		strcpy(token_s, "");
		fgetpos(fp, &pos);
		//end reading
		if (fgetc(fp) == EOF){
			break;
		}
		fsetpos(fp, &pos);

		//space
		skipSpace();
		ch = fgetc(fp);

		if (ch == '\r')
			continue;
		
		//enter
		if (isEnter(ch)) {
			node = setToken(token_line, ENTER, "", node);
			token_line++;
			continue;
		}

		//;
		if (isSemi(ch)) {
			node = setToken(token_line, SEMI, "", node);
			continue;
		}

		if (isComma(ch)) {
			node = setToken(token_line, COMMA, "", node);
			continue;
		}

		//brackets
		int get_bracket = getBracket(ch);
		switch (get_bracket) {
			case 1:
				node = setToken(token_line, LPAR, "", node);
				break;
			case 2:
				node = setToken(token_line, RPAR, "", node);
				break;
			case 3:
				node = setToken(token_line, LSQBR, "", node);
				break;
			case 4:
				node = setToken(token_line, RSQBR, "", node);
				break;
			case 5:
				node = setToken(token_line, LCUBR, "", node);
				break;
			case 6:
				node = setToken(token_line, RCUBR, "", node);
				break;
			default:
				break;
		}
		if (get_bracket != 0)
			continue;

		//operator
		int get_op = getOp(ch, node);
		switch (get_op) {
			case 1:
				node = setToken(token_line, ADD, "", node);
				break;
			case 2:
				node = setToken(token_line, SUB, "", node);
				break;
			case -2:
				node = setToken(token_line, NEG, "", node);
				break;
			case 3:
				node = setToken(token_line, MUL, "", node);
				break;
			case -3:
				node = setToken(token_line, PTR, "", node);
				break;
			case 4:
				node = setToken(token_line, DIV, "", node);
				break;
			case 5:
				node = setToken(token_line, MOD, "", node);
				break;

			case 6:
				node = setToken(token_line, EQ, "", node);
				break;
			case 7:
				node = setToken(token_line, ASSIGN, "", node);
				break;
			case 8:
				node = setToken(token_line, NEQ, "", node);
				break;
			case 9:
				node = setToken(token_line, NOT, "", node);
				break;
			case 10:
				node = setToken(token_line, GE, "", node);
				break;
			case 11:
				node = setToken(token_line, GT, "", node);
				break;
			case 12:
				node = setToken(token_line, LE, "", node);
				break;
			case 13:
				node = setToken(token_line, LT, "", node);
				break;
			case 14:
				node = setToken(token_line, AND, "", node);
				break;
			case 15:
				node = setToken(token_line, ADDR, "", node);
				break;
			case 16:
				node = setToken(token_line, OR, "", node);
				break;
			case -16:
				node = setToken(token_line, ERROR, "Invalid operator", node);
				error_count++;
				break;
			default:
				break;
		}
		if (get_op != 0)
			continue;

		int is_comment = isComment(ch);
		if (is_comment == 1) {
			continue;
		}
		else if (is_comment == -1) {
			setToken(token_line, ERROR, "Invalid comment", node);
			error_count++;
			continue;
		}

		//function start
		if (isStartFunc(ch)) {
			node = setToken(token_line, STARTFUNC, "", node);
			continue;
		}

		//function end
		if (isEndFunc(ch)) {
			node = setToken(token_line, ENDFUNC, "", node);
			continue;
		}

		//string
		strcat(token_s, getString(ch));
		if (strcmp(token_s, "0") != 0) {
			node = setToken(token_line, STRING, token_s, node);
			continue;
		}
		strcpy(token_s, "");

		//KEY
		int get_key = getKey(ch);
		switch (get_key) {
			case 1:
				node = setToken(token_line, NUMT, "", node);
				break;
			case 2:
				node = setToken(token_line, VOIDT, "", node);
				break;
			case 3:
				node = setToken(token_line, IF, "", node);
				break;
			case 4:
				node = setToken(token_line, ELSE, "", node);
				break;
			case 5:
				node = setToken(token_line, WHILE, "", node);
				break;
			case 6:
				node = setToken(token_line, RETURN, "", node);
				break;
			default:
				break;
		}
		if (get_key != 0)
			continue;

		//ID
		strcpy(token_s, getId(ch));
		if (strcmp(token_s, "000") != 0) {
			node = setToken(token_line, ID, token_s, node);
			continue;
		}
		strcpy(token_s, "");

		//NUM
		strcpy(token_s, getNum(ch, node));
		if (strcmp(token_s, "---") != 0) {
			if (strcmp(token_s, "error") == 0)
			{
				node = setToken(token_line, ERROR, "Invalid number", node);
				error_count++;
				continue;
			}
			node = setToken(token_line, NUM, token_s, node);
			continue;
		}
		strcpy(token_s, "");
		node = setToken(token_line, ERROR, "Invalid token", node);
		error_count++;
	}
	struct Node *end = emptyNode();
	strcpy(end->t.type, "END");
	node->next = end;
	end->prev = node;

	//error
	t.line = 0;
	strcpy(t.val, "");
	if (error_count != 0)
	{
		strcpy(t.type, ERROR);
	}
	else
	{
		strcpy(t.type, "");
	}
	first->t = t;
	printList(error_count, first);
	fclose(fp);
	return first;
}
