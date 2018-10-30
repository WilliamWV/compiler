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
		l->list = (ILOC_OP**)realloc(l->list, l->operations * sizeof(ILOC_OP*));
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
	oper->args = (ILOC_ARG**) realloc(oper->args, oper->argsNum * sizeof(ILOC_ARG*));
	oper->args[oper->argsNum - 1] = arg;
}
