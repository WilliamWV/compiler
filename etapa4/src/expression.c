#include "../include/expression.h"
#include "../include/tree.h"
#include "../include/lexVal.h"
#include "../include/hash.h"
#include <stdio.h>

Operands *currentOperands = NULL;

int operandosNaExpAtual = 0;
int openedParenthesis = 0;
Operands *criaOperando(Node *ast){
	Operands *newOperand = NULL;
	if(ast != NULL){
		if(ast->token != NULL)
		{
			if(ast->token->literType == INT || ast->token->literType == FLOAT || ast->token->literType == BOOL || ast->token->literType == STRING || ast->token->literType == CHAR){	
				if(openedParenthesis == 0){
					newOperand = malloc(sizeof(Operands));
					newOperand->identifier = NULL;
					newOperand->originalType = NONE;
					newOperand->next = NULL;
					newOperand->previous = NULL;
					switch(ast->token->literType)
					{
						case INT: newOperand->originalType = INT; break;
						case FLOAT: newOperand->originalType = FLOAT; break;
						case BOOL: newOperand->originalType = BOOL; break;
						case STRING: newOperand->originalType = STRING; break;
						case CHAR: newOperand->originalType = CHAR; break;
					}
					newOperand->type = newOperand->originalType;
				}
			}
			else if(ast->token->tokenType == IDS && openedParenthesis == 0){				
				newOperand = malloc(sizeof(Operands));
				newOperand->identifier = NULL;
				newOperand->originalType = NONE;
				newOperand->type = NONE;
				newOperand->next = NULL;
				newOperand->previous = NULL;
				if(ast->fieldOf != NULL){
					newOperand->identifier = ast->token->value.str;
					newOperand->originalType = fieldType(ast->fieldOf, ast->token->value.str);
					newOperand->type = newOperand->originalType;
				}
				else{
					newOperand->identifier = ast->token->value.str;
					newOperand->originalType = identifierType(ast->token->value.str);
					newOperand->type = newOperand->originalType;
				}
			}
			else if(ast->token->tokenType == SPEC_CHAR){
				if(openedParenthesis == 0){
					if(ast->token->value.c == '('){
						newOperand = malloc(sizeof(Operands));
						newOperand->identifier = NULL;
						newOperand->next = NULL;
						newOperand->previous = NULL;
						newOperand->character =  ast->token->value.c;
						newOperand->originalType = ast->kids[0]->type;
						//printf("tipo: %d\n",newOperand->originalType );
						newOperand->type = newOperand->originalType;
						//printf("ok1\n");
					}
					else{
						newOperand = malloc(sizeof(Operands));
						newOperand->identifier = NULL;
						newOperand->next = NULL;
						newOperand->previous = NULL;
						newOperand->originalType = SPEC_CHAR;
						newOperand->type = newOperand->originalType;
						newOperand->character =  ast->token->value.c;
					}
				}
				if(ast->token->value.c == '('){
						openedParenthesis++;
				}
				else if(ast->token->value.c == ')'){
						openedParenthesis--;
				}			
			}
			else if(ast->token->tokenType == COMP_OPER && openedParenthesis == 0 ){
				newOperand = malloc(sizeof(Operands));
				newOperand->next = NULL;
				newOperand->previous = NULL;
				newOperand->originalType = COMP_OPER;
				newOperand->type = newOperand->originalType;
				newOperand->identifier = ast->token->value.str;				
			}
		}
	}
	
	return newOperand;	
}

void adicionaOperando(Operands *newOperand){
	if(newOperand != NULL){
		if(currentOperands == NULL) currentOperands = newOperand;
		Operands *aux = currentOperands;
		if(aux != NULL){
			while(aux->next != NULL){
				aux = aux->next;
			}
			aux->next = newOperand;
			//printf("ops\n");
			newOperand->previous = aux;
			//printf("uepa\n");
			newOperand->next = NULL;
		}	
		operandosNaExpAtual++;
	}
}

