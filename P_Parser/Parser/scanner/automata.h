#include "list.h"
#include "token.h"


FILE *fp;
struct Node *setToken(int line, char *type, char *val, struct Node *node);
void skipSpace();
int isSemi(char ch);
int isComma(char ch);
int isEnter(char ch);
int getBracket(char ch);
int getKey(char ch);
int getOp(char ch, struct Node *node);
char *getString(char ch);
char *getNum(char ch, struct Node *node);
char *getId(char ch);
int isComment(char ch);
int isStartFunc(char ch);
int isEndFunc(char ch);
