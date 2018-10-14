#include "lexVal.h"
#include "errors.h"

#define HASH_SIZE 40009
/* Reusa tipos de literais definidos em lexVal.h
#define INT 0X8
#define FLOAT 0x9
#define CHAR 0xA
#define BOOL 0XB
#define STRING 0XC
*/
#define USER 0xD //adiciona tipo de usuário
#define VEC 0xE  //adiciona tipo vetor
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
	char* symbol;                 // string que identifica o símbolo, útil para
                                  // determinar se é o símbolo desejado ou outro
                                  // com mesmo valor na hash
	int line;                     // linha do símbolo
	int nature;                   // natureza, como definido em natureza.h
	int type;                     // tipo de dado do símbolo
	int isFunction;
	int size;                     // tamanho do símbolo derivado do tipo
	int vecSize;				  // valor que será 0 se o símbolo não for um
                                  // vetor e o tamanho do vetor caso contrário
                                  // OBS: foi escolhido não usar 1 para poder
                                  // diferenciar de um vetor com 1 elemento
	int argsNum;	              // quantidade de argumentos na função
	FuncArg** args;               // argumentos e seus tipos, se for função
	int fieldsNum;                // quantidade de campos no tipo de usuário
	UserTypeField** fields;       // campos e seus tipos, se for tipo de usuário
	struct lexval* valor_lexico;  // valores associados ao yylval do símbolo
}Hash;

////////////////////////////////////////////////////////////////////////////////
/// HashStack                                                                ///
/// pilha de tabela de símbolos, implementada como uma lista simplesmente    ///
/// encadeada de tabelas de símbolos.                                        ///
////////////////////////////////////////////////////////////////////////////////

typedef struct hashStack{
	Hash** currentTable;
	struct hashStack* next;
}HashStack;

//adiciona nova tabela de símbolos ao topo da pilha, útil quando se inicializa 
//um novo escopo.                                               
void initTable();

//remove uma tabela do tipo da pilha, útil quando um escopo está sendo fechado.
void closeTable();


//adiciona um novo símbolo à tabela de símbolos do topo da pilha, será recebido 
//o valor léxico do símbolo, a sua natureza e o seu tipo. A linha está presente
//no valor léxico, e o tamanho é inferido a partid do tipo. Se o símbolo for uma
//função, os argumentos devem ser adicionados usando addFuncArg. Se for um tipo
//de usuário, os campos devem ser adicionados usando addField.
int addSymbol(struct lexval* valor_lexico, int nature, int type, int vecSize, int isFunction);

//adiciona um argumento a um símbolo
void addFuncArg(char* symbol, FuncArg* arg);

//adiciona um tipo de usuário a um símbolo
void addField(char* symbol, UserTypeField* utf);

//busca um determinado símbolo em toda a pilha de tabelas de símbolos, começando
//pela tabela do escopo atual, subindo até o escopo global
Hash* getSymbol(char* symbol);


int isVariable(char *symbol);

int isVector(char *symbol);

int isFunction(char *symbol);

int isDefined(char *symbol);



