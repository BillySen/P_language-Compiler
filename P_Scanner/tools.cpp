#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include "tools.h"

char *readFile(const char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *code;//define a variable to store the code information in the file, used for calling later
	int n = 0;
	char c;

	if (file == NULL)
		perror("Error for opening file");
	return NULL; //could not open file

//code = malloc(10000);
	while ((c = fgetc(file)) != EOF)
	{
		code[n++] = c;
	}
	// end up with NULL
	code[n] = '\0';
	fclose(file);
	return code;
}

//Judging functions
bool is_num(char c) {
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

//for making a second judgment
bool is_integer(char ch) {
	if (ch <= '9' && ch >= '0')
		return true;
	else
		return false;
}

bool is_letter(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return true;
	else
		return false;
}

bool is_operator(char c) {
	if (c == '+' || c == '*' || c == '-' || c == '=' || c == '%' || c == '<' || c == '>' || c == '!' || c == ':')
		return true;
	else
		return false;
}

bool  is_sign(char c) {
	if (c == '(' || c == ')' || c == '{' || c == '}'  || c == ','  || c == ';' || c == '?')
		return true;
	else
		return false;
}

bool is_space(char c) {
	if (c == ' ' || c == '\t')
		return true;
	else
		return false;
}

bool find_char(char *c) {
	for (int i = 0; i < sizeof(c); i++) {
		if (is_letter(c[i])) {
			return true;
		}
	}
	return false;
}


bool find_digit(char *c) {
	for (int i = 0; i < sizeof(c); i++) {
		if (is_num(c[i])) {
			return true;
		}
	}
	return false;
}

bool match_keyword(char* c) {
	for (int i = 0; i < 7; i++) {
		//c = toLower(c); //no need to convert to lower type
		if (strcmp(c, keyWord[i]) == 0) {
			return true;
		}
	}
	return false;
}

bool match_two_character_operator(char* c) {
	for (int i = 0; i < 4; i++) {
		//c = toLower(c); //no need to convert to lower type
		if (strcmp(c, two_character_operator[i]) == 0) {
			return true;
		}
	}
	return false;
}




/*bool isId(char* c, int start, int end) {

	if (c == NULL || (end - start + 1) < 0) {
		return false;
	}
	else {
		int len = end - start + 1;
		if (!is_letter(c[start]) && c[start] != '_') {   //judge the first character
			return false;
		}
		else {
			for (int i = start + 1; i <= end; ++i) {
				if (c[i] != '_' && !is_num(c[i]) && !is_letter(c[i])) {
					return false;
				}
			}
		}
		return true;
	}
}*/






