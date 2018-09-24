#ifndef TREE_H
#define TREE_H

#include "lexVal.h"

typedef struct node{
	struct lexval* token;
	int kidsNumber;
	struct node **kids; // lista de ponteiros
} Node;

Node* criaNodo(struct lexval* token);

void adicionaFilho(Node *pai, Node *kid);

void imprimeToken(union Value value, int tokenType, int literType);

void descompila(void *voidNode);

void libera(void *voidNode);


#endif /* TREE_H */
