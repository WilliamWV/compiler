#include "lexVal.h"
#include "hash.h"
#include "iloc.h"
#include "everybodyHateLeaks.h"
#include "defines.h"

/**
	O objetivo desse arquivo, associado com o arquivo util.c, é fornecer funções
	úteis de forma geral pelo código, como criação de estruturas.
*/

struct lexval* createLexval(int lineNumber, int tokenType, int literType, void* value, bool tokenInAst);

FuncArg* createFuncArg(int argType, char* userType, char* argName, bool isConst);

UserTypeField* createUserTypeField(int fieldEncaps, int fieldType, char* fieldName);

ILOC_OP* createILOCOper(int opcode, char* opSpelling);

ILOC_ARG* createILOCArg(int argType, void* value);

void printILOCArg(ILOC_ARG* arg);

void printILOCOper(ILOC_OP* op);

void printILOCList(ILOC_LIST* l);


