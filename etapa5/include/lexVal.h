#ifndef LEXVAL_H //usado para evitar múltiplas inclusões desse arquivo que também será incluso em outros headers
#define LEXVAL_H 

#include <stdlib.h>
#include <string.h>
#include "defines.h"

//Definição de bool baseado em int para funcionar em versões mais antigas do C
typedef int bool;

//Definição da union que representa o valor dos tokens
union Value{
	int i;
	float f;
	char c;
	bool b;
	char* str; 
};
// Estrutura usada para associar valor ao token
struct lexval{
	int tokenInAst;
	int lineNumber; 
	int tokenType; 
	int literType;
	union Value value; //um dos campos da union acima
};

#endif //LEXVAL_H
