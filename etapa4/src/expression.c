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
		adicionaOperando(criaOperando(ast));
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
		}
		aux = aux->next;
	}
}
