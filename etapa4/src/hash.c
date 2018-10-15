#include "../include/hash.h"
#include <stdio.h>

HashStack* tabelas = NULL;

int sizeOfType(int type, int vecSize){
	int temp = vecSize;
	if(vecSize == 0) temp = 1;	
	switch(type){
		case CHAR: return 1 * temp; break;
		case STRING: return 1 * temp; break; //1 para cada caractere, precisa ser mudado quadno conteúdo muda
		case INT: return 4 * temp; break;
		case FLOAT: return 8 * temp; break;
		case BOOL: return 1 * temp; break;
		case USER: return 0; break; // deve ser somado ao valor de cada campo conforme os campos são adicionados
	}
}

//função de hash inspirada em:
//http://www.cse.yorku.ca/~oz/hash.html

int hashFunction(char* symbol){
	unsigned long hash = 5381;
	int c;
	while(c = *symbol++)
		hash = ((hash<<5) + hash) + c;

	return (int)(hash%HASH_SIZE);
}

//adiciona nova tabela de símbolos ao topo da pilha, útil quando se inicializa 
//um novo escopo.                                               
void initTable(){
	HashStack* aux = (HashStack*)malloc(sizeof(HashStack));
	aux->currentTable = (Hash**) malloc(sizeof(Hash*) * HASH_SIZE);
	for(int i = 0; i<HASH_SIZE; i++)
		aux->currentTable[i] = NULL;
	aux->next = tabelas;
	tabelas = aux;
	aux = NULL; // evita duas referências a mesma posição

}

//libera possíveis campos de argumentos de função
void liberaArgs(int index){
	if (tabelas->currentTable[index]->args!=NULL){
		int i; 
		for(i = 0; i < tabelas->currentTable[index]->argsNum; i++){
			free(tabelas->currentTable[index]->args[i]);
			tabelas->currentTable[index]->args[i] = NULL;
		}
		free(tabelas->currentTable[index]->args);
		tabelas->currentTable[index]->args = NULL;
	}
}

void liberaFields(int index){
	if (tabelas->currentTable[index]->fields!=NULL){
		int i; 
		for(i = 0; i < tabelas->currentTable[index]->fieldsNum; i++){
			free(tabelas->currentTable[index]->fields[i]->fieldName);
			free(tabelas->currentTable[index]->fields[i]);
			tabelas->currentTable[index]->fields[i] = NULL;
		}
		free(tabelas->currentTable[index]->fields);
		tabelas->currentTable[index]->fields = NULL;
	}
}

void printFields(char *symbol){
	Hash *symbolContent = getSymbol(symbol);
	if (symbolContent!=NULL){
		int i; 
		for(i = 0; i < symbolContent->fieldsNum; i++){
			printf("%s\n", symbolContent->fields[i]->fieldName);
		}
	}
}
//libera memória de todos os símbolos presentes na tabela do topo da pilha
void freeTable(){
	
	if(tabelas->currentTable != NULL){

		int tableIndex;
		for(tableIndex = 0; tableIndex<HASH_SIZE; tableIndex++){
			if(tabelas->currentTable[tableIndex]!=NULL){
				if (tabelas->currentTable[tableIndex]->valor_lexico!= NULL){
					liberaArgs(tableIndex);
					liberaFields(tableIndex);
					free(tabelas->currentTable[tableIndex]->symbol);
					free(tabelas->currentTable[tableIndex]->valor_lexico);
					tabelas->currentTable[tableIndex]->valor_lexico = NULL;
				}
				free(tabelas->currentTable[tableIndex]);
				tabelas->currentTable[tableIndex] = NULL;
			}
		}

	}
}

