/*
Project: parser(based on scanner)
PAN WENXI & LEIRUIJIA
contact us at 1709853ui011001@student.must.edu.mo
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "automata.h"


struct Node *setToken(int line, char *type, char *val, struct Node *node)
{
	struct Token t;
	t.line = line;
	strcpy(t.type, type);
	strcpy(t.val, val);
	node = newNode(node, t);
	return node;
}


void skipSpace()
{
	fpos_t pos;
	char ch;
	while (1) 
	{
		fgetpos(fp, &pos);
		ch = fgetc(fp);
		if (ch != ' ' && ch != '\t' && ch != '\v')
		{
			fsetpos(fp, &pos);
			break;
		}
	}
}


int isEnter(char ch)
{
	if (ch == '\n' || ch == '\r')
		return 1;
	return 0;
}


int isSemi(char ch)
{
	if (ch == ';')
		return 1;
	return 0;
}


int isComma(char ch)
{
	if (ch == ',')
		return 1;
	return 0;
}


int getBracket(char ch)
{
	//()
	if (ch == '(') {
		return 1;
	}
	if (ch == ')') {
		return 2;
	}

	//[]
	if (ch == '[') {
		return 3;
	}
	if (ch == ']') {
		return 4;
	}

	//{}
	if (ch == '{') {
		return 5;
	}
	if (ch == '}') {
		return 6;
	}

	return 0;
}


int getKey(char ch)
{
	fpos_t pos;
	fpos_t pos_temp;
	fgetpos(fp, &pos);
	//num
	if (ch == 'n') {
		ch = fgetc(fp);
		if (ch == 'u') {
			ch = fgetc(fp);
			if (ch == 'm') {
				ch = fgetc(fp);
				if (ch == ' ') {
					return 1;
				}
			}
		}
		fsetpos(fp, &pos);
	}

	//void
	else if (ch == 'v') {
		ch = fgetc(fp);
		if (ch == 'o') {
			ch = fgetc(fp);
			if (ch == 'i') {
				ch = fgetc(fp);
				if (ch == 'd') {
					fgetpos(fp, &pos_temp);
					ch = fgetc(fp);
					if (ch == ' ' || ch == ')') {
						fsetpos(fp, &pos_temp);
						return 2;
					}
				}
			}
		}
		fsetpos(fp, &pos);
	}

	//if
	else if (ch == 'i') {
		ch = fgetc(fp);
		if (ch == 'f') {
			fgetpos(fp, &pos_temp);
			ch = fgetc(fp);
			if (ch == ' ' || ch == '(') {
				fsetpos(fp, &pos_temp);
				return 3;
			}
		}
		fsetpos(fp, &pos);
	}

	//else
	else if (ch == 'e') {
		ch = fgetc(fp);
		if (ch == 'l') {
			ch = fgetc(fp);
			if (ch == 's') {
				ch = fgetc(fp);
				if (ch == 'e') {
					ch = fgetc(fp);
					if (ch == ' ' || ch == '\n' || ch == '\r') {
						return 4;
					}
				}
			}
		}
		fsetpos(fp, &pos);
	}

	//while
	else if (ch == 'w') {
		ch = fgetc(fp);
		if (ch == 'h') {
			ch = fgetc(fp);
			if (ch == 'i') {
				ch = fgetc(fp);
				if (ch == 'l') {
					ch = fgetc(fp);
					if (ch == 'e') {
						fgetpos(fp, &pos_temp);
						ch = fgetc(fp);
						if (ch == ' ' || ch == '(') {
							fsetpos(fp, &pos_temp);
							return 5;
						}
					}
				}
			}
		}
		fsetpos(fp, &pos);
	}

	//return
	else if (ch == 'r') {
		ch = fgetc(fp);
		if (ch == 'e') {
			ch = fgetc(fp);
			if (ch == 't') {
				ch = fgetc(fp);
				if (ch == 'u') {
					ch = fgetc(fp);
					if (ch == 'r') {
						ch = fgetc(fp);
						if (ch == 'n') {
							ch = fgetc(fp);
							if (ch == ' ') {
								return 6;
							}
						}
					}
				}
			}
		}
		fsetpos(fp, &pos);
	}
	return 0;
}


int getOp(char ch, struct Node *node)
{
	fpos_t pos;
	fgetpos(fp, &pos);
	if (ch == '+') {
		return 1;
	}
	if (ch == '-') {
		if (strcmp(node->t.type, NUM) == 0 || strcmp(node->t.type, ID) == 0)  // negative or subtract
			return 2;
		if (isStartFunc(ch)) {
			fsetpos(fp, &pos);
			return 0;
		}
		return -2;
	}
	if (ch == '*') {
		if (strcmp(node->t.type, NUMT) == 0 || strcmp(node->t.type, VOIDT) == 0)
			return -3;
		return 3;
	}
	if (ch == '/') {
		if (isComment(ch)) // comment
		{
			fsetpos(fp, &pos);
			return 0;
		}
		return 4;
	}
	if (ch == '%') {
		return 5;
	}

	if (ch == '=') {
		ch = fgetc(fp);
		if (ch == '=')
			return 6;
		fsetpos(fp, &pos);
		return 7;
	}
	if (ch == '!') {
		ch = fgetc(fp);
		if (ch == '=')
			return 8;
		fsetpos(fp, &pos);
		return 9;
	}
	if (ch == '>') {
		ch = fgetc(fp);
		if (ch == '=')
			return 10;
		fsetpos(fp, &pos);
		return 11;
	}
	if (ch == '<') {
		ch = fgetc(fp);
		if (ch == '=')
			return 12;
		fsetpos(fp, &pos);
		return 13;
	}
	if (ch == '&') {
		ch = fgetc(fp);
		if (ch == '&')
			return 14;
		fsetpos(fp, &pos);
		return 15;
	}
	if (ch == '|') {
		ch = fgetc(fp);
		if (ch == '|')
			return 16;
		fsetpos(fp, &pos);
		return -16;
	}
	return 0;
}


char *getString(char ch)
{
	if (ch == '"') {
		char token_s[100];
		strcpy(token_s, "");
		char ch_s[] = {ch, '\0'};
		strcat(token_s, ch_s);
		while (1)
		{
			ch = fgetc(fp);
			char ch_s[] = {ch, '\0'};
			strcat(token_s, ch_s);
			if (ch == '"')
				break;
		}
		return token_s;
	}

	return "0";
}


char *getNum(char ch, struct Node *node)
{
	if (isdigit(ch)) {
		fpos_t pos;
		char token_s[100];
		strcpy(token_s, "");
		char ch_s[] = {ch, '\0'};
		strcat(token_s, ch_s);
		while(1)
		{
			fgetpos(fp, &pos);
			ch = fgetc(fp);
			if (!(isdigit(ch) || ch == '|')) {
				fsetpos(fp, &pos);
				if (getOp(ch, node)==0 && !isComma(ch) && !isSemi(ch) && getBracket(ch)==0 && ch!=' ') {
					return "error";
				}
				break;
			}
			char ch_s[] = {ch, '\0'};
			strcat(token_s, ch_s);
		}
		return token_s;
	}
	return "---";
}


char *getId(char ch)
{
	fpos_t pos;
	char token_s[100];
	strcpy(token_s, "");
	if (ch == '_' || isalpha(ch)) {
		char ch_s[] = {ch, '\0'};
		strcat(token_s, ch_s);
		while (1)
		{
			fgetpos(fp, &pos);
			ch = fgetc(fp);
			if (!(ch == '_' || isalnum(ch))) {
				fsetpos(fp, &pos);
				break;
			}
			char ch_s[] = {ch, '\0'};
			strcat(token_s, ch_s);
		}
		return token_s;
	}
	return "000";
}


int isComment(char ch)
{
	fpos_t pos;
	fgetpos(fp, &pos);
	if (ch == '/') {
		char ch = fgetc(fp);
		if (ch == '/')
		{
			while (1)
			{
				ch = fgetc(fp);
				if (isEnter(ch))
					return 1;
			}
		}
		if (ch == '*') {
			while (1)
			{
				ch = fgetc(fp);
				if (ch == '*') {
					ch = fgetc(fp);
					if (ch == '/') {
						return 1;
					}
				}
				if (ch == EOF)
					return -1;
			}
		}
	}
	fsetpos(fp, &pos);
	return 0;
}


int isStartFunc(char ch)
{
	fpos_t pos;
	fgetpos(fp, &pos);
	if (ch == '-') {
		char ch = fgetc(fp);
		if (ch == '-') {
			char ch = fgetc(fp);
			if (ch == '>') {
				return 1;
			}
		}
	}
	fsetpos(fp, &pos);
	return 0;
}


int isEndFunc(char ch)
{
	fpos_t pos;
	fgetpos(fp, &pos);
	if (ch == ':') {
		ch = fgetc(fp);
		if (ch == ')'){
			return 1;
		}
	}
	fsetpos(fp, &pos);
	return 0;
}
