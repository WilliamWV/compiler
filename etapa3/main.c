
#include <stdio.h>
#include "parser.tab.h" //arquivo gerado com bison -d parser.y
#include "tree.h"

void *arvore = NULL;
void descompila (void *arvore);
void libera (void *arvore);
//função definida em lex.yy.c para desalocar memória usada pelo flex
extern int yylex_destroy  (void); 

int main (int argc, char **argv)
{
	int ret = yyparse(); 
	descompila (arvore);
	libera(arvore);
	yylex_destroy();
	arvore = NULL;
	return ret;
}
