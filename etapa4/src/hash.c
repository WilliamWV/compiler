#include "../include/hash.h"

HashStack* tabelas = NULL;

int sizeOfType(int type){
	switch(type){
		case CHAR: return 1; break;
		case STRING: return 1; break; //1 para cada caractere
		case INT: return 4; break;
		case FLOAT: return 8; break;
		case BOOL: return 1; break;
		case USER: return 0; break; // deve ser somado ao valor de cada campo conforme os campos são adicionados
		//TODO: precisa adicionar suporte a vetor
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

//libera memória de todos os símbolos presentes na tabela do topo da pilha
void freeTable(){
	
	if(tabelas->currentTable != NULL){

		int tableIndex;
		for(tableIndex = 0; tableIndex<HASH_SIZE; tableIndex++){
			if(tabelas->currentTable[tableIndex]!=NULL){
				free(tabelas->currentTable[tableIndex]);
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
void addSymbol(struct lexval* valor_lexico, int nature, int type){
	
	int hashIndex = hashFunction(valor_lexico->value.str);
	tabelas->currentTable[hashIndex] = (Hash*)malloc(sizeof(Hash));
	tabelas->currentTable[hashIndex]->line = valor_lexico->lineNumber;
	tabelas->currentTable[hashIndex]->nature = nature;
	tabelas->currentTable[hashIndex]->type = type;
	tabelas->currentTable[hashIndex]->size = sizeOfType(type);
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
		symbolContent->size = symbolContent->size + sizeOfType(utf->fieldType);
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
