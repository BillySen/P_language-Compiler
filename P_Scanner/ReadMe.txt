---------------------------------------------------------------
!All by myself!  

Author:                   LEI RUIJIA
ID number:             1709853U-I011-0012
Class:                      CN103
Project:                   Lexical Analyser
         
---------------------------------------------------------------
Open project:
operate and run main function  in scanner.c 
Features
1.Detection of errors
  Error1：if operators and signs(two-character) are like  "))”  “<!” these types(without defined at first) 
  Error2:  if fraction is like "3.5" "66.2" with "."(in N language should be like "3|5")
  Error3:  if function isn't begin with"-->" and end with ":)"
  Error4:  illegal input and illegal character
  Error5:  character order error
  Error6:  file name error,file open error
------------------------------------------------------------------
2.Using enum,struct,array to define data type
   TokenType
   Token
   token_namelist
------------------------------------------------------------------
3.Tools used to judge tokens
  bool is_num(char c);
  bool is_integer(char ch);
  bool is_letter(char c);
  bool is_operator(char c);
  bool is_space(char c);
  bool is_sign(char c);
  bool match_keyword(char* c);
  bool match_two_character_operator(char* c);
------------------------------------------------------------------
4.Function in “scanner.c”
  char *readFile(char *fname)
  void getToken(char *code) 
  void n_lexical_print(struct Token *arr)
  void setTokenBuffer(char* type, char* value) 
------------------------------------------------------------------
5.comprehension of data
  token  --store different token content  
  token_buffer  --store struct Token which contains token information 
------------------------------------------------------------------
6.Effective Code
   the use of memset() and malloc function(dynamic memory set)
   release memory in time（memset the memory of token of each while loop）



