#include "../include/hash.h"
#include <stdio.h>


HashStack* tabelas = NULL;

extern char *currentFunc;

//int localOffset = 0;
int globalOffset = 0;


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
	while(c = *symbol++){
		hash = ((hash<<5) + hash) + c;
	}
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
			//free(tabelas->currentTable[index]->args[i]->arg);
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

void printArgs(char *symbol){
	Hash *symbolContent = getSymbol(symbol);
	if (symbolContent!=NULL){
		int i; 
		for(i = 0; i < symbolContent->argsNum; i++){
			printf("Nome do argumento: %s  ", symbolContent->args[i]->argName);
			if(symbolContent->args[i]->isConst == FALSE)
				printf("Const: false  ");
			else printf("Const: true  ");
			switch(symbolContent->args[i]->argType)
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
					printf("Tipo: user (%s)\n", symbolContent->args[i]->userType);
					break;
			}
		}
	}
}

int fieldType(char *identifier, char *field){
	Hash *symbolContent = getSymbol(identifier);
	symbolContent = getSymbol(symbolContent->userType);
	if (symbolContent!=NULL){
		int i;
		for(i = 0; i < symbolContent->fieldsNum; i++){
			if(strcmp(symbolContent->fields[i]->fieldName, field) == 0)
				return symbolContent->fields[i]->fieldType;
		}
	}
	return -1; // field nao encontrado
}

int identifierType(char *identifier){
	Hash *symbolContent = getSymbol(identifier);
	if (symbolContent!=NULL){
		return symbolContent->type;
	}
	return -1; // field nao encontrado
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
					if(tabelas->currentTable[tableIndex]->userType!=NULL)
						free(tabelas->currentTable[tableIndex]->userType);
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
	
	if (verifyUse(valor_lexico->value.str, UTN) == TRUE) return ERR_DECLARED;

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
	tabelas->currentTable[hashIndex]->isFunction = isFunction;
	tabelas->currentTable[hashIndex]->hasReturn = FALSE;
	tabelas->currentTable[hashIndex]->hasReturnOutsideOfIf = FALSE;
	tabelas->currentTable[hashIndex]->flags = flags;
	tabelas->currentTable[hashIndex]->size = sizeOfType(type, vecSize);
	if (userType == NULL)
		tabelas->currentTable[hashIndex]->userType = NULL;
	else{ 
		tabelas->currentTable[hashIndex]->userType = (char*) malloc(sizeof(char) * (strlen(userType) + 1));
		strcpy(tabelas->currentTable[hashIndex]->userType, userType);	
		Hash* usrType = getSymbol(userType);		
		tabelas->currentTable[hashIndex]->size = usrType->size;	
	}
	tabelas->currentTable[hashIndex]->vecSize = vecSize;
	tabelas->currentTable[hashIndex]->argsNum = 0;
	tabelas->currentTable[hashIndex]->argsSize = 0;
	tabelas->currentTable[hashIndex]->fieldsNum = 0;
	tabelas->currentTable[hashIndex]->args = (FuncArg**)malloc(sizeof(FuncArg*));
	tabelas->currentTable[hashIndex]->registers = (Registers*)aloca(sizeof(FuncArg));
	tabelas->currentTable[hashIndex]->registers->registers = (char**)aloca(sizeof(FuncArg*));
	tabelas->currentTable[hashIndex]->registers->numberOfRegs = 0;
	tabelas->currentTable[hashIndex]->fields = (UserTypeField**)malloc(sizeof(UserTypeField*));
	tabelas->currentTable[hashIndex]->valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	*(tabelas->currentTable[hashIndex]->valor_lexico) = *(valor_lexico);
	int scopeLevel = currentScopeLevel();	
	if(scopeLevel == 0){ // variável global
		tabelas->currentTable[hashIndex]->offset = globalOffset;
		globalOffset+=tabelas->currentTable[hashIndex]->size;
		
	}
	else{ // variável loval
		Hash* func = getSymbol(currentFunc);
		tabelas->currentTable[hashIndex]->offset = func->localOffset;
		func->localOffset+=tabelas->currentTable[hashIndex]->size;
	}
	tabelas->currentTable[hashIndex]->sizeOfLocalVars = 0;
	if(isFunction == TRUE){
		tabelas->currentTable[hashIndex]->label = getNewLabel();
		// o valor de retorno é a soma de:
		// 1) Endereço de retorno -> tamanho 4
		// 2) rsp e rfp -> tamanho 8
		// 3) vínculo estático -> tamanho 4
		// 4) valor de retorno -> tamanho 4
		if (strcmp(tabelas->currentTable[hashIndex]->symbol, "main") == 0){
			tabelas->currentTable[hashIndex]->localOffset = 0;
		}else{
			tabelas->currentTable[hashIndex]->localOffset = 4 + 8 + 4 + 4;
		}
	}
	else{		
		tabelas->currentTable[hashIndex]->label = NULL;
		tabelas->currentTable[hashIndex]->localOffset = 0;
	}
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
		symbolContent->localOffset = symbolContent->localOffset + 4;
		int currentArgOffset;
		
		if (symbolContent->argsNum >= 1){
			Hash* arg = getSymbol(symbolContent->args[0]->argName);
			currentArgOffset = arg->offset;	
		}		
		for (int i = 0; i <symbolContent->argsNum; i++){
			Hash* arg = getSymbol(symbolContent->args[i]->argName);
			arg->offset = currentArgOffset+4;
			currentArgOffset = arg->offset;
		}
	}
}
//adiciona um campo tipo de usuário a um símbolo
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
		symbolContent->size = symbolContent->size + utf->size;
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

