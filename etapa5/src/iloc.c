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
