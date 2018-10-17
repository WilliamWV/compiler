#include "../include/expression.h"
#include "../include/tree.h"
#include "../include/lexVal.h"
#include "../include/hash.h"
#include <stdio.h>

Operands *currentOperands = NULL;

int operandosNaExpAtual = 0;

Operands *criaOperando(Node *ast){
	Operands *newOperand = NULL;
	if(ast != NULL){
		if(ast->token != NULL)
		{
			if(ast->token->literType == INT || ast->token->literType == FLOAT || ast->token->literType == BOOL || ast->token->literType == STRING || ast->token->literType == CHAR){	
				newOperand = malloc(sizeof(Operands));
				newOperand->identifier = NULL;
				newOperand->type = NONE;
				newOperand->next = NULL;
				switch(ast->token->literType)
				{
					case INT: newOperand->type = INT; break;
					case FLOAT: newOperand->type = FLOAT; break;
					case BOOL: newOperand->type = BOOL; break;
					case STRING: newOperand->type = STRING; break;
					case CHAR: newOperand->type = CHAR; break;
				}
			}
			else if(ast->token->tokenType == IDS){				
				newOperand = malloc(sizeof(Operands));
				newOperand->identifier = NULL;
				newOperand->type = NONE;
				newOperand->next = NULL;
				if(ast->fieldOf != NULL){
					newOperand->identifier = ast->token->value.str;
					newOperand->type = fieldType(ast->fieldOf, ast->token->value.str);
				}
				else{
					newOperand->identifier = ast->token->value.str;
					newOperand->type = identifierType(ast->token->value.str);
				}
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
		}
		aux = aux->next;
	}
}

int wrongTypeInExpression(){
	Operands *aux = currentOperands;
	int foundExpressionOperands = FALSE;
	while(aux != NULL){
		if(aux->type == USER)
			return ERR_WRONG_TYPE;
		if(aux->type != CHAR && aux->type != STRING &&  aux->type != USER)
			foundExpressionOperands = TRUE;
		if( (aux->type == CHAR || aux->type == STRING) && foundExpressionOperands == TRUE)
			return ERR_WRONG_TYPE;
		aux = aux->next;
	}
	return 0;
}

//chamada apos a de cima
int typeInference(){
	Operands *aux = currentOperands;
	int type;
	int contador = 0;
	while(aux != NULL){
		if(contador == 0){
			contador++;
			type = aux->type;
		}
		if(type == INT && aux->type == FLOAT)
			type = FLOAT;
		else if(type == BOOL && aux->type == INT)
			type = INT;
		else if(type == BOOL && aux->type == FLOAT)
			type = FLOAT;
		aux = aux->next;
	}
	/*switch(type)
		{
			case INT: 
				printf("Tipo: int\n");
				break;
			case FLOAT: 
				printf("Tipo: float\n");
				break;
			case BOOL: 
				printf("Tipo: bool\n");
				break;
			case CHAR: 
				printf("Tipo: char\n");
				break;
			case STRING: 
				printf("Tipo: string\n");
				break;
			case USER:
				printf("Tipo: user\n");
				break;
		}*/
	return type;
}

int coercion(int expectedType, Node *expressionNode){
	int correctOperands =  wrongTypeInExpression();
		if (correctOperands != 0) return correctOperands;
	int expressionType = typeInference();
	if(expectedType != NONE){ // se estou esperando qualquer tipo nao ha erro de coercao
		if(expectedType == CHAR && expressionType != CHAR) return ERR_CHAR_TO_X;
		else if(expectedType != CHAR && expressionType == CHAR) return ERR_CHAR_TO_X;
		else if(expectedType == STRING && expressionType != STRING) return ERR_STRING_TO_X;
		else if(expectedType != STRING && expressionType == STRING) return ERR_STRING_TO_X;
		else if(expectedType == USER || expressionType == USER) return ERR_USER_TO_X;
	}

	expressionNode->type = expressionType;

	if(expectedType == FLOAT && expressionType == INT) { expressionNode->coercion = INT_TO_FLOAT; /*printf("int vira float\n");*/ }
	else if(expectedType == BOOL && expressionType == INT) { expressionNode->coercion = INT_TO_BOOL; /*printf("int vira bool\n");*/ }
	else if(expectedType == FLOAT && expressionType == BOOL) { expressionNode->coercion = BOOL_TO_FLOAT; /*printf("bool vira float\n");*/ }
	else if(expectedType == INT && expressionType == BOOL) { expressionNode->coercion = BOOL_TO_INT; /*printf("bool vira int\n");*/ }
	else if(expectedType == INT && expressionType == FLOAT) { expressionNode->coercion = FLOAT_TO_INT; /*printf("float vira int\n");*/ }
	else if(expectedType == BOOL && expressionType == FLOAT) { expressionNode->coercion = FLOAT_TO_BOOL; /*printf("float vira bool\n");*/ }
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


