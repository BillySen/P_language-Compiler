#include <stdio.h>
#include <string.h>
#include "tools.h"


void printList(int error_count, struct Node *first)
{
	printf("Print Tokens\n\n");
	struct Node *node;
	for (node = first->next; hasNext(node); node = node->next)
	{
		if (strcmp(node->t.val, "") == 0)
			printf("%d %s\n", node->t.line, node->t.type);
		else
			printf("%d %s: %s\n", node->t.line, node->t.type, node->t.val);
	}
	printf("\n");
	if (error_count == 0)
	{
		printf(":) No error is found.\n");
	}
	else
	{
		printf(":( %d errors found.\n", error_count);
		for (node = first->next; hasNext(node); node = node->next)
		{
			if (strcmp(node->t.type, ERROR) == 0)
				printf("Error found at line %d: %s\n", node->t.line, node->t.val);
		}
	}
}
