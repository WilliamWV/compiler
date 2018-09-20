#include "../lexVal.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct lexval* token;
	int kidsNumber;
	struct node **kids; // lista de ponteiros
} Node;


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
		case SPEC_CHAR: printf("%c ", value.c); break;
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
				case STRING: printf("\"%s\" ", value.str);	
			}
			break;
	}		
}

void descompila(void *voidNode){
	Node *n = (Node*) voidNode;
	int i = 0;
	if(n->kidsNumber == 0){ 	// o print vai depender do tipo (PRECISO IMPLEMENTAR ISSO) e só será executado se for um nodo folha
		imprimeToken(n->token->value, n->token->tokenType, n->token->literType);
	}
	else while(i < n->kidsNumber){ // enquanto houver filhos, os explora
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


int main(){

    struct lexval token;
    token.lineNumber = 12;
    token.literType = INT;
    token.tokenType = LITERAL;
    token.value.i = 1;

    struct lexval token2;
    token2.lineNumber = 122;
    token2.literType = INT;
    token2.tokenType = LITERAL;
    token2.value.i = 2;

    struct lexval token3;
    token3.lineNumber = 1222;
    token3.literType = INT;
    token3.tokenType = LITERAL;
    token3.value.i = 3;

    struct lexval token4;
    token4.lineNumber = 12222;
    token4.literType = INT;
    token4.tokenType = LITERAL;
    token4.value.i = 4;

    Node *primeiroNodo = criaNodo(&token);

    printf("Valores do primeiro nodo:\n");
    printf("Line number: %d\n", primeiroNodo->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->token->literType);
    printf("Token type: %d\n", primeiroNodo->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kidsNumber);
    printf("Fim dos valores do primeiro nodo:\n\n");

    printf("Adiciona filho:\n");
    Node *primeiroFilho = criaNodo(&token2);
    adicionaFilho(primeiroNodo, primeiroFilho);
    printf("Valores do primeiro nodo apos adicionar o primeiro filho (devem ser iguais, exceto o nro de filhos):\n");
    printf("Line number: %d\n", primeiroNodo->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->token->literType);
    printf("Token type: %d\n", primeiroNodo->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kidsNumber);
    printf("Valores do primeiro filho:\n");
    printf("Line number: %d\n", primeiroNodo->kids[0]->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->kids[0]->token->literType);
    printf("Token type: %d\n", primeiroNodo->kids[0]->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->kids[0]->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kids[0]->kidsNumber);
    printf("Fim dos valores do primeiro filho\n\n");

    Node *segundoFilho = criaNodo(&token3);
    adicionaFilho(primeiroNodo, segundoFilho);
    printf("Valores do primeiro nodo apos adicionar o segundo filho (devem ser iguais, exceto o nro de filhos):\n");
    printf("Line number: %d\n", primeiroNodo->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->token->literType);
    printf("Token type: %d\n", primeiroNodo->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kidsNumber);
    printf("Valores do primeiro filho apos adicionar o segundo filho (devem ser iguais):\n");
    printf("Line number: %d\n", primeiroNodo->kids[0]->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->kids[0]->token->literType);
    printf("Token type: %d\n", primeiroNodo->kids[0]->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->kids[0]->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kids[0]->kidsNumber);
    printf("Valores do segundo filho:\n");
    printf("Line number: %d\n", primeiroNodo->kids[1]->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->kids[1]->token->literType);
    printf("Token type: %d\n", primeiroNodo->kids[1]->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->kids[1]->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kids[1]->kidsNumber);
    printf("Fim dos valores do segundo filho\n\n");

    Node *filhoDoSegundoFilho = criaNodo(&token4);
    adicionaFilho(segundoFilho, filhoDoSegundoFilho);
    printf("Valores do primeiro nodo apos adicionar filho ao segundo filho (devem ser iguais, exceto o nro de filhos):\n");
    printf("Line number: %d\n", primeiroNodo->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->token->literType);
    printf("Token type: %d\n", primeiroNodo->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kidsNumber);
    printf("Valores do primeiro filho apos adicionar filho ao segundo filho (devem ser iguais):\n");
    printf("Line number: %d\n", primeiroNodo->kids[0]->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->kids[0]->token->literType);
    printf("Token type: %d\n", primeiroNodo->kids[0]->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->kids[0]->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kids[0]->kidsNumber);
    printf("Valores do segundo filho apos dar a ele um filho (devem ser iguais, exceto o nro de filhos):\n");
    printf("Line number: %d\n", primeiroNodo->kids[1]->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->kids[1]->token->literType);
    printf("Token type: %d\n", primeiroNodo->kids[1]->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->kids[1]->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kids[1]->kidsNumber);
    printf("Valores do filho do segundo filho:\n");
    printf("Line number: %d\n", primeiroNodo->kids[1]->kids[0]->token->lineNumber);
    printf("Literal type: %d\n", primeiroNodo->kids[1]->kids[0]->token->literType);
    printf("Token type: %d\n", primeiroNodo->kids[1]->kids[0]->token->tokenType);
    printf("Token value: %d\n", primeiroNodo->kids[1]->kids[0]->token->value.i);
    printf("Number of kids: %d\n", primeiroNodo->kids[1]->kids[0]->kidsNumber);
    printf("Fim dos valores do filho do segundo filho\n\n");

    descompila(primeiroNodo); // deve mostrar os valores de primeiroFilho (2) e filhoDoSegundoFilho (4), já que são os únicos nodos-folha
    printf("\n");
    libera(primeiroNodo);

    return 0;
}
