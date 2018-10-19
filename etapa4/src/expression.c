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
			newOperand->previous = aux;
			newOperand->next = NULL;
		}	
		operandosNaExpAtual++;
	}
}

void parseOperands(Node *ast){
	int i = 0;
	
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
				if(!(aux->previous->type == aux->next->type || ( (aux->previous->type == INT || aux->previous->type == FLOAT || aux->previous->type == BOOL) && (aux->next->type == INT || aux->next->type == FLOAT || aux->next->type == BOOL) ) ))
					return ERR_WRONG_TYPE;
				else{
					aux->next->type = BOOL;
					aux->previous->type = BOOL;
				}

				
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

int coercion(int expectedType, Node *expressionNode){
	
	int expressionType = expressionNode->type;	
	
	if(expectedType != NONE){ // se estou esperando qualquer tipo nao ha erro de coercao
		if(expectedType == CHAR && expressionType != CHAR) return ERR_CHAR_TO_X;
		else if(expectedType != CHAR && expressionType == CHAR) return ERR_CHAR_TO_X;
		else if(expectedType == STRING && expressionType != STRING) return ERR_STRING_TO_X;
		else if(expectedType != STRING && expressionType == STRING) return ERR_STRING_TO_X;
		else if(expectedType == USER || expressionType == USER) return ERR_USER_TO_X;
	}
	

	if(expectedType == FLOAT && expressionType == INT) { expressionNode->coercion = INT_TO_FLOAT; /*printf("int vira float\n");*/ }
	else if(expectedType == BOOL && expressionType == INT) { expressionNode->coercion = INT_TO_BOOL; /*printf("int vira bool\n");*/ }
	else if(expectedType == FLOAT && expressionType == BOOL) { expressionNode->coercion = BOOL_TO_FLOAT; /*printf("bool vira float\n");*/ }
	else if(expectedType == INT && expressionType == BOOL) { expressionNode->coercion = BOOL_TO_INT; /*printf("bool vira int\n");*/ }
	else if(expectedType == INT && expressionType == FLOAT) { expressionNode->coercion = FLOAT_TO_INT; /*printf("float vira int\n");*/ }
	else if(expectedType == BOOL && expressionType == FLOAT) { expressionNode->coercion = FLOAT_TO_BOOL; /*printf("float vira bool\n");*/ }

	return 0;
}

int logicCoercion(Node *ss, Node *s1, Node *s3){
	if(s1->type == CHAR || s1->type == STRING || s3->type == CHAR || s3->type == STRING || s1->type == USER || s3->type == USER)
		return ERR_WRONG_TYPE;
	if(s1->type == INT)
		s1->coercion = INT_TO_BOOL;
	if(s3->type == INT)
		s1->coercion = INT_TO_BOOL;
	if(s1->type == FLOAT)
		s1->coercion = FLOAT_TO_BOOL;
	if(s3->type == FLOAT)
		s1->coercion = FLOAT_TO_BOOL;
	ss->type = BOOL;
	return 0;
}
int unaryLogicCoercion(Node *ss, Node *s2){
	if(s2->type == CHAR || s2->type == STRING || s2->type == USER)
		return ERR_WRONG_TYPE;
	if(s2->type == INT)
		s2->coercion = INT_TO_BOOL;
	else if(s2->type == FLOAT)
		s2->coercion = FLOAT_TO_BOOL;

	ss->type = BOOL;
	return 0;
}

int relationalCoercion(Node *ss, Node *s1, Node *s3){
	if(s1->type == USER || s3->type == USER)
		return ERR_WRONG_TYPE;
	if(s1->type == STRING && s3->type != STRING)
		return ERR_WRONG_TYPE;
	if(s1->type == CHAR && s3->type != CHAR)
		return ERR_WRONG_TYPE;
	else if(s1->type == INT && s3->type == FLOAT){
		s1->coercion = INT_TO_FLOAT;
		ss->type = BOOL;
		//printf("\nINT TO FLOAT\n");
	}
	else if(s3->type == INT && s1->type == FLOAT){
		s3->coercion = INT_TO_FLOAT;
		ss->type = BOOL;
		//printf("\nINT TO FLOAT\n");
	}
	else if(s1->type == BOOL && s3->type == FLOAT){
		s1->coercion = BOOL_TO_FLOAT;
		ss->type = BOOL;
		//printf("\nBOOL TO FLOAT\n");
	}
	else if(s3->type == BOOL && s1->type == FLOAT){
		s3->coercion = BOOL_TO_FLOAT;
		ss->type = BOOL;
		//printf("\nBOOL TO FLOAT\n");
	}
	else if(s1->type == BOOL && s3->type == INT){
		s1->coercion = BOOL_TO_INT;
		ss->type = BOOL;
		//printf("\nBOOL TO INT\n");
	}
	else if(s3->type == BOOL && s1->type == INT){
		s3->coercion = BOOL_TO_INT;
		ss->type = BOOL;
		//printf("\nBOOL TO INT\n");
	}
	else if(s1->type == s3->type){
		ss->type = BOOL;
	}
	return 0;
}

int bitwiseCoercion(Node *ss, Node *s1, Node *s3){
	if(s1->type == USER || s3->type == USER)
		return ERR_WRONG_TYPE;
	if(s1->type == STRING && s3->type != STRING)
		return ERR_WRONG_TYPE;
	if(s1->type == CHAR && s3->type != CHAR)
		return ERR_WRONG_TYPE;
	else if(s1->type == INT && s3->type == FLOAT){
		s1->coercion = INT_TO_FLOAT;
		ss->type = FLOAT;
		//printf("\nINT TO FLOAT\n");
	}
	else if(s3->type == INT && s1->type == FLOAT){
		s3->coercion = INT_TO_FLOAT;
		ss->type = FLOAT;
		//printf("\nINT TO FLOAT\n");
	}
	else if(s1->type == BOOL && s3->type == FLOAT){
		s1->coercion = BOOL_TO_FLOAT;
		ss->type = FLOAT;
		//printf("\nBOOL TO FLOAT\n");
	}
	else if(s3->type == BOOL && s1->type == FLOAT){
		s3->coercion = BOOL_TO_FLOAT;
		ss->type = FLOAT;
		//printf("\nBOOL TO FLOAT\n");
	}
	else if(s1->type == BOOL && s3->type == INT){
		s1->coercion = BOOL_TO_INT;
		ss->type = INT;
		//printf("\nBOOL TO INT\n");
	}
	else if(s3->type == BOOL && s1->type == INT){
		s3->coercion = BOOL_TO_INT;
		ss->type = INT;
		//printf("\nBOOL TO INT\n");
	}
	else if(s1->type == s3->type){
		ss->type = s1->type;
		
		//printf("chegoulhe\n\n");
	}
	return 0;
}

int unaryArithCoercion(Node *ss, Node *s2){
	if(s2->type == CHAR || s2->type == STRING || s2->type == USER)
		return ERR_WRONG_TYPE;
	if(s2->type == INT)
		ss->type = INT;
	else if(s2->type == FLOAT)
		ss->type = FLOAT;
	else if(s2->type == BOOL)
		ss->type = BOOL;
	return 0;
}

int arithRelationalCoercion(Node *ss, Node *s1, Node *s3){
	if(s1->type == CHAR || s1->type == STRING || s3->type == CHAR || s3->type == STRING || s1->type == USER || s3->type == USER)
		return ERR_WRONG_TYPE;
	else if(s1->type == INT && s3->type == FLOAT){
		s1->coercion = INT_TO_FLOAT;
		ss->type = BOOL;
		//printf("\nINT TO FLOAT\n");
	}
	else if(s3->type == INT && s1->type == FLOAT){
		s3->coercion = INT_TO_FLOAT;
		ss->type = BOOL;
		//printf("\nINT TO FLOAT\n");
	}
	else if(s1->type == BOOL && s3->type == FLOAT){
		s1->coercion = BOOL_TO_FLOAT;
		ss->type = BOOL;
		//printf("\nBOOL TO FLOAT\n");
	}
	else if(s3->type == BOOL && s1->type == FLOAT){
		s3->coercion = BOOL_TO_FLOAT;
		ss->type = BOOL;
		//printf("\nBOOL TO FLOAT\n");
	}
	else if(s1->type == BOOL && s3->type == INT){
		s1->coercion = BOOL_TO_INT;
		ss->type = BOOL;
		//printf("\nBOOL TO INT\n");
	}
	else if(s3->type == BOOL && s1->type == INT){
		s3->coercion = BOOL_TO_INT;
		ss->type = BOOL;
		//printf("\nBOOL TO INT\n");
	}
	else if(s1->type == s3->type)
		ss->type = BOOL;
	return 0;
}

int arithmeticCoercion(Node *ss, Node *s1, Node *s3){
	//printf("Tipo da esquerda: %d   Tipo da direita: %d\n\n", s1->type, s3->type );
	if(s1->type == CHAR || s1->type == STRING || s3->type == CHAR || s3->type == STRING || s1->type == USER || s3->type == USER)
		return ERR_WRONG_TYPE;
	else if(s1->type == INT && s3->type == FLOAT){
		s1->coercion = INT_TO_FLOAT;
		ss->type = FLOAT;
		//printf("\nINT TO FLOAT\n");
	}
	else if(s3->type == INT && s1->type == FLOAT){
		s3->coercion = INT_TO_FLOAT;
		ss->type = FLOAT;
		//printf("\nINT TO FLOAT\n");
	}
	else if(s1->type == BOOL && s3->type == FLOAT){
		s1->coercion = BOOL_TO_FLOAT;
		ss->type = FLOAT;
		//printf("\nBOOL TO FLOAT\n");
	}
	else if(s3->type == BOOL && s1->type == FLOAT){
		s3->coercion = BOOL_TO_FLOAT;
		ss->type = FLOAT;
		//printf("\nBOOL TO FLOAT\n");
	}
	else if(s1->type == BOOL && s3->type == INT){
		s1->coercion = BOOL_TO_INT;
		ss->type = INT;
		//printf("\nBOOL TO INT\n");
	}
	else if(s3->type == BOOL && s1->type == INT){
		s3->coercion = BOOL_TO_INT;
		ss->type = INT;
		//printf("\nBOOL TO INT\n");
	}
	else if(s1->type == s3->type)
		ss->type = s1->type;

	return 0;
}

void printAllOperands(Node *expression){
	int i = 0;
	if(expression!=NULL){
		if(expression->token != NULL)
			printOperandsWithoutInfo(expression);
		while(i < expression->kidsNumber){ // enquanto houver filhos, os explora e os imprime
			printAllOperands(expression->kids[i]);
			i++;
		}
	}
}

void printOperandsWithoutInfo(Node *expression){
	switch(expression->token->tokenType) // impressao especifica para cada token
	{
		case KEYWORD: printf("%s ", expression->token->value.str); break;
		case SPEC_CHAR: 
			switch(expression->token->value.c) // deixa a descompila um pouco mais formatada
			{
				case ';': printf("%c\n", expression->token->value.c); break;
				case '{': printf("%c\n", expression->token->value.c); break;

				case '}': printf("%c", expression->token->value.c); break;
				default: printf("%c", expression->token->value.c); break;
			}
			break;
		case COMP_OPER: printf("%s", expression->token->value.str); break;
		case IDS: printf("%s", expression->token->value.str); break;
		case LITERAL:
			switch(expression->token->literType)
			{
				case INT: printf("%d", expression->token->value.i); break;
				case FLOAT: printf("%f", expression->token->value.f); break;
				case CHAR: printf("\'%c\'", expression->token->value.c); break;
				case BOOL: 
					if(expression->token->value.b == TRUE)
						printf("true");
					else printf("false");
					break;
				case STRING: printf("%s", expression->token->value.str); break;		
			}
			break;
	}
}

void printOperand(Node *operand){
	int type = operand->type;
	int coercion = operand->coercion;
	if(operand->token == NULL){
		printf("Operacao intermediaria.");
	}
	else switch(operand->token->tokenType)
	{
		case SPEC_CHAR: printf("Operando SPEC_CHAR: \"%c\".", operand->token->value.c); break;
		case COMP_OPER: printf("Operando COMP_OPER: \"%s\".", operand->token->value.str); break;
		case IDS: printf("Operando IDENTIFICADOR: \"%s\".", operand->token->value.str); break;
		case LITERAL: 
			switch(operand->token->literType)
			{
				case INT: printf("Operando LITERAL INT: \"%d\".", operand->token->value.i); break;
				case FLOAT: printf("Operando LITERAL FLOAT: \"%f\".", operand->token->value.f); break;
				case CHAR: printf("Operando LITERAL CHAR: \"%c\".", operand->token->value.c); break;
				case BOOL: 
					if(operand->token->value.b == TRUE)
						printf("Operando LITERAL BOOL: \"true\".");
					else printf("Operando LITERAL BOOL: \"false\".");
					break;
				case STRING: printf("Operando LITERAL STRING: \"%s\".", operand->token->value.str); break;	
			}
			break;
		default: printf("Operando desconhecido."); break;
	}
	switch(operand->type)
	{
		case INT: printf(" Tipo INT."); break;
		case FLOAT: printf(" Tipo FLOAT."); break;
		case BOOL: printf(" Tipo BOOL."); break;
		case CHAR: printf(" Tipo CHAR."); break;
		case STRING: printf(" Tipo STRING."); break;
		case USER: printf(" Tipo USER."); break;
		case NONE: printf(" Tipo NONE."); break;
		default: printf(" Tipo UNKNOWN."); break;
	}
	switch(operand->coercion)
	{
		case INT_TO_BOOL: printf(" Coercao de INT para BOOL.\n"); break;
		case INT_TO_FLOAT: printf(" Coercao de INT para FLOAT.\n"); break;
		case FLOAT_TO_INT: printf(" Coercao de FLOAT para INT.\n"); break;
		case FLOAT_TO_BOOL: printf(" Coercao de FLOAT para BOOL.\n"); break;
		case BOOL_TO_FLOAT: printf(" Coercao de BOOL para FLOAT.\n"); break;
		case BOOL_TO_INT: printf(" Coercao de BOOL para INT.\n"); break;
		case NONE: printf(" Nao sofreu coercao.\n"); break;
		default: printf(" Coercao desconhecida.\n"); break;
	}
	if(operand->token == NULL){
		printf("	Operando da esquerda: ");
		printAllOperands(operand->kids[0]);
		printf("\n");
		if(operand->kids[1]->token->tokenType == SPEC_CHAR)
			printf("	Operando: %c", operand->kids[1]->token->value.c);
		else printf("	Operando: %s", operand->kids[1]->token->value.str);
		printf("\n");
		printf("	Operando da direita: ");
		printAllOperands(operand->kids[2]);
		printf("\n");
	}
}
void printExpression(Node *expression){
	int i = 0;
	if(expression!=NULL){
		printOperand(expression);
		while(i < expression->kidsNumber){ // enquanto houver filhos, os explora e os imprime
			printExpression(expression->kids[i]);
			i++;
		}
	}
}
