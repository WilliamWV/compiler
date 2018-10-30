#include "../include/util.h"

struct lexval* createLexval(int lineNumber, int tokenType, int literType, void* value, bool tokenInAst){
	struct lexval* lv = (struct lexval*)malloc(sizeof(struct lexval));
	lv->tokenInAst = tokenInAst;
	lv->lineNumber = lineNumber;
	lv->tokenType = tokenType;
	lv->literType = literType;
	switch(literType){
		case INT: lv->value.i = *((int*)value); break;
		case FLOAT: lv->value.f = *((float*)value); break;
		case CHAR: lv->value.c = *((char*)value); break;
		case BOOL: lv->value.b = *((bool*)value); break;
		case STRING:
		case NONE: lv->value.str = (char*)value;break;
	}
	return lv;
}

FuncArg* createFuncArg(int argType, char* userType, char* argName, bool isConst){
	FuncArg* fa = (FuncArg*)malloc(sizeof(FuncArg));
	fa->argType = argType;
	fa->userType = userType;
	fa->argName = argName;
	fa->isConst = isConst;
	return fa;
}
UserTypeField* createUserTypeField(int fieldEncaps, int fieldType, char* fieldName){
	UserTypeField* utf = (UserTypeField*)malloc(sizeof(UserTypeField));
	utf->fieldEncaps = fieldEncaps;
	utf->fieldType = fieldType;
	utf->fieldName = fieldName;
	return utf;
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