//remove uma tabela do tipo da pilha, útil quando um escopo está sendo fechado.
void closeTable(){
	
	if(tabelas != NULL){
		freeTable();
		free(tabelas->currentTable);
		HashStack* aux = tabelas;
		tabelas = tabelas->next;
		free(aux);
	}

}
//adiciona um novo símbolo à tabela de símbolos do topo da pilha, será recebido 
//o valor léxico do símbolo, a sua natureza e o seu tipo. A linha está presente
//no valor léxico, e o tamanho é inferido a partid do tipo. Se o símbolo for uma
//função, os argumentos devem ser adicionados usando addFuncArg. Se for um tipo
//de usuário, os campos devem ser adicionados usando addField.
//Retornará 0 se adicionou corretamente, ou um valor diferente se ocorreu um erro
//O erro que pode ocorrer é o símbolo já estar definido no escopo atual
//adiciona um novo símbolo à tabela de símbolos do topo da pilha, será recebido 
//o valor léxico do símbolo, a sua natureza e o seu tipo. A linha está presente
//no valor léxico, e o tamanho é inferido a partid do tipo. Se o símbolo for uma
//função, os argumentos devem ser adicionados usando addFuncArg. Se for um tipo
//de usuário, os campos devem ser adicionados usando addField.
//Retornará 0 se adicionou corretamente, ou um valor diferente se ocorreu um erro
//O erro que pode ocorrer é o símbolo já estar definido no escopo atual
int addSymbol(struct lexval* valor_lexico, int nature, int type, char* userType, int vecSize, int isFunction, int flags){
	
	int hashIndex = hashFunction(valor_lexico->value.str);
	while (tabelas->currentTable[hashIndex]!=NULL){
		if(strcmp(tabelas->currentTable[hashIndex]->symbol, valor_lexico->value.str) == 0){
			//símbolo já declarado
			return ERR_DECLARED;
		}
		//precisamos procurar outra posição para o símbolo, a pesquisa será
		//realizada de forma linear até que se ache uma posição livre na tabela
		hashIndex = (hashIndex + 1)%HASH_SIZE;
		
	}
	tabelas->currentTable[hashIndex] = (Hash*)malloc(sizeof(Hash));
	tabelas->currentTable[hashIndex]->symbol = (char*) malloc(sizeof(char) * (strlen(valor_lexico->value.str) + 1));
	strcpy(tabelas->currentTable[hashIndex]->symbol, valor_lexico->value.str);
	tabelas->currentTable[hashIndex]->line = valor_lexico->lineNumber;
	tabelas->currentTable[hashIndex]->nature = nature;
	tabelas->currentTable[hashIndex]->type = type;
	if (userType == NULL)
		tabelas->currentTable[hashIndex]->userType = NULL;
	else{ 
		tabelas->currentTable[hashIndex]->userType = (char*) malloc(sizeof(char) * (strlen(userType) + 1));
		strcpy(tabelas->currentTable[hashIndex]->userType, userType);		
	}
	tabelas->currentTable[hashIndex]->isFunction = isFunction;
	tabelas->currentTable[hashIndex]->flags = flags;
	tabelas->currentTable[hashIndex]->size = sizeOfType(type, vecSize);
	tabelas->currentTable[hashIndex]->vecSize = vecSize;
	tabelas->currentTable[hashIndex]->argsNum = 0;
	tabelas->currentTable[hashIndex]->fieldsNum = 0;
	tabelas->currentTable[hashIndex]->args = (FuncArg**)malloc(sizeof(FuncArg*));
	tabelas->currentTable[hashIndex]->fields = (UserTypeField**)malloc(sizeof(UserTypeField*));
	tabelas->currentTable[hashIndex]->valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	*(tabelas->currentTable[hashIndex]->valor_lexico) = *(valor_lexico);
	return 0;
}
//adiciona um argumento a um símbolo
void addFuncArg(char* symbol, FuncArg* arg)
{
	Hash* symbolContent = getSymbol(symbol);
	if(symbolContent != NULL){

		symbolContent->argsNum = symbolContent->argsNum + 1;
		if(symbolContent->args != NULL)
		symbolContent->args = (FuncArg**)realloc(
			symbolContent->args, 
			symbolContent->argsNum * sizeof(FuncArg*)
		);
		symbolContent->args[symbolContent->argsNum - 1] = arg;

	}
}
//adiciona um tipo de usuário a um símbolo
void addField(char* symbol, UserTypeField* utf)
{
	Hash* symbolContent = getSymbol(symbol);
	if(symbolContent != NULL){
	
		symbolContent->fieldsNum = symbolContent->fieldsNum + 1;
		symbolContent->fields = (UserTypeField**)realloc(
			symbolContent->fields, 
			symbolContent->fieldsNum * sizeof(UserTypeField**)
		);
		symbolContent->fields[symbolContent->fieldsNum - 1] = utf;
		//tamanho do tipo de usuário
		symbolContent->size = symbolContent->size + sizeOfType(utf->fieldType, 0);
	}
}
//busca um determinado símbolo em toda a pilha de tabelas de símbolos, começando
//pela tabela do escopo atual, subindo até o escopo global
Hash* getSymbol(char* symbol)
{
	int hashIndex = hashFunction(symbol);
	int tempIndex = hashIndex; // será usado se for necessário buscar símbolo em caso
                               // de colisão
	Hash* symbolContent;
	HashStack* aux = tabelas;
	do{	
		symbolContent = aux->currentTable[hashIndex];
		while(symbolContent != NULL){	
			if(strcmp(symbolContent->symbol, symbol) == 0)
				return symbolContent;
			else{
				tempIndex++;
				symbolContent = aux->currentTable[tempIndex];
			}
		}
		aux = aux->next;
		tempIndex = hashIndex;
	}while(aux!=NULL);

	return NULL; // vai ser NULL se não existir
}

int isDefined(char *symbol){
	Hash *symbolContent = getSymbol(symbol);
	if(symbolContent == NULL)
		return ERR_UNDECLARED;
	else return 0;
}

int isFunction(char *symbol){
	int defined = isDefined(symbol);
	if (defined == 0){
		Hash *symbolContent = getSymbol(symbol);
		if(symbolContent->isFunction == TRUE)
			return TRUE;
		else return ERR_FUNCTION;
	}
	else return defined;
}

int isVector(char *symbol){
	int defined = isDefined(symbol);
	if (defined == 0){
		Hash *symbolContent = getSymbol(symbol);
		if(symbolContent->vecSize > 0)
			return TRUE;
		else return ERR_VECTOR;
	}
	else return defined;
}

int isVariable(char *symbol){
	int defined = isDefined(symbol);
	if (defined == 0){
		Hash *symbolContent = getSymbol(symbol);
		if(isVector(symbol) != TRUE && isFunction(symbol) != TRUE)
			return TRUE;
		else return ERR_VARIABLE;
	}
	else return defined;
}

int isUserType(char *symbol){
	int defined = isDefined(symbol);
	if (defined == 0){
		Hash *symbolContent = getSymbol(symbol);
		if(symbolContent->fieldsNum > 0)
			return TRUE;
		else return ERR_USER;
	}
	else return defined;
}

int hasField (char* symbol, char* field){
	int isUT = isUserType(symbol);
	if(isUT == TRUE){
		Hash* symbolContent = getSymbol(symbol);
		int i;
		for(i = 0; i<symbolContent->fieldsNum; i++){
			if (strcmp(symbolContent->fields[i]->fieldName, field) == 0) return TRUE;
		}
		return ERR_USER;
	}
	else return isUT;
}

