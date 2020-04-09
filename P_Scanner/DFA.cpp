#include <string.h>
#include <stdlib.h>
#include "DFA.h"
/*
*All fundamental structures and functions are assert in "DFA.h"
*Will use and finish in my parser project
*Please read the file "DFA_description.txt"
*/
/************************************
My DFA Description

Fundamental attribute:
	Initialize
	Transaction
	State

Representitive sign:
   "-->"  when encounter

Give initialized state:
"START(Start state)"  "FINAL(Final state)"
"TRAP(Trap state)" "ERROR(Error state)"
"READ(Media State)"

" "(space)--> TRAP(ignore space)

/ --> Path1: -->is_num-->FINAL(add token info:MOD)
		 Path2: continue-->READ-->(1) * -->FINAL(add token info:ANNOT_STRAT)
											  -->(2) / singleline comment--> FINAL(add token info:SINGLE_ANNOT)
			  -->(3) other-->TRAP

* --> Path1: FINAL(MULTI )
		 Path2: continue-->READ-->(1)/ -->FINAL(add token info:ANNOT_END)
			  -->(2) other-->TRAP

+ -->Path1: is_num--> FINAL(add token info:PLUS)
		 Path2: continue-->READ-->(1)= --> FINAL(add token info:)
			  -->(2) other-->TRAP

- --> Path1: is_num -->FINAL(add token info: NVG)
		Path2: continue-->READ -->(1) ¡°-¡± --> ¡°>¡±-->FINAL(add token info:FUNC_START)
											  -->(2) other-->TRAP

< --> Path1: FINAL(add token info:LESS)
		 Path2: continue-->READ-->(1)= -->FINAL(add token info:LESS_OR_EQUAL)
			  -->(2) other-->TRAP
> --> Path1: FINAL(add token info:GREATER)
		 Path2: continue-->READ-->(1)= -->FINAL(add token info:GREATER_OR_EQUAL)
			  -->(2) other-->TRAP
= --> Path1: FINAL(add token info:EQUAL)
		 Path2: continue-->READ-->(1)= -->FINAL(add token info:EQUAL_EQUAL)
			  -->(2) other-->TRAP
! --> Path1: FINAL(add token info:EXCLA)
		 Path2: continue-->READ-->(1)= -->FINAL(add token info:UNEQUAL)
			  -->(2) other-->TRAP

( --> FINAL(add token info:LPAR)
) --> FINAL(add token info:RPAR)
{ --> FINAL(add token info:LBCT)
} --> FINAL(add token info:RBCT)
: --> FINAL(add token info:COM)
; --> FINAL(add token info:SEMI)

" -->Path1: LOOP(is_letter||is_num||is_operator||is_sign)-->"(add token info:STRING)
		 Path2: other-->TRAP

num(is_num) -->Path1:is_num||is_fraction--> FINAL(add token info:NUM)
						  Path2: continue-->READ-->(1) -  -->FINAL(add token info:MINUS) --> is_num||is_fraction--> FINAL(add token info:NUM)
							   -->(2) other-->TRAP

? --> ERROR(throw error information)

***************************************/

