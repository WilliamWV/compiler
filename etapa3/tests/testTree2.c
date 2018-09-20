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
    token2.literType = STRING;
    token2.tokenType = LITERAL;
    token2.value.str = "string char float bool int keyword specchar compoperator identifier";

    struct lexval token3;
    token3.lineNumber = 1222;
    token3.literType = CHAR;
    token3.tokenType = LITERAL;
    token3.value.c = 'z';

    struct lexval token4;
    token4.lineNumber = 12222;
    token4.literType = CHAR;
    token4.tokenType = LITERAL;
    token4.value.c = 'f';

    struct lexval token5;
    token5.lineNumber = 122222;
    token5.literType = FLOAT;
    token5.tokenType = LITERAL;
    token5.value.f = -12.07;

    struct lexval token6;
    token6.lineNumber = 1222222;
    token6.literType = BOOL;
    token6.tokenType = LITERAL;
    token6.value.b = 1;

    struct lexval token7;
    token7.lineNumber = 12222222;
    token7.literType = INT;
    token7.tokenType = LITERAL;
    token7.value.i = 17;


    struct lexval token8;
    token8.lineNumber = 0;
    token8.literType = NONE;
    token8.tokenType = KEYWORD;
    token8.value.str = "private";

    struct lexval token9;
    token9.lineNumber = 0;
    token9.literType = NONE;
    token9.tokenType = SPEC_CHAR;
    token9.value.c = ';';

    struct lexval token10;
    token10.lineNumber = 0;
    token10.literType = NONE;
    token10.tokenType = COMP_OPER;
    token10.value.str = ">>";

    struct lexval token11;
    token11.lineNumber = 0;
    token11.literType = NONE;
    token11.tokenType = IDS;
    token11.value.str = "identificador";

    Node *primeiroNodo = criaNodo(&token);

    Node *primeiroFilho = criaNodo(&token2);
    adicionaFilho(primeiroNodo, primeiroFilho);

    Node *segundoFilho = criaNodo(&token3);
    adicionaFilho(primeiroNodo, segundoFilho);

    Node *filhoDoSegundoFilho = criaNodo(&token4);
    adicionaFilho(segundoFilho, filhoDoSegundoFilho);

    Node *terceiroFilho = criaNodo(&token5);
    Node *quartoFilho = criaNodo(&token6);
    Node *quintoFilho = criaNodo(&token7);
    Node *sextoFilho = criaNodo(&token8);
    Node *setimoFilho = criaNodo(&token9);
    Node *oitavoFilho = criaNodo(&token10);
    Node *nonoFilho = criaNodo(&token11);
    adicionaFilho(primeiroNodo, terceiroFilho);
    adicionaFilho(primeiroNodo, quartoFilho);
    adicionaFilho(primeiroNodo, quintoFilho);
    adicionaFilho(primeiroNodo, sextoFilho);
    adicionaFilho(primeiroNodo, setimoFilho);
    adicionaFilho(primeiroNodo, oitavoFilho);
    adicionaFilho(primeiroNodo, nonoFilho);

    printf("Number of kids of the first node: %d\n\nResultado do descompila:\n", primeiroNodo->kidsNumber);
	

    descompila(primeiroNodo); // deve mostrar os valores de primeiroFilho (2) e filhoDoSegundoFilho (4), já que são os únicos nodos-folha
    printf("\n");
    libera(primeiroNodo);

    return 0;
}
