#include "../include/iloc.h"

ILOC_LIST* createILOCList ()
{
	ILOC_LIST* l = (ILOC_LIST*) aloca(sizeof(ILOC_LIST));
	l->operations = 0;
	l->list = NULL;
	return l;
}
void addILOCToList(ILOC_LIST* l, ILOC_OP* oper)
{
	l-> operations = l->operations + 1;
	if (l->operations == 1){ // aloca pela primeira vez
		l->list = (ILOC_OP**) aloca(sizeof(ILOC_OP*));
		l->list[0] = oper;
	}
	else{
		l->list = (ILOC_OP**)realoca(l->list, l->operations * sizeof(ILOC_OP*));
		l->list[l->operations-1] = oper;
	}
}
ILOC_LIST* concatILOC(ILOC_LIST* l1, ILOC_LIST* l2)
{
	ILOC_LIST* dest = createILOCList();
	for(int i = 0; i<l1->operations; i++){
		addILOCToList(dest, l1->list[i]);
	}
	for(int i = 0; i<l2->operations; i++){
		addILOCToList(dest, l2->list[i]);
	}
	return dest;
}

void addILOCArg(ILOC_OP* oper, ILOC_ARG* arg){
	oper->argsNum = oper->argsNum + 1;
	oper->args = (ILOC_ARG**) realoca(oper->args, oper->argsNum * sizeof(ILOC_ARG*));
	oper->args[oper->argsNum - 1] = arg;
}

ILOC_OP* createILOCOper(int opcode, char* opSpelling)
{
	ILOC_OP* ans = (ILOC_OP*) aloca (sizeof(ILOC_OP));
	ans->opcode = opcode;
	ans->opSpelling = opSpelling;
	ans->argsNum = 0;
	ans->args = NULL;
}

ILOC_ARG* createILOCArg(int argType, void* value)
{
	ILOC_ARG* ans = (ILOC_ARG*) aloca (sizeof(ILOC_ARG));
	ans->argType = argType;
	if(argType == IMED){
		ans->value.i = *((int*)value);
	}
	else{
		ans->value.str = (char*) value;	
	}
}

//cria uma estrutura de argumento para um argumento bem nomeado, ou seja, se for
//registrador o primeiro caractere é 'r', se for label o primeiro caractere é 'L'
//se não é um valor imediato constante inteiro
ILOC_ARG* wellFormedArg(void* arg){
	char* a = (char*) arg;
	if(a[0] == 'r') return createILOCArg(REG, arg);
	if(a[0] == 'L') return createILOCArg(LAB, arg);
	else return createILOCArg(IMED, arg);
}
void createOperation(ILOC_LIST* l, int opcode, char* opSpell, void* arg1, void* arg2, void* arg3){
	ILOC_OP* oper = createILOCOper(opcode, opSpell);
	if(arg1 != NULL){
		ILOC_ARG* a1 = wellFormedArg(arg1);
		addILOCArg(oper, a1);
	}
	if(arg2 != NULL){
		ILOC_ARG* a2 = wellFormedArg(arg2);
		addILOCArg(oper, a2);
	}
	if(arg3 != NULL){
		ILOC_ARG* a3 = wellFormedArg(arg3);
		addILOCArg(oper, a3);
	}
	addILOCToList(l, oper);
}

void addNewLabel(Labels *list, char *label){
	list->numberOfLabels = list->numberOfLabels + 1;
	list->labels = (char**)realoca(list->labels, list->numberOfLabels * sizeof(char*));
	list->labels[list->numberOfLabels - 1] = label;
}

void concatenateLabelsList(Labels *list1, Labels *list2){
	for(int i = 0; i < list2->numberOfLabels; i++){
		addNewLabel(list1, list2->labels[i]);
	}
}

void printListOfOperations(ILOC_LIST *listOp){
	for(int i = 0; i< listOp->operations; i++){
		printOperation(listOp->list[i]);
	}
}

