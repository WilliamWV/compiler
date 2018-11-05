#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>

int liberaDanglingUsed = FALSE;

int nodosCriados = 0;
int contaNodosRaiz = 0;

extern Node *danglingNodes;

////////////////////////////////////////////////////////////////////////////////
/// Node* criaNodo(struct lexval* token)                                     ///
/// função chamada pelas ações do bison definidas em parser.y seu objetivo é ///
/// construir um nodo da AST a partir de uma estrutura que represente um     ///
/// token da entrada capturado pelo scanner.l e analisado pelo parser.y      ///
////////////////////////////////////////////////////////////////////////////////
Node* criaNodo(struct lexval* token){
	nodosCriados++;
	if(token != NULL)
		token->tokenInAst = TRUE;
	Node *node = malloc(sizeof(Node));
	node->type = NONE;
	node->coercion = NONE;
	node->fieldOf = NULL;
	node->token = token;
	node->kidsNumber = 0;
	node->reg = NULL;
	node->opList = createILOCList();
	node->kids = (Node**)malloc(sizeof(Node*)); // aloca espaço para o primeiro ponteiro para um ponteiro de Node

	return node;
}

Node* criaNodoTipado(struct lexval* token, int type){
	nodosCriados++;
	if(token != NULL)
		token->tokenInAst = TRUE;
	Node *node = malloc(sizeof(Node));
	node->type = type;
	node->coercion = NONE;
	node->fieldOf = NULL;
	node->token = token;
	node->kidsNumber = 0;
	node->reg = NULL;
	node->opList = createILOCList();
	node->kids = (Node**)malloc(sizeof(Node*)); // aloca espaço para o primeiro ponteiro para um ponteiro de Node

	return node;
}

Node* criaNodoCampo(struct lexval* token, char *fieldOf){
	nodosCriados++;
	if(token != NULL)
		token->tokenInAst = TRUE;
	Node *node = malloc(sizeof(Node));
	node->type = NONE;
	node->coercion = NONE;
	node->fieldOf = fieldOf;
	node->token = token;
	node->kidsNumber = 0;
	node->reg = NULL;
	node->opList = createILOCList();
	node->kids = (Node**)malloc(sizeof(Node*)); // aloca espaço para o primeiro ponteiro para um ponteiro de Node

	return node;
}

////////////////////////////////////////////////////////////////////////////////
/// Node* criaNodoDangling(struct lexval* token)                             ///
/// função chamada pelo scanner.l logo após criar um token, seu objetivo se  ///
/// relaciona a manter registro de todos os tokens alocados o quanto antes   ///
/// para que se possa liberar memória correspondente a esses tokens em caso  ///
/// de erro no parse que faça que um nodo da AST correspondente a esse token ///
/// não seja criado.                                                         ///
///                                                                          ///
/// Portanto essa função é útil quando a criaNodo acaba não sendo chamada    ///
/// devido a situações de erro no parse. O tratamento, realizado em          ///
/// scanner.l acaba sendo feito criando uma segunda árvore com nodos de      ///
/// mesma estrutura da AST que não possui a mesma ordem lógica e cujos nodos ///
/// não ficam órfãos em caso de erro. Em situação normal, ou seja, sem erros,///
/// essa segunda árvore vai acabar sendo desalocada pela libera pois todos   ///
/// seus ponteiros também estarão na AST do programa.                        ///
////////////////////////////////////////////////////////////////////////////////
Node* criaNodoDangling(struct lexval* token){
	Node *node = malloc(sizeof(Node));
	node->token = token;
	node->kidsNumber = 0;
	node->kids = (Node**)malloc(sizeof(Node*));

	return node;
}
////////////////////////////////////////////////////////////////////////////////
/// void adicionaFilho(Node *pai, Node *kid)                                 ///
/// função chamada pelas ações do bison definidas em parser.y seu objetivo é ///
/// adicionar um nodo já criado como filho de outro nodo, isso é feito       ///
/// seguindo a ordem explicada na observação 6 das ações em parser.y         ///
////////////////////////////////////////////////////////////////////////////////
void adicionaFilho(Node *pai, Node *kid){
	pai->kidsNumber = pai->kidsNumber + 1;
	pai->kids = (Node**)realloc(pai->kids, pai->kidsNumber * sizeof(Node*)); // aloca espaço para mais um ponteiro para um ponteiro de Node
	pai->kids[pai->kidsNumber - 1] = kid; // acessa o ponteiro recém alocado e guarda nele um ponteiro de Node
}
////////////////////////////////////////////////////////////////////////////////
/// void imprimeToken(union Value value, int tokenType, int literType)       ///
/// função chamada pela descompila com resposábilidade de imprimir um token  ///
/// considerando seu valor, o tipo do token e, se o token é um literal, o    ///
/// tipo do literal                                                          ///
////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
/// void descompila(void *voidNode)                                          ///
/// função segue a especficicação do trabalho percorrendo a árvore a partir  ///
/// da raiz. Gera um programa semanticamente equivalente ao programa entrado ///
/// que gerou a AST.                                                         ///
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
/// void libera(void *voidNode)                                              ///
/// função segue a especficicação do trabalho e libera a memória alocada no  ///
/// processo de construção da AST, inicialmente são liberados os nodos que   ///
/// não foram adicionados à AST final devido a erro, mas que estão na árvore ///
/// auxiliar, em seguida vai percorrendo a AST de forma recursiva liberando  ///
/// os nodos correspondentes aos filhos até que todos os nodos tenham sido   ///
/// desalocados                                                              ///
////////////////////////////////////////////////////////////////////////////////
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
		//libera memória alocada para string se foi usado strdup
		if(n->token != NULL)
			if(n->token->tokenType == KEYWORD || n->token->tokenType == COMP_OPER || n->token->tokenType == IDS || (n->token->tokenType == LITERAL && n->token->literType == STRING))
			free(n->token->value.str);
		free(n->token);
		free(n);	// libera o nodo
	}
}

