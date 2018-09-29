#ifndef TREE_H
#define TREE_H

#include "lexVal.h"

typedef struct node{
	struct lexval* token;
	int kidsNumber;
	struct node **kids; // lista de ponteiros
} Node;

Node* criaNodo(struct lexval* token);

Node* criaNodoDangling(struct lexval* token);

void adicionaFilho(Node *pai, Node *kid);

void imprimeToken(union Value value, int tokenType, int literType);

void descompila(void *voidNode);

void libera(void *voidNode);

void liberaDanglingScanner(Node *n);

void liberaDanglingParser(Node *n);

void nullifyPointer(struct lexval* token, Node *n);

void contaNodosNaRaiz(Node *n);


#endif /* TREE_H */
