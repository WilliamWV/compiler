#include "../include/hash.h"

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
			free(tabelas->currentTable[index]->fields[i]);
			tabelas->currentTable[index]->fields[i] = NULL;
		}
		free(tabelas->currentTable[index]->fields);
		tabelas->currentTable[index]->fields = NULL;
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
void addSymbol(struct lexval* valor_lexico, int nature, int type, int vecSize, int isFunction){
	
	int hashIndex = hashFunction(valor_lexico->value.str);
	tabelas->currentTable[hashIndex] = (Hash*)malloc(sizeof(Hash));
	tabelas->currentTable[hashIndex]->line = valor_lexico->lineNumber;
	tabelas->currentTable[hashIndex]->nature = nature;
	tabelas->currentTable[hashIndex]->type = type;
	tabelas->currentTable[hashIndex]->isFunction = isFunction;
	tabelas->currentTable[hashIndex]->size = sizeOfType(type, vecSize);
	tabelas->currentTable[hashIndex]->vecSize = vecSize;
	tabelas->currentTable[hashIndex]->argsNum = 0;
	tabelas->currentTable[hashIndex]->fieldsNum = 0;
	tabelas->currentTable[hashIndex]->args = (FuncArg**)malloc(sizeof(FuncArg*));
	tabelas->currentTable[hashIndex]->fields = (UserTypeField**)malloc(sizeof(UserTypeField*));
	tabelas->currentTable[hashIndex]->valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	*(tabelas->currentTable[hashIndex]->valor_lexico) = *(valor_lexico);
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
	Hash* symbolContent;
	HashStack* aux = tabelas;
	do{	
		symbolContent = aux->currentTable[hashIndex];
		aux = aux->next;
	}while(symbolContent == NULL && aux != NULL);
	return symbolContent; // vai ser NULL se não existir
}

int isDefined(char *symbol){
	Hash *symbolContent = getSymbol(symbol);
	if(symbolContent == NULL)
		return ERR_UNDECLARED;
	else return 0;
}

int isFunction(char *symbol){
	int isDefined = isDefined(symbol);
	if (isDefined == 0){
		Hash *symbolContent = getSymbol(symbol);
		if(symbolContent->isFunction == TRUE)
			return TRUE;
		else return ERR_VECTOR;
	}
	else return isDefined;
}

int isVector(char *symbol){
	int isDefined = isDefined(symbol);
	if (isDefined == 0){
		Hash *symbolContent = getSymbol(symbol);
		if(symbolContent->vecSize > 0)
			return TRUE;
		else return ERR_VARIABLE;
	}
	else return isDefined;
}

int isVariable(char *symbol){
	int isDefined = isDefined(symbol);
	if (isDefined == 0){
		Hash *symbolContent = getSymbol(symbol);
		if(isVector(symbol) == FALSE && isFunction(symbol) == FALSE)
			return TRUE;
		else return ERR_VARIABLE;
	}
	else return isDefined;
}
