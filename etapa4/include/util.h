#include "../include/lexVal.h"
#include "../include/hash.h"

/**
	O objetivo desse arquivo, associado com o arquivo util.c, é fornecer funções
	úteis de forma geral pelo código, como criação de estruturas.
*/

struct lexval* createLexval(int lineNumber, int tokenType, int literType, void* value, bool tokenInAst);

FuncArg* createFuncArg(int argType, char* userType, char* argName, bool isConst);

UserTypeField* createUserTypeField(int fieldEncaps, int fieldType, char* fieldName);