void parseOperands(Node *ast){
	int i = 0;
	if(ast!=NULL){
		Operands *newOperand= criaOperando(ast);

		//excecoes especificas para tratar o caso de variaveis do tipo do usuario com campos (exemplo: tipousuario$campo); sem esses ifs acabamos adicionando tanto a variavel quanto o campo como operandos
		if( (ast->kidsNumber == 2 || ast->kidsNumber == 4) && ast->kids[0]->token->tokenType == SPEC_CHAR){
			if(ast->kids[0]->token->value.c != '$'){
				adicionaOperando(newOperand);
			}else{
				free(newOperand);
			}
		}
		else if( (ast->kidsNumber == 7 || ast->kidsNumber == 5) && ast->kids[3]->token->tokenType == SPEC_CHAR){
			if(ast->kids[3]->token->value.c != '$'){
				adicionaOperando(newOperand);
			}
			else{
				free(newOperand);
			}
		}
		else adicionaOperando(newOperand);
		while(i < ast->kidsNumber){ // enquanto houver filhos, os explora e os imprime
			parseOperands(ast->kids[i]);
			i++;
		}
	}
}

void printCurrentOperands(){
	Operands *aux = currentOperands;
	while(aux != NULL){
		switch(aux->type)
		{
			case INT: 
				if(aux->identifier != NULL)
					printf("Tipo: int; Identificador: %s\n", aux->identifier);
				else printf("Tipo: int; Sem identificador (literal)\n");
				break;
			case FLOAT: 
				if(aux->identifier != NULL)
					printf("Tipo: float; Identificador: %s\n", aux->identifier);
				else printf("Tipo: float; Sem identificador (literal)\n");
				break;
			case BOOL: 
				if(aux->identifier != NULL)
					printf("Tipo: bool; Identificador: %s\n", aux->identifier);
				else printf("Tipo: bool; Sem identificador (literal)\n");
				break;
			case CHAR: 
				if(aux->identifier != NULL)
					printf("Tipo: char; Identificador: %s\n", aux->identifier);
				else printf("Tipo: char; Sem identificador (literal)\n");
				break;
			case STRING: 
				if(aux->identifier != NULL)
					printf("Tipo: string; Identificador: %s\n", aux->identifier);
				else printf("Tipo: string; Sem identificador (literal)\n");
				break;
			case USER:
				if(aux->identifier != NULL)
					printf("Tipo: criado pelo usuario; Identificador: %s\n", aux->identifier);
				else printf("Tipo: criado pelo usuario; Sem identificador (literal)\n");
				break;
			case COMP_OPER: printf("Operador composto: %s\n", aux->identifier); break;
			case SPEC_CHAR: printf("Operador simples: %c\n", aux->character); break;
		}
		aux = aux->next;
	}
}

int wrongTypeInExpression(){
	Operands *aux = currentOperands;
	int foundExpressionOperandsOrOperators = FALSE; // marca que achou ou operadores aritmeticos/booleanos, ou operandos numericos/booleanos, que n podem se misturar com char e string nas expressoes
	int isComparison = 0;
	int isNotComparisonOnly = 0;
	int isBitwise = 0;
	int foundString = FALSE;
	int foundChar = FALSE;
	while(aux != NULL){
		if(aux->originalType == COMP_OPER){
			if(aux->originalType == USER) return ERR_WRONG_TYPE;
			if(strcmp(aux->identifier, "==") == 0 || strcmp(aux->identifier, "!=") == 0 ){
				//printf("%d %d\n", aux->previous->type, aux->next->type);
				if(!(aux->previous->type == aux->next->type || ( (aux->previous->type == INT || aux->previous->type == FLOAT || aux->previous->type == BOOL) && (aux->next->type == INT || aux->next->type == FLOAT || aux->next->type == BOOL) ) ))
					return ERR_WRONG_TYPE;
				else{
					aux->next->type = BOOL;
					aux->previous->type = BOOL;
				}

				//printf("previous coercion type:%d next original type:%d next coercion type: %d\n", aux->previous->type, aux->next->originalType, aux->next->type);
			}
			else if( strcmp(aux->identifier, "&&") == 0 || strcmp(aux->identifier, "||") == 0 ){
					if(aux->previous->type == CHAR || aux->previous->type == STRING || aux->next->type == CHAR || aux->next->type == STRING) return ERR_WRONG_TYPE;
					if(aux->previous->type == INT) aux->previous->type = BOOL;
					if (aux->previous->type == FLOAT) aux->previous->type = BOOL;
					if(aux->next->type == INT) aux->next->type = BOOL;
					if(aux->next->type == FLOAT) aux->next->type = BOOL;
				}
			else{
				if(aux->type == CHAR || aux->type == STRING)
					return ERR_WRONG_TYPE;
			}
			
		}

		if(aux->originalType == SPEC_CHAR){
			if( aux->character == '&' || aux->character == '|'){
				if(!(aux->previous->type == aux->next->type || ( (aux->previous->type == INT || aux->previous->type == FLOAT || aux->previous->type == BOOL) && (aux->next->type == INT || aux->next->type == FLOAT || aux->next->type == BOOL) ) ))
					return ERR_WRONG_TYPE;	
			}
			else if( aux->character == '!' ){
				if(aux->next->type == CHAR || aux->next->type == STRING)
					return ERR_WRONG_TYPE;
				else if(aux->next->type == INT) {aux->next->type = BOOL;/* printf("%c    tipo: %d    tipo original: %d\n\n", aux->next->character,aux->next->type, aux->next->originalType);*/}
				else if(aux->next->type == FLOAT) aux->next->type = BOOL;
			}
			else{
				if(aux->next->type == USER || aux->next->type == CHAR || aux->next->type == STRING)
					return ERR_WRONG_TYPE;
			}
		}

		aux = aux->next;		
	}

	return 0;
}

