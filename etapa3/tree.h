#ifndef TREE_H
#define TREE_H

typedef struct node{
	struct lexval* token;
	int kidsNumber;
	struct node **kids; // lista de ponteiros
} Node;

Node* criaNodo(struct lexval* token);

void adicionaFilho(Node *pai, Node *kid);

void descompila(void *voidNode);

void libera(void *voidNode);


#endif /* TREE_H */
