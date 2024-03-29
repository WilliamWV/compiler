#include "../include/functionArgs.h"
#include "../include/tree.h"
#include <stdio.h>

//útil para verificar retorno
char *currentFunc = NULL;

Args *currentArgs = NULL;

int argsNaFuncaoAtual = 0;
int contaArgs = 0;

Args *criaArg(Node *arg){
	Args *newArg = malloc(sizeof(Args));
	newArg->arg = malloc(sizeof(FuncArg));
	newArg->arg->isConst = FALSE;
	newArg->arg->argType = NONE;
	newArg->arg->userType = NULL;
	int i = 0;
	if(arg!=NULL){
		if(!(arg->kidsNumber == 1 && arg->token->tokenType == IDS))
			adicionaInfoAArg(arg, newArg);
		else{
				newArg->arg->userType = arg->token->value.str;
				newArg->arg->argType = USER;
			}
		while(i < arg->kidsNumber){
			if(!(arg->kidsNumber == 2 && arg->kids[0]->token->tokenType == IDS && i == 0)) // se estou analisando o primeiro filho e ele eh um identificador, significa que ele eh um tipo de usuario e que nao quero adicionar ele como argumento; quero adicionar apenas a variavel que eh desse tipo
				adicionaInfoAArg(arg->kids[i], newArg);
			else{
				newArg->arg->userType = arg->kids[0]->token->value.str;
				newArg->arg->argType = USER;
			}
			i++;
		}
	}
	newArg->next = NULL;
	contaArgs++;
	return newArg;	
}

void adicionaInfoAArg(Node* arg, Args *newArg){
	int i = 0;
	
	if(arg!=NULL){
			if(arg->token != NULL){
				if(arg->token->tokenType == KEYWORD){
					char *string = arg->token->value.str;
					if(strcmp(string, "const") == 0){
						newArg->arg->isConst = TRUE;					
					}
					else if(strcmp(string, "int") == 0){
						newArg->arg->argType = INT;					
					}
					else if(strcmp(string, "float") == 0){
						newArg->arg->argType = FLOAT;			
					}
					else if(strcmp(string, "bool") == 0){
						newArg->arg->argType = BOOL;			
					}
					else if(strcmp(string, "char") == 0){
						newArg->arg->argType = CHAR;
					}
					else if(strcmp(string, "string") == 0){
						//printf(" arg->token->value.str = %s\n",  arg->token->value.str);
						newArg->arg->argType = STRING;		
					}
				}
				else if(arg->token->tokenType == IDS){
					newArg->arg->argName = arg->token->value.str;		
				}		
			}
			i++;
	}
}

void adicionaArg(Args *newArg){
	if(currentArgs == NULL) currentArgs = newArg;
	Args *aux = currentArgs;
	if(aux != NULL){
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = newArg;
		newArg->next = NULL;
	}	
	argsNaFuncaoAtual++;
}


void addArgsToSymbol(char* symbol, Args *args){
	Args *aux = currentArgs;
	int storeContador;	
	int contador = 0;
	while(aux != NULL){
		aux = aux->next;
		contador++;
	}
	storeContador = contador;	
	while(storeContador > 0){		
		aux = currentArgs;
		contador = storeContador;
		while(contador-1 > 0){
				aux = aux->next;
				contador--;
		}
		if(aux->arg != NULL)
			addFuncArg(symbol, aux->arg);
		storeContador--;
	}
}

int verifyReturn(struct node* returnExpression){
	Hash* func = getSymbol(currentFunc);
	if(func == NULL){
		//tem algo errado com o tratamento se chegar aqui
		return ERR_WRONG_PAR_RETURN;
	}
	int retType = getCurrentFuncReturnType();
	if(retType!=USER){
		int correctOperands =  coercion(retType, returnExpression);
		if (correctOperands != 0){ return ERR_WRONG_PAR_RETURN;}
		return TRUE;
	}
	else{
		//Se for tipo de usuário a expressão será ou um identificador
		//ou um elemento de vetor, ambos terão como nodo raiz da expressão
		//o identificador que possui o tipo de usuário em userType
		if(returnExpression->type != USER) return ERR_WRONG_PAR_RETURN;
		else{
			Hash* exp = getSymbol(returnExpression->token->value.str);
			if(strcmp(func->userType, exp->userType) == 0)
				return TRUE;
			else return ERR_WRONG_PAR_RETURN;
		}
		
	}
		
}

void saveFunc(char* symbol){
	currentFunc = symbol;
	
}

void clearCurrentArgsError(){
	Args *aux = currentArgs;
	Args *temp = aux;
	while(argsNaFuncaoAtual > 0){
		int contador = 0;
		aux = currentArgs;
		while(aux != NULL){
			aux = aux->next;
			contador++;
		}
		aux = currentArgs;
		while(contador-1 > 0){
			temp = aux;
			aux = aux->next;
			contador--;
		}		
		temp->next = NULL;
		free(aux->arg);
		free(aux);
		argsNaFuncaoAtual--;
	}
	currentArgs = NULL;
}

void clearCurrentArgs(){
	Args *aux = currentArgs;
	Args *temp = aux;
	while(argsNaFuncaoAtual > 0){
		int contador = 0;
		aux = currentArgs;
		while(aux != NULL){
			aux = aux->next;
			contador++;
		}
		aux = currentArgs;
		while(contador-1 > 0){
			temp = aux;
			aux = aux->next;
			contador--;
		}		
		temp->next = NULL;
		free(aux);
		argsNaFuncaoAtual--;
	}
	currentArgs = NULL;
}

int getCurrentFuncReturnType(){
	Hash* func = getSymbol(currentFunc);
	if(func == NULL) return NONE;	
	return func->type;

}

void argsSize(){
	Args *aux = currentArgs;
	Hash* funcContent = getSymbol(currentFunc);
	if(funcContent!=NULL){
		while(aux != NULL){
			int newVarSize = sizeOfType(currentArgs->arg->argType, 0);
			updateLocalVarSize(newVarSize);
			funcContent->argsSize = funcContent->argsSize + newVarSize;
			aux = aux->next;			
		}
	}
}

void updateLocalVarSize(int newVarSize){
	Hash* funcContent = getSymbol(currentFunc);
	if(funcContent!=NULL){
		funcContent->sizeOfLocalVars = funcContent->sizeOfLocalVars + newVarSize;
	}	
}