//chamada apos a de cima
int typeInference(){
	Operands *aux = currentOperands;
	int type;
	int contador = 0;
	while(aux->next != NULL){aux = aux->next;}
	type = aux->type;
	aux = currentOperands;
	while(aux != NULL){
		/*if(contador == 0){
			if(aux->type != SPEC_CHAR && aux->type != COMP_OPER){
				contador++;
				type = aux->type;
			}
		}*/
		if(type == INT && aux->type == FLOAT)
			type = FLOAT;
		else if(type == BOOL && aux->type == INT)
			type = INT;
		else if(type == BOOL && aux->type == FLOAT)
			type = FLOAT;
		aux = aux->next;
	}
	
	return type;
}

int coercion(int expectedType, Node *expressionNode){
	int correctOperands =  wrongTypeInExpression(); // 1 eh pq soh tem operadores de comparacao na expressao, entao seu tipo deve ser booleano; 0 indica que a expressao pode ter tipos diversos
	if (correctOperands > 1) return correctOperands;

	int expressionType = typeInference();	
	if(correctOperands == 1) expressionType = BOOL;

	//printf("%d %d", expectedType, expressionType);
	if(expectedType != NONE){ // se estou esperando qualquer tipo nao ha erro de coercao
		if(expectedType == CHAR && expressionType != CHAR) return ERR_CHAR_TO_X;
		else if(expectedType != CHAR && expressionType == CHAR) return ERR_CHAR_TO_X;
		else if(expectedType == STRING && expressionType != STRING) return ERR_STRING_TO_X;
		else if(expectedType != STRING && expressionType == STRING) return ERR_STRING_TO_X;
		else if(expectedType == USER || expressionType == USER) return ERR_USER_TO_X;
	}

	expressionNode->type = expressionType;
	//printf("%d\n", expressionNode->type);

	if(expectedType == FLOAT && expressionType == INT) { expressionNode->coercion = INT_TO_FLOAT; printf("int vira float\n"); }
	else if(expectedType == BOOL && expressionType == INT) { expressionNode->coercion = INT_TO_BOOL; printf("int vira bool\n"); }
	else if(expectedType == FLOAT && expressionType == BOOL) { expressionNode->coercion = BOOL_TO_FLOAT; printf("bool vira float\n"); }
	else if(expectedType == INT && expressionType == BOOL) { expressionNode->coercion = BOOL_TO_INT; printf("bool vira int\n"); }
	else if(expectedType == INT && expressionType == FLOAT) { expressionNode->coercion = FLOAT_TO_INT; printf("float vira int\n"); }
	else if(expectedType == BOOL && expressionType == FLOAT) { expressionNode->coercion = FLOAT_TO_BOOL; printf("float vira bool\n"); }
	return 0;
}

void clearCurrentOperands(){
	Operands *aux = currentOperands;
	Operands *temp = aux;
	while(operandosNaExpAtual > 0){
		int contador = 0;
		aux = currentOperands;
		while(aux != NULL){
			aux = aux->next;
			contador++;
		}
		aux = currentOperands;
		while(contador-1 > 0){
			temp = aux;
			aux = aux->next;
			contador--;
		}		
		temp->next = NULL;
		free(aux);
		operandosNaExpAtual--;
	}
	currentOperands = NULL;
}