void printOperation(ILOC_OP *oper){
	
	printf("%s\t", oper->opSpelling);
	if(oper->opcode == CBR || oper->opcode == SUB || oper->opcode == ADD || oper->opcode == DIV)
		printf("\t");
	int opType = operationSpellType(oper->opcode);
	switch(opType){
		case TWO_EQ_ONE:
			if(oper->argsNum == 3){
				printArg(oper->args[0]);
				printf(", ");
				printArg(oper->args[1]);
				printf(" => ");
				printArg(oper->args[2]);
			} 
			else printf("Operação %s com quantidade de argumentos incorreta", oper->opSpelling);
		break;     
		case ONE_EQ_ONE: 
			if(oper->argsNum == 2){
				printArg(oper->args[0]);
				printf(" => ");
				printArg(oper->args[1]);
			} 
			else printf("Operação %s com quantidade de argumentos incorreta", oper->opSpelling);
		break;          
		case ONE_EQ_TWO:
			if(oper->argsNum == 3){
				printArg(oper->args[0]);
				printf(" => ");
				printArg(oper->args[1]);
				printf(", ");
				printArg(oper->args[2]);
			} 
			else printf("Operação %s com quantidade de argumentos incorreta", oper->opSpelling);
		break;           
		case ZERO_MINUS_ONE:
			if(oper->argsNum == 1){
				printf(" -> ");
				printArg(oper->args[0]);
			} 
			else printf("Operação %s com quantidade de argumentos incorreta", oper->opSpelling);
		break;    
		case ONE_MINUS_ONE:
			if(oper->argsNum == 1){
				printf(" -> ");
				printArg(oper->args[0]);
			} 
			else printf("Operação %s com quantidade de argumentos incorreta", oper->opSpelling);
		break;    
		case ONE_MINUS_TWO:
			if(oper->argsNum == 3){
				printArg(oper->args[0]);
				printf(" -> ");
				printArg(oper->args[1]);
				printf(", ");				
				printArg(oper->args[2]);
			} 
			else printf("Operação %s com quantidade de argumentos incorreta", oper->opSpelling);
		break;        
		case TWO_MINUS_ONE:  
			if(oper->argsNum == 3){
				printArg(oper->args[0]);
				printf(", ");
				printArg(oper->args[1]);
				printf(" -> ");
				printArg(oper->args[2]);
			} 
			else printf("Operação %s com quantidade de argumentos incorreta", oper->opSpelling);
		break;      
	}
	printf("\n");
}
int operationSpellType(int opcode){
	switch (opcode){
		case ADD:
		case SUB:
		case MULT:
		case DIV:
		case ADDI:
		case SUBI:
		case RSUBI:
		case MULTI:
		case DIVI:
		case RDIVI:
		case LSHIFT:
		case LSHIFTI:
		case RSHIFT:
		case RSHIFTI:
		case AND:
		case ANDI:
		case OR:
		case ORI:
		case XOR:
		case XORI:
		case LOADAI:
		case LOADA0:
		case CLOADAI:
		case CLOADA0:
			return TWO_EQ_ONE;
		case LOADI:
		case LOAD:
		case CLOAD:
		case STORE:
		case CSTORE:
		case I2I:
		case C2C:
		case C2I:
		case I2C:
			return ONE_EQ_ONE;
		case STOREAI:
		case STOREA0:
		case CSTOREAI:
		case CSTOREA0:
			return ONE_EQ_TWO; 
		case JUMPI:
			return ONE_MINUS_ONE;
		case JUMP:
			return ZERO_MINUS_ONE;
		case CBR:
			return ONE_MINUS_TWO;
		case CMP_LT:
		case CMP_LE:
		case CMP_EQ:
		case CMP_GE:
		case CMP_GT:
		case CMP_NE:
			return TWO_MINUS_ONE;
		default: return NOP;
	}
}

void printArg(ILOC_ARG* arg){
	if(arg->argType == IMED)
		printf("%d",arg->value.i);
	else
		printf("%s", arg->value.str);
}

void substituteLabels(char *newLabel, char *targetLabel, ILOC_OP *oper){
	for(int i = 0; i < oper->argsNum; i++){
		if(oper->args[i]->argType == LAB){
			if(strcmp(oper->args[i]->value.str, targetLabel) == 0){
				oper->args[i]->value.str = newLabel;
			}
		}
	}
}

void patch(ILOC_LIST *listOp, char *newLabel, Labels *targetedLabels){
	for(int i = 0; i < targetedLabels->numberOfLabels; i++){
		for(int j = 0; j < listOp->operations; j++){
			substituteLabels(newLabel, targetedLabels->labels[i], listOp->list[j]);
		}
	}
}

void printLabels(Labels *list){
	printf("Labels da lista atual:\n\t");
	for(int i = 0; i < list->numberOfLabels; i++){
		printf("%s ", list->labels[i]);
	}
	printf("\n");
}