int symbolUse(char* symbol){
	Hash* symbolContent = getSymbol(symbol);
	
	if(symbolContent != NULL){
		if (symbolContent->isFunction) return FUN;
		if (symbolContent->vecSize > 0) return VET;
		if (symbolContent->type == USER){
			if(symbolContent->userType == NULL) return UTN;
			else return UTV;	
		}
		return VAR;
	}
	else return ERR_UNDECLARED;
}

int errorOf(int symbUse){
	switch(symbUse){
		case VAR: return ERR_VARIABLE;
		case VET: return ERR_VECTOR;
		case FUN: return ERR_FUNCTION;
		case UTN: return ERR_USER;
		case UTV: return ERR_USER_TO_X;
	}
}

int verifyUse(char* symbol, int expectedUse){
	int defined = isDefined(symbol);
	if(defined == 0){
		int symbUse = symbolUse(symbol);
		if(symbUse==expectedUse) return TRUE;
		else return errorOf(symbUse);
	}
	else return defined;
}

int hasField (char* symbol, char* field){
	int isUT = verifyUse(symbol, UTV);
	if(isUT == TRUE){
		//símbolo da variável de tipo de usuário
		Hash* varSymbolContent = getSymbol(symbol);
		//símbolo do identificador do tipo de usuário
		Hash* typeSymbolContent = getSymbol(varSymbolContent->userType);
		int i;
		for(i = 0; i<typeSymbolContent->fieldsNum; i++){
			if (strcmp(typeSymbolContent->fields[i]->fieldName, field) == 0) return TRUE;
		}
		return ERR_USER;
	}
	else return isUT;
}

void liberaTodasTabelas(){
	while(tabelas!=NULL){
		closeTable();
	}
}

int getFieldSize(char* ut, char* field){
	Hash* usr = getSymbol(ut);
	Hash* usrType = getSymbol(usr->userType);
	for(int i = 0; i<usrType->fieldsNum; i++){
		if(strcmp(usrType->fields[i]->fieldName, field) == 0){
			return usrType->fields[i]->size;			
		}
	}
	return 0;
}

void setFieldSize(char* ut, char* field, int size, int vecSize){
	Hash* usr = getSymbol(ut);
	Hash* usrType = getSymbol(usr->userType);
	for(int i = 0; i<usrType->fieldsNum; i++){
		if(strcmp(usrType->fields[i]->fieldName, field) == 0){
			if(size> usrType->fields[i]->size){
				usrType->size = usrType->size + size - usrType->fields[i]->size;			
				usrType->fields[i]->size = size;
				usr->size = usrType->size * vecSize;
			}
		}
	}
}

int getStringExpressionSize(struct node* expression){
	//expression pode ser:
	// 1) Identificador
	// 2) Literal
	// 3) elemento de vetor
	// 4) campo de tipo de usuário
	// 5) campo de um elemento de um vetor de tipo de usuário
	if(expression->token != NULL){
		
			
		if (expression->token->tokenType == LITERAL){//literal
			return strlen(expression->token->value.str) - 2; 
		}
		else if(expression->kidsNumber==0){//identificador
			Hash* expSymb = getSymbol(expression->token->value.str);		
			return expSymb->size;
		}
		else if(expression->kidsNumber==3 &&
			expression->kids[0]->token->tokenType == SPEC_CHAR &&
			expression->kids[0]->token->value.c == '$'){//elemento de vetor
			printf("Entrou\n");
			Hash* expSymb = getSymbol(expression->token->value.str);
			if(expSymb->vecSize > 0)
				return expSymb->size /expSymb->vecSize; 
		}
		else if(expression->kidsNumber==2 && 
			expression->kids[0]->token->tokenType == SPEC_CHAR &&
			expression->kids[0]->token->value.c == '$')
		{//campo de tipo de usuário
			return getFieldSize(expression->token->value.str, expression->kids[1]->token->value.str);
		}
		else if(expression->kidsNumber==5){//campo de um elemento de um vetor de tipo de usuário
			return getFieldSize(expression->token->value.str, expression->kids[4]->token->value.str);			
		}
	}
	else{
		//expressão com nodo nulo
		return -1;
	}
}

