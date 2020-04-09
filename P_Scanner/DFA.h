#ifndef  _DFA_H
#define  _DFA_H
#include "token.h"

typedef struct
{
	int *condition; //a bool-returning and char-taking function pointer which is used to test whether this transition is to be taken.
	int target_StateID;
} Transition;


typedef struct
{
	int ID; //unique ID associated with every state
	int has_action; //indicates whether any action should be taken when DFA is in this state
	int numOfTransitions; //number of outgoing transitions excluding the default (other) transition
	char actionName[256]; //the string based on which action is taken
	Transition transitions[100]; //list of outgoing transitions
	int defaultToStateID; //the default (other) transition. This is taken when no other transition is possible
} State;

typedef struct
{
	int startStateID;
	int currentStateID;
	int numOfStates;//number of states
	State* states[];
} DFA;


DFA* createDFA();//START,FINAL,TRAP,ERROR 
void reset(DFA* dfa); //makes the dfa prepare for consumption. sets "this" state to start state.
void makeNextTransition(DFA* dfa, char c);
void addState(DFA* pDFA, State* newState);
State* dfa_createState(int hasAction, char* actionName);
void addTransition(DFA* dfa, int fromStateID, int(*condition)(char), int toStateID);


//analyse
void analyseToken(Token *token, DFA *dfa);



#endif // ! _DFA_H
