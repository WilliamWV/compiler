#include "lexVal.h"

/* Reusa tipos de literais definidos em lexVal.h
#define INT 0X8
#define FLOAT 0x9
#define CHAR 0xA
#define BOOL 0XB
#define STRING 0XC
*/
#define USER 0xD //adiciona tipo de usuário
////////////////////////////////////////////////////////////////////////////////
/// FuncArg                                                                  ///
/// Estrutura usada para armazenar informações de um argumento de função, é  ///
/// necessária aqui pois o valor de um símbolo do tipo função, na hash,      ///
/// estará associado aos seus parâmetros formais                             ///
////////////////////////////////////////////////////////////////////////////////
typedef struct arg{
	int argType;      // tipo do argumento
	char* userType;   // se for um tipo de usuário esse campo possuirá o 
                      // identificador correspondente
	char* argName;    // nome do argumento
	bool isConst;     // argumento possui modificador const ou não
}FuncArg;

//Definição dos modificadores de encapsulamento
#define PUBLIC_ENCAPS     0x10
#define PRIVATE_ENCAPS    0x11
#define PROTECTED_ENCAPS  0X12
////////////////////////////////////////////////////////////////////////////////
/// UserTypeField                                                            ///
/// Estrutura usada para armazenar informações dos campos de um tipo de      ///
/// usuário, assim como a estrutura para argumentos de função, esta é        ///
/// opcional no valor do hash usada em um caso específico de símbolo         ///
////////////////////////////////////////////////////////////////////////////////
typedef struct utf{
	int fieldEncaps;  // modificador de encapsulamento do campo
	int fieldType;    // tipo do campo, como, não permite tipo de usuário, não 
                      // precisa de um campo userType como a estrutura anterior 
	char* fieldName;  // nome do campo
}UserTypeField;

////////////////////////////////////////////////////////////////////////////////
/// HashContent                                                              ///
/// Estrutura usada para armazenar informações dos símbolos da tabela de     ///
/// símbolos. Cada entrada da tabela de símbolos vai ter um valor do tipo    ///
/// dessa estrutura associado a si.                                          ///
////////////////////////////////////////////////////////////////////////////////
typedef struct hashContent{
	int line;                     // linha do símbolo
	int nature;                   // natureza, como definido em natureza.h
	int type;                     // tipo de dado do símbolo
	int size;                     // tamanho do símbolo derivado do tipo
	FuncArg* args;                // argumentos e seus tipos, se for função
	UserTypeField* userFields;    // campos e seus tipos, se for tipo de usuário
	struct lexval valor_lexico;   // valores associados ao yylval do símbolo
}Hash;

Hash* Table;

long createSymbol(struct lexval valor_lexico, int nature, int type);

void addFuncArg(long symbolKey, FuncArg* arg);

void addField(long symbolKey, UserTypeField* utf);

Hash getSymbol(long symbolKey);


