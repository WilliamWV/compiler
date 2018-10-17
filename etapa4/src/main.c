
#include <stdio.h>
#include "../include/parser.tab.h" 
#include "../include/tree.h"

void *arvore = NULL;
void descompila (void *arvore);
void libera (void *arvore);
//função definida em lex.yy.c para desalocar memória usada pelo flex
extern int yylex_destroy  (void); 
extern void exitAndFree2(int exitCode, char *identifier);
extern int nodosCriados;
extern int contaNodosRaiz;
extern int tokensCriados;
extern int returnError;
extern char *identifierError;

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
	if(ret == 1) exitAndFree2(returnError, identifierError);
	return ret;
}