void updateStringSize(char* id, struct node* expression, int type, char* field){
	
	Hash* idSymb = getSymbol(id);	
	int size;
	switch(type){
		case IDENT: 
		 	size = getStringExpressionSize(expression);
			if(size >= 0){
				idSymb->size = size;
			}
			break;
		case VECTOR:
			if(idSymb->vecSize>0){
				int currentSize = idSymb->size/idSymb->vecSize;
				int expSize = getStringExpressionSize(expression);
				if(currentSize < expSize){
					idSymb->size = expSize * idSymb->vecSize;
				}
			}
			break;
		case USR:
			setFieldSize(id, field, getStringExpressionSize(expression), 1);
			break;
		case VEC_USR:
			setFieldSize(id, field, getStringExpressionSize(expression), idSymb->vecSize);
		break;
	}
	//printf("Size of \'%s\' = %d\n", id, idSymb->size);
	
}

// o nível de escopo depende de quantas tabelas estão empilhadas
// quando se chega na base da pilha tem-se que tabelas->next = NULL
int currentScopeLevel(){
	int scopeLevel = 0;
	if (tabelas==NULL) return 0;
	HashStack* aux = tabelas;
	while (aux->next != NULL){
		scopeLevel++;
		aux = aux->next;
	}
	return scopeLevel;
}

// Função semelhante a getSymbol, mas retorna o nível do escopod e um identificador
// onde 0 é escopo global, 1 é o primeiro escopo sobre o global e assim por diante

int scopeLevelOfID(char* id){
	int hashIndex = hashFunction(id);
	int tempIndex = hashIndex; // será usado se for necessário buscar símbolo em caso
                               // de colisão
	Hash* symbolContent;
	HashStack* aux = tabelas;
	int scope = currentScopeLevel();
	do{	
		symbolContent = aux->currentTable[hashIndex];
		while(symbolContent != NULL){	
			if(strcmp(symbolContent->symbol, id) == 0)
				return scope;
			else{
				tempIndex++;
				symbolContent = aux->currentTable[tempIndex];
			}
		}
		aux = aux->next;
		tempIndex = hashIndex;
		scope--;
	}while(aux!=NULL);

	return -1; // retorna -1 se não existir, NOTA: isso nunca deve ser executado pois
	           // a análise semântica deve detectar esse erro e a geração de código
	           // não seria iniciada
}

char* calculateAddressOfVar(ILOC_LIST* l, char* varName){
	Hash* varContent = getSymbol(varName);	
	if(varContent!=NULL){	
		int offset = varContent->offset;
		int varScopeLevel = scopeLevelOfID(varName);
		char* address = getNewRegister(); // registrador que vai conter o endereço final
		if(varScopeLevel == 0){ // global - usa registrador rbss
			createOperation(l, ADDI, "addI", "rbss", (void*) &offset, address, ARG2_IMED);
		}
		else{//local - usa registrador rfp
			createOperation(l, ADDI, "addI", "rfp", (void*) &offset, address, ARG2_IMED);
		}
		
		return address;
	}
	else return NULL; // nunca deve ocorrer pois esse erro deve ser percebido pela
					  // análise semântica
}

// O carregamento de uma variável é feito nos seguintes passos:
// 1 - Cálcula endereço da variável
// 		1.1 - Determina qual o escopo da variável para saber o registrador de referência
//		1.2 - Cria uma operação de addi do registrador de referência com o deslocamento
//		      da variável em relação a esse registrador salvando o resultado em um 
//		      novo registrador
// 2 - Cria uma instrução de load para carregar o endereço da variável em um registrador
//
char* loadVarToRegister(ILOC_LIST* l, char* varName){
	Hash* varContent = getSymbol(varName);	
	if(varContent!=NULL){	
		int offset = varContent->offset;
		int varScopeLevel = scopeLevelOfID(varName);
		char* address = getNewRegister(); // registrador que vai conter o endereço final
		if(varScopeLevel == 0){ // global - usa registrador rbss
			createOperation(l, ADDI, "addI", "rbss", (void*) &offset, address, ARG2_IMED);
		}
		else{//local - usa registrador rfp
			createOperation(l, ADDI, "addI", "rfp", (void*) &offset, address, ARG2_IMED);
		}
		char* finalReg = getNewRegister();
		createOperation(l, LOAD, "load", address, NULL, finalReg, 0);
		return finalReg;
	}
	else return NULL; // nunca deve ocorrer pois esse erro deve ser percebido pela
					  // análise semântica
}

int identifierSize(char* id){
	Hash* idContent = getSymbol(id);
	if(id != NULL){
		return idContent->size;
	}else return 0; //nunca deve ocorrer pois esse erro deve ser percebido pela 
	                // análise semântica
}

int localVarBegin(char* function){
	Hash* func = getSymbol(function);
	if(func->isFunction == TRUE){
		// o valor de retorno é a soma de:
		// 1) Endereço de retorno -> tamanho 4
		// 2) rsp e rfp -> tamanho 8
		// 3) vínculo estático -> tamanho 4
		// 4) parâmetros : pela simplificação da etapa5 são todos inteiros portanto
		//    tem tamanho 4 * quantidade de parâmetros
		// 5) valor de retorno
		return 4 + 8 + 4 + 4 * func->argsNum + 4;
	}
	else return 0;
}

