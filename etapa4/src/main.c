
#include <stdio.h>
#include "../include/parser.tab.h" 
#include "../include/tree.h"
#include "../include/expression.h"
#include "../include/functionArgs.h"
#include "../include/userTypeField.h"
#include "../include/hash.h"

void *arvore = NULL;
void descompila (void *arvore);
void libera (void *arvore);
//função definida em lex.yy.c para desalocar memória usada pelo flex
extern int yylex_destroy  (void); 
extern int get_line_number(void);
extern int nodosCriados;
extern int contaNodosRaiz;
extern int tokensCriados;

extern int returnError;
extern char *identifierError;
extern Node *nodeNotAdded;

void exitAndFree(int exitCode, char *identifier, Node *danglingNode){

	int lineNumber = get_line_number();		
	
	switch(exitCode)
	{
		case ERR_UNDECLARED: printf("Undeclared identifier on line %d.\n", get_line_number()); break;
		case ERR_DECLARED:  printf("Redeclaration on line %d.\n", get_line_number()); break;
		case ERR_VARIABLE: printf("Identifier not used as variable on line %d.\n", get_line_number());  break;
		case ERR_VECTOR: printf("Identifier not used as vector on line %d.\n", get_line_number());  break;
		case ERR_WRONG_TYPE: printf("Char, string or user type used in expression on line %d.\n", get_line_number()); break;
		case ERR_STRING_TO_X: printf("Tried to assign string to a non-string or non-string to a string on line %d.\n", get_line_number()); break;
		case ERR_CHAR_TO_X: printf("Tried to assign char to a non-char or non-char to char on line %d.\n", get_line_number()); break;
		case ERR_USER_TO_X: printf("Tried to assign a user type to another type or another type to a user type on line %d.\n", get_line_number()); break;
		case ERR_MISSING_ARGS: printf("Missing arguments on line %d.\n", get_line_number()); break;
		case ERR_EXCESS_ARGS: printf("Excessive arguments on line %d.\n", get_line_number()); break;
		case ERR_WRONG_TYPE_ARGS: printf("Wrong argument type on line %d.\n", get_line_number()); break;
		case ERR_WRONG_PAR_INPUT: printf("Non-identifier used as input on line %d.\n", get_line_number()); break;
		case ERR_WRONG_PAR_OUTPUT: printf("Non-expression and non-string literal used as output on line %d.\n", get_line_number()); break;
		case ERR_WRONG_PAR_RETURN: printf("Expression type does not match return type on line %d.\n", get_line_number()); break;
		case 1: break;
		default: printf("Unknown error.\n"); break;
	}

	clearCurrentFields();
	clearCurrentArgsError();	

	liberaTodasTabelas();	
	
	libera(danglingNode);
	
	exit(exitCode);
}

int main (int argc, char **argv)
{
	int ret = yyparse(); 
	descompila (arvore);

	#if DEBUG == TRUE
		contaNodosNaRaiz(arvore);
		printf("\nTokens criados: %d\nNodos na raiz: %d\nNodos criados: %d\n", tokensCriados, contaNodosRaiz, nodosCriados);
	#endif

	libera(arvore);
	yylex_destroy();
	arvore = NULL;
	if(ret == 1) exitAndFree(returnError, identifierError, nodeNotAdded);
	return ret;
}
