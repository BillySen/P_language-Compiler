Project: Parser
Date: 2019/01/05
-------------------------------------------------------------------
Member：
PAN WENXI      1709853X-I011-0010     //Write code and provide ideas and correct errors
LEI RUIJIA         1709853U-I011-0012    //Write code and provide ideas and correct errors
WANG HAOXU  1709853E-I011-0032    //Correct errors
-----------------------------------------------------------------------------------------------------
Files introduction:
automata.h, list.h, parser.h, token.h, tools.h, 
automata.c, list.c, main.c, parser.c, print_parser.c, scanner.c, tools.c
-----------------------------------------------------------------------------------------------------
Explain for some functions or files: 
	A. automata:
	This file have functions which mainly determine the main token types in this language
               Like, skip space, find Enter, operators, get the types of brackets, judge the key words, get ID, Num, String and so on.
	For example, use many if&else to see whether it is a keyword or other token types, if ture, for keywords only, return 2

	B. list：
	Two struct types are recorded as lists, and the layout of the left and right subtree 
	relationships for each List will be completed in list.c.
	Define emptyNode and newNode and use malloc to open memory space.
	hasNext() to judge if current node has next node.

	C. tools：
	Define the function: printList
	Tools calls list file, and prints the type of each token based on the type which has been defined.
              
	D.print_parser.c:
	Accroding to the trees which are generated and print the information of them.
	And the function is directly called in main.c.

	F.parser:
	Has basic data type of Node and TreeNode and corresponding previous node and next node.
	Have judegement to see if a newtreenode have a parent or child, if no, setParent for node.
	With function to match node type, judge whether is a operator.
	Have priority setting function for some declared types.
               Declaration of statement which has type pointer, ID, parameter, variable, array, function,
               declaration of operator expression, like ID/NUM/call function/unary and binary operator and so on.
	Individual treenode for if/else/return/while/parser.	
-----------------------------------------------------------------------------------------------------
Features:
	Correct and corresponding annotations and comments.
	For node and other data type definition, use malloc to open relative memory space and clear memory in time for code efficiency.
	Complete definition structure of Tree,TreeNode and ChildNode and so on.
               Clear program code structure.
	Correct and proper error information.
               Have function to create or set  or insert for some Node/Parent/Priority/Expression/.. information.
-----------------------------------------------------------------------------------------------------
Some running example is at the file "Run_example"，you can have a look!
-----------------------------------------------------------------------------------------------------
How to test(operation):
Open the main.c and run in IDE, then input file name:
Recommend using "fact.n/arrayMaxMean.n/selection_sort.n" to test.
If there is something wrong please contact us or removes the nesting of multiple parentheses in a function definition.