#include "tree.h"
#include "hash.h"

typedef struct operandsList{
	char *identifier;
	int type;
	struct operandsList *next;
} Operands;

void adicionaOperando(Operands *newOperand);

Operands *criaOperando(Node *ast);

void parseOperands(Node *ast);

void printCurrentOperands();

/*
//chamo essa funcao pra expressoes aritmeticas ou booleanas; se houver char ou string retorno ERR_WRONG_TYPE
int wrongType(Operands *operands);

//deve ser chamada depois da funcao acima, vai retornar ou o tipo da coercao e marcar no nodo correspondente, ou o erro encontrado (ERR_STRING_TO_X, ERR_CHAR_TO_X, ERR_USER_TO_X)
int coercion(Operands *operands, int expectedType, Node *ast);

void clearCurrentOperands();*/
