#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int liberaDanglingUsed = FALSE;
extern Node *danglingNodes;
extern int contaCriacaoDeNodos;

Node* criaNodo(struct lexval* token){
	if(token != NULL)
		token->tokenInAst = TRUE;
	Node *node = malloc(sizeof(Node));
	node->token = token;
	node->kidsNumber = 0;
	node->kids = (Node**)malloc(sizeof(Node**)); // aloca espaço para o primeiro ponteiro para um ponteiro de Node

	return node;
}

Node* criaNodoDangling(struct lexval* token){
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
	switch(tokenType) // impressao especifica para cada token
	{
		case KEYWORD: printf("%s ", value.str); break;
		case SPEC_CHAR: 
			switch(value.c) // deixa a descompila um pouco mais formatada
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
	if(n!=NULL){
		if(n->token != NULL) // token eh um ponteiro NULL quando foi criado a partir de uma regra empty; nesse caso nao deve ser impresso
			imprimeToken(n->token->value, n->token->tokenType, n->token->literType); // primeiro imprimimos pai, depois os filhos na ordem em que foram adicionados
		while(i < n->kidsNumber){ // enquanto houver filhos, os explora e os imprime
			descompila(n->kids[i]);
			i++;
		}
	}
}

void libera(void *voidNode){ //recebe ponteiro de Node como ponteiro void devido a especificacao, depois faz o cast
	if(liberaDanglingUsed == FALSE){ // desaloca danglingNodes e seus possiveis tokens nunca utilizados no parser.
		liberaDanglingUsed = TRUE;
		liberaDanglingScanner(danglingNodes);
	}
	Node *n = (Node*) voidNode;
	int i = 0;
	if(n!=NULL){
		while(i < n->kidsNumber){ // enquanto houver filhos, os explora...
			libera(n->kids[i]); // ... e os libera
			i++;
		}
		free(n->kids);	// libera ponteiro para ponteiro de nodos (os ponteiros de nodos foram liberados no while acima, por meio de free(n))
		if(n->token != NULL)
			if(n->token->tokenType == KEYWORD || n->token->tokenType == COMP_OPER || n->token->tokenType == IDS || (n->token->tokenType == LITERAL && n->token->literType == STRING))
			free(n->token->value.str);
		free(n->token);
		free(n);	// libera o nodo
	}
}

// Libera nodos criados no scanner. Tais nodos sao criados para armazenar todos os tokens criados. Isso eh necessario pois o scanner pode alocar tokens que nunca serao postos em um nodo pelo parser (pode-se verificar com a entrada "zor z@r;" de wrongEntry2). Tais tokens terao tokenInAst == FALSE, e serao desalocados nessa funcao.
void liberaDanglingScanner(Node *n){ //recebe ponteiro de Node como ponteiro void devido a especificacao, depois faz o cast
	int i = 0;
	if(n!=NULL){
		while(i < n->kidsNumber){ // enquanto houver filhos, os explora...
			liberaDanglingScanner(n->kids[i]); // ... e os libera
			i++;
		}
		free(n->kids);	// libera ponteiro para ponteiro de nodos (os ponteiros de nodos foram liberados no while acima, por meio de free(n))
		
		if(n->token != NULL){
			if(n->token->tokenInAst == FALSE){
				if(n->token->tokenType == KEYWORD || n->token->tokenType == COMP_OPER || n->token->tokenType == IDS || (n->token->tokenType == LITERAL && n->token->literType == STRING))
					free(n->token->value.str);
				free(n->token);				
			}
		}
		free(n);
	}
}


// Libera nodos "soltos" criados no parser quando ha erro; esses nodos terao tokenInAst == TRUE, ja que sao criados com criaNodo(). Funcao eh chamada pelo destrutor de <ast>.
void liberaDanglingParser(Node *n){ //recebe ponteiro de Node como ponteiro void devido a especificacao, depois faz o cast
	int i = 0;
	if(n!=NULL){
		nullifyPointer(n->token, danglingNodes);
		while(i < n->kidsNumber){ // enquanto houver filhos, os explora...
			liberaDanglingParser(n->kids[i]); // ... e os libera
			i++;
		}
		free(n->kids);	// libera ponteiro para ponteiro de nodos (os ponteiros de nodos foram liberados no while acima, por meio de free(n))
		
		if(n->token != NULL){
				if(n->token->tokenType == KEYWORD || n->token->tokenType == COMP_OPER || n->token->tokenType == IDS || (n->token->tokenType == LITERAL && n->token->literType == STRING))
					free(n->token->value.str);
				free(n->token);	
		}
		free(n);
	}
}

// Quando o parser vai liberar um nodo+token, eh necessario checar se o ponteiro para o token que vai ser desalocado esta em danglingNodes. Se estiver, devemos fazer com que o ponteiro, em danglingNodes, para tal token aponte para NULL. Isso se faz necessario pois, apesar de em liberaDanglingScanner(Node *n) apenas os tokens com tokenInAst == FALSE serem desalocados, acabamos percorrendo todos os tokens criados pelo scanner; logo, se nao apontarmos o ponteiro para NULL, tentaremos acessar um ponteiro que ja foi liberado.
void nullifyPointer(struct lexval* token, Node *n){
	int i = 0;
	if(n!=NULL){
		while(i < n->kidsNumber){ // enquanto houver filhos, os explora...
				nullifyPointer(token, n->kids[i]); // ... e os libera
				i++;
		}
		if(n->token == token)
			n->token = NULL;
	}
}
