#ifndef _TOKEN_H
#define _TOKEN_H
#include <string.h>

//the order of token type corresponds with tokentype_namelist
typedef enum TokenType {
	ID ,			  //0
	NUMBER,          //1
	STRING,       //2
	VOID,		  //3
	IF,		      //4
	WHILE,        //5
	FOR,          //6
	ELSE,         //7
	RETURN,       //8 
	LPAR,         //9  (
	RPAR,         //10 )
	LBCT,         //11 {
	RBCT,         //12 }
	ASSIN,        //13 =
	SEMI,         //14 :
	COL,          //15 :
	COM,          //16 ,
	NVG,          //17 -
	PLUS,         //18 +
	MINUS,        //19 -
	MULTI,        //20 *
	DIV,          //21 /
	MOD,          //22 %
	GREATER,      //23 >
	LESS,         //24 <
	QUES,         //25 ?
	NOT,          //26 !
	ANNOT_START,     //27 /*
	ANNOT_END,       //28 */
	ANNOTATION,      //29 //
	GREATER_OR_EQUAL,//30 >=
	LESS_OR_EQUAL,   //31 <=
	UNEQUAL,         //32 !=
	EQUAL_EQUAL,     //33 ==
	FUNC_START,      //34 -->
	FUNC_END,        //35 :)
	ENTER,           //36 '\n'
	NVG_NUM,         //37 nagative num type
	KEYWORD,         //38
	OTHER,           //39
	TRAP,            //40
	ERROR,           //41
	NUM              //42 show the keyword NUM
}TokenType;

//Token struct: contains token type name and value 
typedef struct Token {
	TokenType type;
	char value[100];
} Token;

extern int indexOfToken;
extern Token token_buffer[256];

extern char *keyWord[7];
extern char *two_character_operator[4];
extern char *tokentype_namelist[];

//Token Functions
void intializeToken(Token *token);
void setTokenBuffer(char* type, char* value);
//void addCharToken(Token *token, char c);

/*
Token make_token(){
	char *str = (char*)malloc(sizeof(str));
	Token *result_info;
	result_info->value = str;
	return *result_info;
}
*/

#endif  //!_TOKEN_H