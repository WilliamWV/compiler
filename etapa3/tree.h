#include "lexVal.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct lexval* token;
	int kidsNumber;
	struct node **kids; // lista de ponteiros
} Node;

//****************************************************************************************************************************
//****************************************************************************************************************************
//PRECISO CRIAR UMA FUNÇÃO PARA PASSAR O PONTEIRO DA RAIZ DA ARVORE PARA A VARIÁVEL EXTERNA arvore
//****************************************************************************************************************************
//****************************************************************************************************************************

Node* criaNodo(struct lexval* token){
	Node *node = malloc(sizeof(Node));
	node->token = token;
	node->kidsNumber = 0;
	node->kids = (Node**)malloc(sizeof(Node**)); // aloca espaço para o primeiro ponteiro para um ponteiro de Node

	return node;
}

void adicionaFilho(Node *pai, Node *kid){
	pai->kidsNumber = pai->kidsNumber + 1;
	pai->kids = (Node**)realloc(pai->kids, pai->kidsNumber * sizeof(Node**)); // aloca espaço para mais um ponteiro para um ponteiro de Node
	pai->kids[pai->kidsNumber - 1] = kid; // acessa o ponteiro recém alocado e guarda nele um ponteiro de Node
}

void descompila(Node *n){
	int i = 0;
	if(n->kidsNumber == 0){ 	// o print vai depender do tipo (PRECISO IMPLEMENTAR ISSO) e só será executado se for um nodo folha
		printf("%d\n", n->token->value.i);
	}
	else while(i < n->kidsNumber){ // enquanto houver filhos, os explora
			descompila(n->kids[i]);
			i++;
		}
}

void libera(Node *n){ //recebe ponteiro de Node
	int i = 0; // talvez dê problema por eu tentar liberar sempre o primeiro ponteiro
	while(i < n->kidsNumber){ // enquanto houver filhos, os explora
		libera(n->kids[i]);
		i++;
	}
	free(n);
}

//Passando um void como valor para poder determinar qual campo do union que deve ser assinalado
//por meio do tipo presente em literType
struct lexval* createLexVal(int line, int tkType, int ltType, void* val){
	struct lexval* temp = (struct lexval*) malloc(sizeof(struct lexval));
	temp->lineNumber = line;
	temp->tokenType = tkType;
	temp->literType = ltType;
	switch (ltType){
		case INT: temp->value.i = *( (int*) val ); break;
		case FLOAT: temp->value.f = *( (float*) val); break;
		case CHAR: temp->value.c = *( (char*) val); break;
		case BOOL: temp->value.b = *( (bool*) val); break;
		case STRING:
		case NONE: temp->value.str = strdup( (char*) val);  	
	}
	return temp;
}

