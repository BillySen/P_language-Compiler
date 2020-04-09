#ifndef PARSER_H
#define PARSER_H


#include "scanner/list.h"

#define TN_DECLARE "Declare"
#define TN_PARAM "Parameter"
#define TN_NUMT "num"
#define TN_VOIDT "void"
#define TN_EXPR "Expression stmt"
#define TN_CALL "Call function"
#define TN_STR "String"
#define TN_ID "ID"
#define TN_CONST "Const"
#define TN_OP "Operator"
#define TN_PRIOP "Expr with priority"
#define TN_ENDPRIOP "End of expr"
#define TN_INDEX "[] index operator"
#define TN_IF "if stmt"
#define TN_ELSE "else stmt"
#define TN_WHILE "while stmt"
#define TN_COMPOUND "Compound Stmt"
#define TN_RETURN "Return"


struct TreeNode
{
	char type[30];
	char val[100];
	int num_child;
	int i_par_child;
	struct TreeNode *child[100];
	struct TreeNode *parent;
	struct TreeNode *lsibling;
	struct TreeNode *rsibling;
};

struct TreeNode *if_stmt(struct TreeNode *parent);
struct TreeNode *else_stmt(struct TreeNode *parent);
struct TreeNode *while_stmt(struct TreeNode *parent);
struct TreeNode *compound_stmt(struct TreeNode *parent);
struct TreeNode *return_stmt(struct TreeNode *parent);
struct TreeNode *expr_stmt(struct TreeNode *parent);
struct TreeNode *declare_stmt(struct TreeNode *parent);
struct TreeNode *op_exp(struct TreeNode *parent);


void genTree();

int matchType(char *node_type, char *type);
struct TreeNode *newTreeNode(char *type, char *val, struct TreeNode *parent);
void setParent(struct TreeNode *tn, struct TreeNode *parent);
void insertOPParent(struct TreeNode *tn, struct TreeNode *new_par);

struct TreeNode *parser(struct Node *first);
void print_tree(struct TreeNode *tn, int indent);
#endif