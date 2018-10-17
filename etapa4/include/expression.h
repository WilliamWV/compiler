#include "tree.h"
#include "hash.h"
#include "defines.h"

typedef struct operandsList{
	char *identifier;
	int type;
	struct operandsList *next;
} Operands;

void adicionaOperando(Operands *newOperand);

Operands *criaOperando(Node *ast);

void parseOperands(Node *ast);

void printCurrentOperands();

void clearCurrentOperands();


//chamo essa funcao pra expressoes aritmeticas ou booleanas; se houver char ou string retorno ERR_WRONG_TYPE
int wrongTypeInExpression();

//deve ser chamada depois da funcao acima, vai retornar ou o tipo da coercao e marcar no nodo correspondente, ou o erro encontrado (ERR_STRING_TO_X, ERR_CHAR_TO_X, ERR_USER_TO_X)
int coercion(int expectedType, Node *expressionNode);

int typeInference();

int verifyReturn(struct node* returnExpression);

void saveFunc(char* symbol);
