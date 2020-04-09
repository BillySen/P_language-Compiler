/*
Project: parser(based on scanner)
PAN WENXI & LEIRUIJIA
contact us at 1709853ui011001@student.must.edu.mo
*/
#include <stdio.h>
#include <string.h>
#include "parser.h"


void print_tree(struct TreeNode *tn, int indent)
{
	//skip
	if (matchType(tn->val, TN_PRIOP) || matchType(tn->val, TN_ENDPRIOP))
	{
		for (int i=0; i<tn->num_child; ++i)
		{
			print_tree(tn->child[i], indent);
		}
	}
	else
	{
		//indent
		printf("%d", indent);
		for (int i=0; i<indent; ++i)
		{
			printf("  ");
		}

		printf("%s: %s\n", tn->type, tn->val);
		for (int i=0; i<tn->num_child; ++i)
		{
			print_tree(tn->child[i], indent+1);
		}
	}
}
