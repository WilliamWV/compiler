#include "tree.h"
#include "hash.h"
#include "defines.h"
#include "expression.h"

typedef struct argsList{
	FuncArg *arg;
	struct argsList *next;
} Args;

//chamo em parameter
void adicionaArg(Args *newArg);

Args *criaArg(Node *arg);

void adicionaInfoAArg(Node* arg, Args *newArg);


//vou chamar sempre ao fim da definicao de uma funcao
void clearCurrentArgs();

void clearCurrentArgsError();

void addArgsToSymbol(char* symbol, Args *args);

int verifyReturn(struct node* returnExpression);

void saveFunc(char* symbol);

int getCurrentFuncReturnType();

void argsSize();

void updateLocalVarSize(int newVarSize);
