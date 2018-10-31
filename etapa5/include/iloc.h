#ifndef ILOC
#define ILOC 2
#include "lexVal.h" //útil para union Value
#include "everybodyHateLeaks.h"
////////////////////////////////////////////////////////////////////////////////
/// Possui definições de estruturas para operações ILOC bem como da lista    ///
/// dessas operações. Também possui definição de funções que serão úteis     ///
/// na geração de código.                                                    ///
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// DEFINIÇÃO DE ESTRUTURAS                                                  ///
////////////////////////////////////////////////////////////////////////////////

//Argumento de operações ILOC
typedef struct ilocArg{
	int argType;         // diferenciar nnome de registrador, valores constantes 
                         // e nomes de rótulos       
	union Value value;   // estrutura definida em lexval.h. Possuirá o valor do 
                         // argumento, devido a simplificação da linguagem os
                         // únicos valores da union que vão acabar sendo usados
                         // serão o 'str' (no caso de nome de registrador ou de 
                         // rótulo) ou o 'i' no caso de valor constante que será
                         // inteira.
} ILOC_ARG;

//operação ILOC
typedef struct ilocOper{
	int opcode;            // Útil para comparar facilmente um identificador da
                           // operação ILOC
	char* opSpelling;      // Útil quando o código for gerado para não precisar
                           // de um grande switch case com itens para cada 
                           // operação ILOC
	int argsNum;           // quantidade de argumentos
	ILOC_ARG** args;       // lista de argumentos da operação
	
} ILOC_OP;

//lista de operações iloc
typedef struct ilocList{
	ILOC_OP** list;       // estrutura das operações ILOC
	int operations;       // quantidade de operações ILOC nessa lista
} ILOC_LIST;



////////////////////////////////////////////////////////////////////////////////
/// DEFINIÇÃO DE FUNÇÕES                                                     ///
/// Funções necessárias:                                                     ///
///   * criar lista vazia de operações                                       ///
///   * adicionar operações ao final de uma lista                            ///
///   * concatenar listas de operações                                       ///
///   * adicionar argumentos à operação
////////////////////////////////////////////////////////////////////////////////

//Funçõe Básicas
ILOC_LIST* createILOCList ();
void addILOCToList(ILOC_LIST* l, ILOC_OP* oper);
ILOC_LIST* concatILOC(ILOC_LIST* l1, ILOC_LIST* l2);
void addILOCArg(ILOC_OP* oper, ILOC_ARG* arg);

//Função extra
////////////////////////////////////////////////////////////////////////////////
/// Função criada para diminuir quantidade de código necessário para         ///
/// adicionar uma operação a uma lista, essa função recebe informações       ///
/// necessárias para criar uma operação, criar seus argumentos e adicionar a ///
/// operação em uma lista de operações                                       ///
/// considera que uma operação tem no máximo três argumentos e que os        ///
/// argumentos obedecem as convenções de nomeação, se existem menos de três  ///
/// argumentos na operação basta deixar os que sobram NULL
////////////////////////////////////////////////////////////////////////////////
void createOperation(ILOC_LIST* l, int opcode, char* opSpell, void* arg1, void* arg2, void* arg3);

//Funções auxiliares
ILOC_OP* createILOCOper(int opcode, char* opSpelling);
ILOC_ARG* createILOCArg(int argType, void* value);
#endif
