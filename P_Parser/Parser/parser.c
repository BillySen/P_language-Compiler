/*
Project: parser(based on scanner)
PAN WENXI & LEI RUIJIA
contact us at 1709853ui011001@student.must.edu.mo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"


struct Node *curr_node;
struct TreeNode *treenode;
struct TreeNode *top;
struct TreeNode *curr_par;
struct TreeNode *op_prev_fact;

struct TreeNode *newTreeNode(char *type, char *val, struct TreeNode *parent)
{
	struct TreeNode *tn = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	//new
	strcpy(tn->type, type);
	strcpy(tn->val, val);
	tn->num_child = 0;
	if (parent != NULL)
	{
		setParent(tn, parent);
		//printf("Create new tree node with type %s and value %s of parent %s %s\n", type, val, parent->type, parent->val);
	}
	return tn;
}

void setParent(struct TreeNode *tn, struct TreeNode *parent)
{
	tn->parent = parent;
	parent->num_child++;
	parent->child[parent->num_child-1] = tn;
	tn->i_par_child = parent->num_child-1;
}


void insertOPParent(struct TreeNode *tn, struct TreeNode *new_par)
{
	struct TreeNode *origin_par = tn->parent;

	tn->parent = new_par;
	new_par->parent = origin_par;

	new_par->num_child++;
	new_par->child[new_par->num_child-1] = tn;
	
	origin_par->child[tn->i_par_child] = new_par;
	new_par->i_par_child = tn->i_par_child;

	tn->i_par_child = new_par->num_child-1;
}


int matchType(char *node_type, char *type)
{
	if (strcmp(node_type, type) == 0)
		return 1;
	return 0;
}

int isBinOP(char *op)
{
	if (matchType(op, ADD) || matchType(op, SUB) || 
		matchType(op, MUL) || matchType(op, DIV) || matchType(op, MOD) ||
		matchType(op, EQ) || matchType(op, NEQ) || 
		matchType(op, LT) || matchType(op, LE) || matchType(op, GT) || matchType(op, GE) || 
		matchType(op, AND) || matchType(op, OR))
		return 1;
	return 0;
}


void nextNode()
{
	curr_node = curr_node->next;
	if (matchType(curr_node->t.type, ENTER))
		nextNode();
}


void prevNode()
{
	curr_node = curr_node->prev;
	if (matchType(curr_node->t.type, ENTER))
		prevNode();
}


int getPriority(char *op)
{
	if (matchType(op, NEG) || matchType(op, NOT))
		return 2;
	if (matchType(op, MUL) || matchType(op, DIV) || matchType(op, MOD))
		return 3;
	if (matchType(op, ADD) || matchType(op, SUB))
		return 4;
	if (matchType(op, GT) || matchType(op, GE) || matchType(op, LT) || matchType(op, LE))
		return 6;
	if (matchType(op, EQ) || matchType(op, NEQ))
		return 7;
	if (matchType(op, AND))
		return 11;
	if (matchType(op, OR))
		return 12;

	return -1;
}

int hasPriority(char *prev, char *next)
{
	if (getPriority(prev) <= getPriority(next))
		return 1;
	return 0;
}


struct TreeNode *declare_stmt(struct TreeNode *parent)
{
	struct Node *origin_n = curr_node;
	if (matchType(curr_node->t.type, NUMT) || matchType(curr_node->t.type, VOIDT))
	{
		char val[100];
		strcpy(val, matchType(curr_node->t.type, NUMT) ? TN_NUMT : TN_VOIDT);
		//type
		nextNode();
		if (matchType(curr_node->t.type, PTR))
		{
			//pointer
			strcat(val, " *");
			nextNode();
		}
		if (matchType(curr_node->t.type, ID))
		{
			//ID
			strcat(val, " ");
			strcat(val, curr_node->t.val);
			if (matchType(parent->type, TN_DECLARE))
			{
				//param
				struct TreeNode *tn_p = newTreeNode(TN_PARAM, val, parent);
				nextNode();
				return tn_p;
			}
		}
		else if (matchType(curr_node->t.type, RPAR) && matchType(parent->type, TN_DECLARE))
		{
			struct TreeNode *tn_p = newTreeNode(TN_PARAM, val, parent);
			return tn_p;
		}

		nextNode();
		//variable
		if (matchType(curr_node->t.type, SEMI))
		{
			struct TreeNode *tn_v = newTreeNode(TN_DECLARE, val, parent);
			nextNode();
			return tn_v;
		}
		//array
		else if (matchType(curr_node->t.type, LSQBR))
		{
			nextNode();
			if (matchType(curr_node->t.type, NUM) || matchType(curr_node->t.type, ID))
			{
				strcat(val, " [");
				strcat(val, curr_node->t.val);
				strcat(val, "]");
				struct TreeNode *tn_a = newTreeNode(TN_DECLARE, val, parent);
				nextNode(); // ]
				nextNode();
				return tn_a;
			}
		}

		//function
		else if (matchType(curr_node->t.type, LPAR))
		{
			nextNode();
			if (matchType(curr_node->t.type, RPAR))
			{
				strcat(val, " function");
				struct TreeNode *tn_f = newTreeNode(TN_DECLARE, val, parent);
				curr_par = tn_f;
				nextNode();
				nextNode();
				return tn_f;
			}
			else
			{
				strcat(val, " function with parameters");
				struct TreeNode *tn_f = newTreeNode(TN_DECLARE, val, parent);
				do
				{
					if (declare_stmt(tn_f) == NULL)  //parameters
						nextNode();
				} while (!matchType(curr_node->t.type, RPAR));
				curr_par = tn_f->child[tn_f->num_child-1];
				nextNode();
				nextNode();
				return tn_f;
			}
		}
	}
	curr_node = origin_n;
	return NULL;
}


struct TreeNode *op_exp(struct TreeNode *parent)
{
	struct Node *origin_n = curr_node;
	if (matchType(curr_node->t.type, ID) || matchType(curr_node->t.type, NUM))
	{
		nextNode();

		//ID or NUM
		if (matchType(curr_node->t.type, SEMI) || matchType(curr_node->t.type, RSQBR) || matchType(curr_node->t.type, RPAR))
		{
			struct TreeNode *tn = newTreeNode(matchType(curr_node->prev->t.type, ID) ? TN_ID : TN_CONST, curr_node->prev->t.val, parent);
			if (matchType(curr_par->val, TN_PRIOP) && matchType(curr_node->t.type, RPAR))
				return op_exp(parent);  //end of expr with ()
			nextNode();
			return tn;
		}

		//call function
		if (matchType(curr_node->t.type, LPAR))
		{
			prevNode();
			return expr_stmt(parent);
		}

		//assign
		if (matchType(curr_node->t.type, ASSIGN))
		{
			prevNode();
			return expr_stmt(parent);
		}

		//array
		else if (matchType(curr_node->t.type, LSQBR))
		{
			struct TreeNode *tn_a = newTreeNode(TN_OP, TN_INDEX, NULL);
			struct TreeNode *tn_ch1 = newTreeNode(TN_ID, curr_node->prev->t.val, tn_a);
			nextNode();
			op_exp(tn_a);
			//binary operator after
			if (isBinOP(curr_node->t.type))
			{
				op_prev_fact = tn_a;
				struct TreeNode *tn_o = op_exp(parent);
				return tn_o;
			}
			if (parent != NULL) setParent(tn_a, parent);
			if (matchType(curr_node->t.type, RPAR))
				return op_exp(parent);
			if (matchType(curr_node->t.type, SEMI))
				nextNode();
			return tn_a;
		}
		//binary operator
		else if (isBinOP(curr_node->t.type))
		{
			op_prev_fact = newTreeNode(matchType(curr_node->prev->t.type, ID) ? TN_ID : TN_CONST, curr_node->prev->t.val, NULL);
			struct TreeNode *tn_o = op_exp(parent);
			return tn_o;
		}
	}

	//sub operation with higher p
	else if (matchType(curr_node->t.type, LPAR))
	{
		nextNode();
		struct TreeNode *tn_pr = newTreeNode(TN_OP, TN_PRIOP, NULL);
		tn_pr->parent = parent;
		curr_par = tn_pr;
		struct TreeNode *tn = op_exp(tn_pr);
		return tn_pr;
	}

	else if (matchType(curr_node->t.type, RPAR))
	{
		nextNode();
		op_prev_fact = curr_par;
		curr_par = curr_par->parent;
		op_prev_fact->parent = NULL;
		struct TreeNode *tn = newTreeNode(TN_OP, TN_ENDPRIOP, curr_par);
		op_exp(curr_par);
		return tn;
	}

	//op
	else if (isBinOP(curr_node->t.type))
	{
		struct TreeNode *tn_o;
		struct TreeNode *tn_par;
		if (isBinOP(parent->val) && (hasPriority(parent->val, curr_node->t.type) || parent))
		{
			tn_o = newTreeNode(TN_OP, curr_node->t.type, NULL);
			insertOPParent(parent, tn_o);
			tn_par = tn_o->child[0];
		}
		else
		{
			tn_o = newTreeNode(TN_OP, curr_node->t.type, parent);
			tn_par = tn_o;
		}
		struct TreeNode *tn = op_prev_fact;
		setParent(tn, tn_par);
		nextNode();
		op_exp(tn_o);
		return tn_o;
	}

	//unary operator
	else if (matchType(curr_node->t.type, NOT) || matchType(curr_node->t.type, NEG))
	{
		struct TreeNode *tn_n = newTreeNode(TN_OP, curr_node->t.type, parent);
		nextNode();
		op_exp(tn_n);
		return tn_n;
	}
	curr_node = origin_n;
	return NULL;
}


struct TreeNode *expr_stmt(struct TreeNode *parent)
{
	struct Node *origin_n = curr_node;
	if (matchType(curr_node->t.type, ID))
	{
		char val[100];
		strcpy(val, curr_node->t.val);
		nextNode();
		//call function
		if (matchType(curr_node->t.type, LPAR))
		{
			struct TreeNode *tn_ec = newTreeNode(TN_EXPR, "", parent);
			strcat(val, ", with arguments:");
			struct TreeNode *tn_c = newTreeNode(TN_CALL, val, tn_ec);
			nextNode();
			//args
			while (!matchType(curr_node->t.type, RPAR))
			{
				if (matchType(curr_node->t.type, STRING))
				{
					newTreeNode(TN_STR, curr_node->t.val, tn_c);
				}
				else if (matchType(curr_node->t.type, ID))
				{
					//function as arg
					if (matchType(curr_node->next->t.type, LPAR))
					{
						expr_stmt(tn_c);
					}
					//array
					else if (matchType(curr_node->next->t.type, LSQBR))
					{
						op_exp(tn_c);
					}
					//variable
					else
					{
						newTreeNode(TN_ID, curr_node->t.val, tn_c);
					}
				}
				else if (matchType(curr_node->t.type, NUM))
					newTreeNode(TN_CONST, curr_node->t.val, tn_c);
				nextNode();
			}
			nextNode();
			return tn_ec;
		}
		//assign
		struct TreeNode *tn_va=NULL;
		if (matchType(curr_node->t.type, LSQBR))
		{
			prevNode();
			tn_va = op_exp(NULL);
		}
		else if (!matchType(curr_node->t.type, LSQBR))
		{
			tn_va = newTreeNode(TN_ID, val, NULL);
		}
		if (matchType(curr_node->t.type, ASSIGN))
		{
			struct TreeNode *tn_ec = newTreeNode(TN_EXPR, "", parent);
			struct TreeNode *tn_as = newTreeNode(TN_OP, ASSIGN, tn_ec);
			setParent(tn_va, tn_as);

			nextNode();
			return op_exp(tn_as);
		}
	}
	else if (matchType(curr_node->t.type, IF))
		return if_stmt(parent);
	else if (matchType(curr_node->t.type, WHILE))
		return while_stmt(parent);
	else if (matchType(curr_node->t.type, RETURN))
		return return_stmt(parent);
	else if (matchType(curr_node->t.type, NUMT) || matchType(curr_node->t.type, VOIDT))
		return declare_stmt(parent);
	curr_node = origin_n;
	return NULL;
}


struct TreeNode *if_stmt(struct TreeNode *parent)
{
	struct Node *origin_n = curr_node;
	if (matchType(curr_node->t.type, IF))
	{
		struct TreeNode *tn_i = newTreeNode(TN_IF, "", parent);
		nextNode();
		if (matchType(curr_node->t.type, LPAR))
		{
			nextNode();
			op_exp(tn_i);
			if (compound_stmt(tn_i) == NULL)
				expr_stmt(tn_i);
		}
		nextNode();
		if (else_stmt(tn_i) != NULL)
		{
			strcat(tn_i->type, " with ELSE");
		}
		else
		{
			strcat(tn_i->type, " without ELSE");
		}
		return tn_i;
	}
	curr_node = origin_n;
	return NULL;
}


struct TreeNode *else_stmt(struct TreeNode *parent)
{
	struct Node *origin_n = curr_node;
	if (matchType(curr_node->t.type, ELSE))
	{
		nextNode();
		struct TreeNode *tn_c = compound_stmt(parent);
		if (tn_c == NULL)
			tn_c = expr_stmt(parent);
		return tn_c;
	}
	curr_node = origin_n;
	return NULL;
}


struct TreeNode *while_stmt(struct TreeNode *parent)
{
	struct Node *origin_n = curr_node;
	if (matchType(curr_node->t.type, WHILE))
	{
		struct TreeNode *tn_w = newTreeNode(TN_WHILE, "", parent);
		nextNode();
		if (matchType(curr_node->t.type, LPAR))
		{
			nextNode();
			op_exp(tn_w);
			if (compound_stmt(tn_w) == NULL)
			{
				expr_stmt(tn_w);
			}
			else
				nextNode();
			return tn_w;
		}
	}
	curr_node = origin_n;
	return NULL;
}


struct TreeNode *compound_stmt(struct TreeNode *parent)
{
	struct Node *origin_n = curr_node;
	if (matchType(curr_node->t.type, LCUBR))
	{
		struct TreeNode *tn_c = newTreeNode(TN_COMPOUND, "", parent);
		curr_par = tn_c;
		return tn_c;
	}
	curr_node = origin_n;
	return NULL;
}


struct TreeNode *return_stmt(struct TreeNode *parent)
{
	struct Node *origin_n = curr_node;
	if (matchType(curr_node->t.type, RETURN))
	{
		struct TreeNode *tn_r = newTreeNode(TN_RETURN, "", parent);
		nextNode();
		op_exp(tn_r);
		return tn_r;
	}
	curr_node = origin_n;
	return NULL;
}


struct TreeNode *parser(struct Node *first)
{
	top = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	strcpy(top->type, "top");
	top->num_child = 0;
	curr_node = first->next;
	curr_par = top;
	while (hasNext(curr_node))
	{
		//skip
		if (matchType(curr_node->t.type, ENTER) || matchType(curr_node->t.type, SEMI))
		{
			nextNode();
			continue;
		}
		if (matchType(curr_node->t.type, RCUBR))
		{
			curr_par = curr_par->parent->parent;
			nextNode();
			continue;
		}
		if (matchType(curr_node->t.type, ENDFUNC))
		{
			curr_par = top;
			nextNode();
			continue;
		}
		if (expr_stmt(curr_par) != NULL) continue;
		nextNode();
	}
	return top;
}