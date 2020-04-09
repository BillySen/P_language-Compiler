/*
Project: parser(based on scanner)
PAN WENXI   1709853X-I011-0010     
LEI RUIJIA  1709853U-I011-0012  
WANG HAOXU  1709853E-I011-0032   
contact us at 1709853ui011001@student.must.edu.mo
*/
#include <stdio.h>
#include <string.h>
#include "scanner/tools.h"
#include "scanner/automata.h"
#include "parser.h"

int main()

{
	printf("Filename: ");
	char fn[20];
	scanf("%s", &fn);
	fp = fopen(fn, "r");

	printf("N Compilation: %s\n\n", fn);
	//scanner 
	struct Node *first = scanner();
	if (strcmp(first->t.type, ERROR) == 0)
	{
		return 0;
	}
	printf("\nLexical analysis is done. Hit \"Enter\" to continue.\n\n");
	getchar();
	getchar();
	//parser
	struct TreeNode *top = parser(first);
	printf("\n\nParse End\n\n");
	for (int i=0; i<top->num_child; ++i)
		print_tree(top->child[i], 1);
	return 0;
}
