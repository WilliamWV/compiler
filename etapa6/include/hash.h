#ifndef HASH_H
#define HASH_H "hashh"
#include "lexVal.h"
#include "defines.h"
#include "tree.h"
#include "naming.h"


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
	int size;	  // necessário para poder mudar dinâmicamente quando for string
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
	char* userType;               // se for um tipo de usuário esse campo armazenará
                                  // o nome do tipo
                                  // De forma geral uma valor na tabela terá USER
                                  // em type em 2 casos:
                                  // 1) Declaração do tipo de usuário com class
                                  // 2) Declaração de variável de tipo de usuário
                                  // para diferenciar em 1 userType vai ser NULL
                                  // (pois mesma string estará em symbol) e vai
                                  // ser o nome do tipo em 2
	int isFunction;
	int flags;                    // flags do tipo static e const
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
	int offset;                   // deslocamento do endereço da variável em 
	                              // relação ao registrador de referência
	int sizeOfLocalVars;          // Usado apenas se o símbolo for uma função 
	                              // para indicar o tamanho de memória que deve
                                  // ser reservado para as variáveis locais
	char* label;                  // usado apenas se o símbolo for uma função
	                              // para indicar a primeira instrução dela 

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
int addSymbol(struct lexval* valor_lexico, int nature, int type, char* userType, int vecSize, int isFunction, int flags);

//adiciona um argumento a um símbolo
void addFuncArg(char* symbol, FuncArg* arg);

//adiciona um tipo de usuário a um símbolo
void addField(char* symbol, UserTypeField* utf);

//busca um determinado símbolo em toda a pilha de tabelas de símbolos, começando
//pela tabela do escopo atual, subindo até o escopo global
Hash* getSymbol(char* symbol);

int isDefined(char* symbol);

int symbolUse(char* symbol);

int errorOf(int symbUse);

int verifyUse(char* symbol, int expectedUse);

int hasField (char* symbol, char* field);

void printFields(char *symbol);

void printArgs(char *symbol);

int fieldType(char *identifier, char *field);

int identifierType(char *identifier);

void liberaTodasTabelas();

void setFieldSize(char* ut, char* field, int size, int vecSize);

int getStringExpressionSize(struct node* expression);

void updateStringSize(char* id, struct node* expression, int type, char* field);

int currentScopeLevel();

int scopeLevelOfID(char* id);

int identifierSize(char* indentifier);



////////////////////////////////////////////////////////////////////////////////
/// Adiciona operações ILOC a lista "l" para carregar valor da variável      ///
/// "varName" em um registrador cujo nome é retornado pela função            ///
///////////////////////////////////////////////////////////////////////////////

char* loadVarToRegister(ILOC_LIST* l, char* varName);
	
char* calculateAddressOfVar(ILOC_LIST* l, char* varName);
	
//Marca no RA o ponto onde começam as variáveis locais isso será somado com o RFP
//e com o deslocamento tas variáveis locais para acessá-las
int localVarBegin(char* function);

#endif
