#ifndef EXPRESSIONH
#define EXPRESSIONH "xd"
#include "tree.h"
#include "hash.h"
#include "defines.h"

typedef struct operandsList{
	char *identifier;
	int type; // tipo apos coercao
	struct operandsList *next;
	struct operandsList *previous;
	char character;
	int originalType;
} Operands;

int unaryArithCoercion(Node *ss, Node *s2);
int unaryLogicCoercion(Node *ss, Node *s2);
int bitwiseCoercion(Node *ss, Node *s1, Node *s3);
int arithmeticCoercion(Node *ss, Node *s1, Node *s3);
int arithRelationalCoercion(Node *ss, Node *s1, Node *s3);
int relationalCoercion(Node *ss, Node *s1, Node *s3);
int logicCoercion(Node *ss, Node *s1, Node *s3);
void printExpression(Node *expression);
void printOperand(Node *operand);
void printOperandsWithoutInfo(Node *expression);
void printAllOperands(Node *expression);

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

#endif
