/**************************************************
***												  *
Individually                                      *
@Project:  N-language lexical analyser            *
@Author:   LEI RUIJIA                             *
@E-mail:   1709853ui011001@student.must.edu.mo    *
@ID:       1709853U-I011-0012					  *
@Date:     2019/11/12							  *
***												  *
***************************************************/

/*
Description: Using ".cpp" suffix in order to use CPP library and prevent some unpredictable errors.
			 the syntax is all written by C language
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"//integrate all header files I created

#define T_LEN 200 //length of token array 

char * m_code;//store all of the information in the test file
char *readFile(char *fname)
{
	//errno_t err;
	FILE *file;
	file = fopen(fname, "r");
	long n = 0;
	char c;

	if (file == NULL)
	{
		perror("Error for opening file");
		return NULL; //could not open file
	}

	//file location 
	fseek(file, 0, SEEK_END);

	//get file length
	long  inputFileLength = ftell(file);

	m_code = (char *)malloc(inputFileLength + 1);
	fseek(file, 0, SEEK_SET);
	while ((c = fgetc(file)) != EOF)
	{
		m_code[n++] = c;
	}
	// end up with NULL
	m_code[n] = '\0';
	fclose(file);
	return m_code;
}

void n_lexical_print(struct Token *arr) {
	int column_num=1;
	printf("************ N language scanner ************\n");
	printf("************ Start the scanner *************\n\n");
	for (int i = 0; i < indexOfToken; i++) {
		if (arr[i].type == ID || arr[i].type == NUMBER || arr[i].type == STRING || arr[i].type == KEYWORD || arr[i].type == ANNOTATION
			|| arr[i].type == FUNC_END|| arr[i].type == FUNC_START|| arr[i].type == QUES || arr[i].type == ERROR ) {
				printf("%d  %s: %s \n", column_num,tokentype_namelist[(int)arr[i].type], arr[i].value);
		}
		else if (arr[i].type == LPAR || arr[i].type == RPAR || arr[i].type == MULTI || arr[i].type == COM || arr[i].type == LBCT || arr[i].type == RBCT 
			     || arr[i].type == COL || arr[i].type == SEMI || arr[i].type == PLUS || arr[i].type == MINUS || arr[i].type == NOT
			     || arr[i].type == MINUS || arr[i].type == LESS || arr[i].type == GREATER || arr[i].type == ASSIN || arr[i].type == MOD )
			printf("%d  %s \n", column_num,tokentype_namelist[(int)arr[i].type]);
		else if (arr[i].type == ENTER) {
			
			printf("%d  %s \n", column_num,tokentype_namelist[(int)arr[i].type]);
			column_num++;
		}
		else if (arr[i].type == LESS_OR_EQUAL || arr[i].type == GREATER_OR_EQUAL || arr[i].type == EQUAL_EQUAL || arr[i].type == UNEQUAL)
			printf("%d  %s \n", column_num,tokentype_namelist[(int)arr[i].type]);
	}
	printf("************The End************\n");
}

void getToken(char *code)
{
	int indexOfCode = 0;
	char token[T_LEN] = { 0 };

	while (code[indexOfCode] != '\0') {
		// when encounter space
		if (is_space(code[indexOfCode])) {
			token[0] = code[indexOfCode];
			setTokenBuffer("Space", token);
			indexOfCode++;
		}
		//    ( ) , { } ; ! ?
		else if (is_sign(code[indexOfCode])) {
			int temp1_state_num;
			if (code[indexOfCode] == '(')
				temp1_state_num = LPAR; //9
			else if (code[indexOfCode] == ')')
				temp1_state_num = RPAR; //10
			else if (code[indexOfCode] == ',')
				temp1_state_num = COM;  //16
			else if (code[indexOfCode] == '{')
				temp1_state_num = LBCT; //11
			else if (code[indexOfCode] == '}')
				temp1_state_num = RBCT; //12
			else if (code[indexOfCode] == ';')
				temp1_state_num = SEMI; //14
			else if (code[indexOfCode] == '?')
				temp1_state_num = QUES; //25
			switch (temp1_state_num) {
				case LPAR: token[0] = code[indexOfCode]; setTokenBuffer("LPAR", token); indexOfCode++; break;
				case RPAR: token[0] = code[indexOfCode]; setTokenBuffer("RPAR", token); indexOfCode++; break;
				case COM: token[0] = code[indexOfCode]; setTokenBuffer("COM", token); indexOfCode++; break;
				case LBCT: token[0] = code[indexOfCode]; setTokenBuffer("LBCT", token); indexOfCode++; break;
				case RBCT: token[0] = code[indexOfCode]; setTokenBuffer("RBCT", token); indexOfCode++; break;
				case SEMI: token[0] = code[indexOfCode]; setTokenBuffer("SEMI", token); indexOfCode++; break;
				case QUES: //token[0] = code[indexOfCode]; setTokenBuffer("QUES", token); 
					 setTokenBuffer("QUES", "Error: \"?\" is illegal!"); indexOfCode++; break;
				default:  indexOfCode++; /*printf("Sign token error\n");*/ break;
			}
		}//end if
		//  single and double character operator  +£¬-£¬*£¬/£¬% ,> ,< ,! ,:, <= , >= , == , !=,:)
		else if (is_operator(code[indexOfCode])) {
			token[0] = code[indexOfCode];
			// nagative sign
			if (code[indexOfCode] == '-') {
				int i = 1;
				if (code[indexOfCode+1]=='-'&&code[indexOfCode + 2] == '>') {
						token[i] = code[indexOfCode + 1];
						token[i+1] = code[indexOfCode + 2];
						i++;
						indexOfCode+=3;
						setTokenBuffer("FUNC_START", token);	
				}
				else {
					setTokenBuffer("MINUS", token);
					indexOfCode++;
				}
			}
			else if (code[indexOfCode] == ':') {
				if (code[indexOfCode + 1] = ')') {
					token[1] = code[indexOfCode + 1];
					setTokenBuffer("FUNC_END", token);
					indexOfCode += 2;
				}
				else {
					setTokenBuffer("COL", token);
					indexOfCode++;
				}		
			}
			else if (code[indexOfCode] != '\0') {
				int temp2_state_num;
				if (code[indexOfCode] == '+')
					temp2_state_num = PLUS; //18
				else if (code[indexOfCode] == '-')
					temp2_state_num = MINUS; //19
				else if (code[indexOfCode] == '*')
					temp2_state_num = MULTI; //20
				else if (code[indexOfCode] == '<') {
					if (code[indexOfCode + 1] != '=')
						temp2_state_num = LESS; //24
					else if (code[indexOfCode + 1] == '=')
						temp2_state_num = LESS_OR_EQUAL; //31
				}
				else if (code[indexOfCode] == '>') {
					if (code[indexOfCode + 1] != '=')
						temp2_state_num = GREATER; //23
					else if (code[indexOfCode + 1] == '=')
						temp2_state_num = GREATER_OR_EQUAL; //30
				}
				else if (code[indexOfCode] == '=') {
					if (code[indexOfCode + 1] != '=')
						temp2_state_num = ASSIN; //13
					else if (code[indexOfCode + 1] == '=')
						temp2_state_num = EQUAL_EQUAL; //33
				}
				else if (code[indexOfCode] == '%')
					temp2_state_num = MOD; //22
				else if (code[indexOfCode] == '!') {
					if (code[indexOfCode + 1] != '=')
						temp2_state_num = NOT; //26
					else if (code[indexOfCode + 1] == '=')
						temp2_state_num = UNEQUAL; //32
				}
				switch (temp2_state_num) {
				case PLUS: token[0] = code[indexOfCode]; setTokenBuffer("PLUS", token); indexOfCode++; break;
				case MINUS: token[0] = code[indexOfCode]; setTokenBuffer("MINUS", token); indexOfCode++; break;
				case MULTI: token[0] = code[indexOfCode]; setTokenBuffer("MULTI", token); indexOfCode++; break;
				case LESS: token[0] = code[indexOfCode]; setTokenBuffer("LESS", token); indexOfCode++; break;
				case GREATER: token[0] = code[indexOfCode]; setTokenBuffer("GREATER", token); indexOfCode++; break;
				case ASSIN: token[0] = code[indexOfCode]; setTokenBuffer("ASSIN", token); indexOfCode++; break;
				case MOD: token[0] = code[indexOfCode]; setTokenBuffer("MOD", token); indexOfCode++; break;
				case NOT: token[0] = code[indexOfCode]; setTokenBuffer("NOT", token); indexOfCode++; break;
				case LESS_OR_EQUAL:token[0] = code[indexOfCode]; token[1] = code[indexOfCode + 1];
					setTokenBuffer("LESS_OR_EQUAL", token); indexOfCode += 2; break;
				case GREATER_OR_EQUAL:token[0] = code[indexOfCode]; token[1] = code[indexOfCode + 1];
					setTokenBuffer("GREATER_OR_EQUAL", token); indexOfCode += 2; break;
				case EQUAL_EQUAL:token[0] = code[indexOfCode]; token[1] = code[indexOfCode + 1];
					setTokenBuffer("EQUAL_EQUAL", token); indexOfCode += 2; break;
				case UNEQUAL:token[0] = code[indexOfCode]; token[1] = code[indexOfCode + 1];
					setTokenBuffer("UNEQUAL", token); indexOfCode += 2; break;
				//default:  indexOfCode++; /*printf("Operator token error\n")*/; break;
				}
			}
			else {
				//setTokenBuffer("single-ch operator", token);
				printf("Illegal sign not contained in n-language");
				indexOfCode++;
			}
		}//end else if 

		//integer¡¢strat with a digit(throw an error)¡¢fraction
		else if (is_num(code[indexOfCode])) {
			// is_num true represent digits, false represent string
			bool is_num = true;
			int i = 1;
			token[0] = code[indexOfCode];
		
			//judge multiple digits and fraction
			while (is_letter(code[indexOfCode + 1])) {
				if (is_letter(code[indexOfCode + 1])) {
					is_num = false;
					token[i] = code[indexOfCode + 1];
					i++;
					indexOfCode++;
				}
				setTokenBuffer("ERROR", "!! Wrong NUM type which includes chars.");
			}

			while (is_integer(code[indexOfCode + 1]) || code[indexOfCode + 1] == '|') {
				if (is_integer(code[indexOfCode + 1])) {
					token[i] = code[indexOfCode + 1];
					i++;
					indexOfCode++;
					is_num = true;
				}
				else if (code[indexOfCode + 1] == '|') {
					token[i] = code[indexOfCode + 1];
					i++;
					indexOfCode++;
					is_num = true;
				}
			}
           
			if (is_num == true) {
				setTokenBuffer("NUMBER", token);
				indexOfCode++;
			}
			else {
				printf("Wrong type of NUMBER");
				indexOfCode++;
			}
		}//end else if 
		// annotation
		else if (code[indexOfCode] == '/') {
			token[0] = code[indexOfCode];
			//Single-line comment  "//"
			if (code[indexOfCode + 1] == '/') {
				int i = 1;
				while (code[indexOfCode + 1] != '\n' && code[indexOfCode + 1] != '#') {
					token[i] = code[indexOfCode + 1];
					i++;
					indexOfCode++;
				}
				indexOfCode++;
				setTokenBuffer("ANNOTATION", token);
			}
			// "/*" and with "\n" which ends file 
			else if (code[indexOfCode + 1] == '*'&& code[indexOfCode + 2] == '\n') 
			{
				token[1] = code[indexOfCode + 1];
				setTokenBuffer("ANNOTATION", token);
				indexOfCode+=2;
			}
			//Multiline comment  "/*  */"
			else if (code[indexOfCode + 1] == '*') {
				int i = 1;
				while (code[indexOfCode + 1] != '*'||code[indexOfCode + 2] != '/') {
					token[i] = code[indexOfCode + 1];
					i++;
					indexOfCode++;
				}
				token[i] = code[indexOfCode + 1];
				token[i+1] = code[indexOfCode + 2];
				indexOfCode += 2;
				setTokenBuffer("ANNOTATION", token);
			}			
			else {
				setTokenBuffer("DIV", token);
				indexOfCode++;
			}
		}//end else if
		//keyword and ID
		else if (is_letter(code[indexOfCode]) || code[indexOfCode] == '_') {
			int i = 1;
			token[0] = code[indexOfCode];
			while (code[indexOfCode + 1] != ' ') {
				if (code[indexOfCode + 1] == '\n' || !((is_letter(code[indexOfCode + 1])) || code[indexOfCode + 1] == '_')) {
					break;
				}
				token[i] = code[indexOfCode + 1];
				i++;
				indexOfCode++;
			}
			char temp[128];
			memset(temp, 0, sizeof(temp));
			for (int j = 0; token[j] != '\0'; j++) {
				temp[j] = token[j];
			}
			if (match_keyword(temp)) {
				setTokenBuffer("KEYWORD", token);
			}
			else {
				setTokenBuffer("ID", token);
			}
			indexOfCode++;
		}//end else if 
		// string
		else if (code[indexOfCode] == '"') {
			int i = 0;
			//token[0] = code[indexOfCode+1];
		
			while (code[indexOfCode+1] != '"') {
				token[i] = code[indexOfCode+1];
				i++;
				indexOfCode++;
			}
			indexOfCode+=2;
			//token[i] = code[indexOfCode + 1];
			//indexOfCode += 2;
			setTokenBuffer("STRING", token);
		}//end else if
		else if (code[indexOfCode] == '\n') {
			token[0] = '\n';
			setTokenBuffer("ENTER", token);
			indexOfCode++;
		}
		else {
			token[0] = ' ';
			setTokenBuffer("OTHER", token);
			indexOfCode++;
		}//end else
		memset(token, 0, sizeof(token));
	}
}


int main(int argc, char **argv) {

	char fileName[1000];
	printf("Please input the file name:\n");
	scanf("%s", &fileName);

	//store the code content of the test file
	if (readFile(fileName) == NULL)
	{
		printf("open file error!");
		getchar();//stop window
		system("pause");
		return 0;
	}

	//traverse the code and put sth into buffer and judge
	getToken(m_code);

	n_lexical_print(token_buffer);

	if (m_code) free(m_code);

	getchar();//stop window
	system("pause");
	return 0;
}

