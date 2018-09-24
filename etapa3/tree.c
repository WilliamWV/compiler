#include "lexVal.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

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

void imprimeToken(union Value value, int tokenType, int literType){
	switch(tokenType)
	{
		case KEYWORD: printf("%s ", value.str); break;
		case SPEC_CHAR: 
			switch(value.c)
			{
				case ';': printf("%c\n", value.c); break;
				case '{': printf("%c\n", value.c); break;

				case '}': printf("%c", value.c); break;
				default: printf("%c ", value.c); break;
			}
			break;
		case COMP_OPER: printf("%s ", value.str); break;
		case IDS: printf("%s ", value.str); break;
		case LITERAL:
			switch(literType)
			{
				case INT: printf("%d ", value.i); break;
				case FLOAT: printf("%f ", value.f); break;
				case CHAR: printf("\'%c\' ", value.c); break;
				case BOOL: 
					if(value.b == TRUE)
						printf("true ");
					else printf("false ");
					break;
				case STRING: printf("%s ", value.str); break;		
			}
			break;
	}		
}

void descompila(void *voidNode){
	Node *n = (Node*) voidNode;
	int i = 0;
	if(n->token != NULL)
		imprimeToken(n->token->value, n->token->tokenType, n->token->literType);
	while(i < n->kidsNumber){ // enquanto houver filhos, os explora
			descompila(n->kids[i]);
			i++;
	}
}

void libera(void *voidNode){ //recebe ponteiro de Node
	Node *n = (Node*) voidNode;
	int i = 0; // talvez dê problema por eu tentar liberar sempre o primeiro ponteiro
	while(i < n->kidsNumber){ // enquanto houver filhos, os explora
		libera(n->kids[i]);
		i++;
	}
	free(n->kids);
	free(n);
}
