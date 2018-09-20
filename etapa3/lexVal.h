#ifndef LEXVAL_H //usado para evitar múltiplas inclusões desse arquivo que também será incluso em outros headers
#define LEXVAL_H 

#include <stdlib.h>
#include <string.h>
//Tipo do token não é um tipo de dado, mas os tipos definidos pelo
//analisador léxico, ou seja:
// 1) Palavra reservada
// 2) Caracteres especiais
// 3) operadores compostos
// 4) Identificadores
// 5) Literais
// Portanto o tipo do token será representado por um inteiro que será um dos valores definidos a seguir.
/*******TIPOS DE TOKENS*******/
#define KEYWORD 0x0
#define SPEC_CHAR 0x1
#define COMP_OPER 0x2
#define IDS 0x3
#define LITERALS 0x4
/*******TIPOS DE LITERAIS*****/
#define INT 0X8
#define FLOAT 0x9
#define CHAR 0xA
#define BOOL 0XB
#define STRING 0XC

/*Usado quando token não é literal no campo correspondente ao tipo do literal*/
#define NONE 0xF


//valores booleanos
#define FALSE 0
#define TRUE 1
//Definição de bool baseado em int para funcionar em versões mais antigas do C
typedef int bool;


union Value{
	int i;
	float f;
	char c;
	bool b;
	char* str; 
};

struct lexval{
	int lineNumber; 
	int tokenType; 
	int literType;
	union Value value; //um dos campos da union acima
};

#endif //LEXVA_H
