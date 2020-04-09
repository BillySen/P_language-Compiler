//Pan Wenxi, 0010

#ifndef LIST_H
#define LIST_H


#include "token.h"


struct Node
{
	struct Node *prev;
	struct Node *next;
	struct Token t;
};


struct Node *newNode(struct Node *prev, struct Token t);
struct Node *emptyNode();
int hasNext(struct Node *node);


#endif