////////////////////////////////////////////////////////////////////////////////
/// void liberaDanglingScanner(Node *n)                                      ///
/// Libera nodos criados no scanner. Tais nodos sao criados para armazenar   ///
/// todos os tokens encontrados. Isso eh necessario pois o scanner pode      ///
/// alocar tokens que nunca serao postos em um nodo pelo parser (pode-se     ///
/// verificar com a entrada "zor z@r;" de wrongEntry2). Tais tokens terao    ///
/// tokenInAst == FALSE, e serao desalocados nessa funcao.                   ///
////////////////////////////////////////////////////////////////////////////////
void liberaDanglingScanner(Node *n){ //recebe ponteiro de Node como ponteiro void devido a especificacao, depois faz o cast
	int i = 0;
	if(n!=NULL){
		while(i < n->kidsNumber){ // enquanto houver filhos, os explora...
			liberaDanglingScanner(n->kids[i]); // ... e os libera
			i++;
		}
		free(n->kids);	// libera ponteiro para ponteiro de nodos (os ponteiros de nodos foram liberados no while acima, por meio de free(n))
		//libera memória alocada para string se foi usado strdup
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

////////////////////////////////////////////////////////////////////////////////
/// void liberaDanglingParser(Node *n)                                       ///
/// Libera nodos "soltos" criados no parser quando ha erro; esses nodos      ///
/// terao tokenInAst == TRUE, ja que sao criados com criaNodo(). Funcao eh   /// 
/// chamada pelo destrutor de <ast>.                                         ///
////////////////////////////////////////////////////////////////////////////////
void liberaDanglingParser(Node *n){ //recebe ponteiro de Node como ponteiro void devido a especificacao, depois faz o cast
	int i = 0;
	if(n!=NULL){
		nullifyPointer(n->token, danglingNodes);
		while(i < n->kidsNumber){ // enquanto houver filhos, os explora...
			liberaDanglingParser(n->kids[i]); // ... e os libera
			i++;
		}
		free(n->kids);	// libera ponteiro para ponteiro de nodos (os ponteiros de nodos foram liberados no while acima, por meio de free(n))
		//libera memória alocada para string se foi usado strdup
		if(n->token != NULL){
				if(n->token->tokenType == KEYWORD || n->token->tokenType == COMP_OPER || n->token->tokenType == IDS || (n->token->tokenType == LITERAL && n->token->literType == STRING))
					free(n->token->value.str);
				free(n->token);	
		}
		free(n);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// void nullifyPointer(struct lexval* token, Node *n)                       ///
/// Quando o parser vai liberar um nodo+token, eh necessario checar se o     ///
/// ponteiro para o token que vai ser desalocado esta em danglingNodes. Se   ///
/// estiver, devemos fazer com que o ponteiro, em danglingNodes, para tal    ///
/// token aponte para NULL. Isso se faz necessario pois, apesar de em        ///
/// liberaDanglingScanner(Node *n) apenas os tokens com tokenInAst == FALSE  ///
/// serem desalocados, acabamos percorrendo todos os tokens criados pelo     ///
/// scanner; logo, se nao apontarmos o ponteiro para NULL, tentaremos        ///
/// acessar um ponteiro que ja foi liberado.                                 ///
////////////////////////////////////////////////////////////////////////////////

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

void contaNodosNaRaiz(Node *n){
	int i =0;
	if(n!=NULL){
		while(i < n->kidsNumber){ // enquanto houver filhos, os explora...
				contaNodosNaRaiz(n->kids[i]);
				i++;				
		}
		contaNodosRaiz++;
	}
}
