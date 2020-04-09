#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct Node *emptyNode()
{
	struct Node *n = (struct Node*)malloc(sizeof(struct Node));
	n->prev = NULL;
	n->next = NULL;
	return n;
}


struct Node *newNode(struct Node *prev, struct Token t)
{
	struct Node *n = (struct Node*)malloc(sizeof(struct Node));
	n->prev = prev;
	prev->next = n;
	n->t = t;
	return n;
}


int hasNext(struct Node *node)
{
	if (node->next != NULL)
		return 1;
	return 0;
}