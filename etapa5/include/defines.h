//valores booleanos
#define FALSE 0
#define TRUE 1


#define NATUREZA_LITERAL_INT        1
#define NATUREZA_LITERAL_FLOAT      2
#define NATUREZA_LITERAL_CHAR       3
#define NATUREZA_LITERAL_STRING     4
#define NATUREZA_LITERAL_BOOL       5
#define NATUREZA_IDENTIFICADOR      6


#define ERR_UNDECLARED  10 //identificador não declarado
#define ERR_DECLARED    11 //identificador já declarado

/* Uso correto de identificadores */
#define ERR_VARIABLE    20 //identificador deve ser utilizado como variável
#define ERR_VECTOR      21 //identificador deve ser utilizado como vetor
#define ERR_FUNCTION    22 //identificador deve ser utilizado como função
#define ERR_USER        23 //identificador deve ser utilizado como de usuário

/* Tipos e tamanho de dados */
#define ERR_WRONG_TYPE  30 //tipos incompatíveis
#define ERR_STRING_TO_X 31 //coerção impossível de var do tipo string
#define ERR_CHAR_TO_X   32 //coerção impossível de var do tipo char
#define ERR_USER_TO_X   33 //coerção impossível de var do tipo de usuário

/* Argumentos e parâmetros */
#define ERR_MISSING_ARGS    40 //faltam argumentos 
#define ERR_EXCESS_ARGS     41 //sobram argumentos 
#define ERR_WRONG_TYPE_ARGS 42 //argumentos incompatíveis

/* Verificação de tipos em comandos */
#define ERR_WRONG_PAR_INPUT  50 //parâmetro não é identificador
#define ERR_WRONG_PAR_OUTPUT 51 //parâmetro não é literal string ou expressão
#define ERR_WRONG_PAR_RETURN 52 //parâmetro não é expressão compatível com tipo do retorno


#define HASH_SIZE 40009


//Tipo do token não é um tipo de dado, mas os tipos definidos pelo
//analisador léxico, ou seja:
// 1) Palavra reservada
// 2) Caracteres especiais
// 3) operadores compostos
// 4) Identificadores
// 5) Literais
// Portanto o tipo do token será representado por um inteiro que será um dos valores definidos a seguir.
/*******TIPOS DE TOKENS*******/
#define KEYWORD 300
#define SPEC_CHAR 301
#define COMP_OPER 302
#define IDS 303
#define LITERAL 304
/*******TIPOS DE LITERAIS*****/
#define INT 305
#define FLOAT 306
#define CHAR 307
#define BOOL 308
#define STRING 309
#define USER 310 //adiciona tipo de usuário
#define VEC 311  //adiciona tipo vetor

/*Valor NONE é usado no campo para tipo do literal quando o token não é literal*/
#define NONE 312


//Definição dos modificadores de encapsulamento
#define PUBLIC_ENCAPS     410
#define PRIVATE_ENCAPS    411
#define PROTECTED_ENCAPS  412
#define NOT_DEFINED_ENCAPS 413


//Flags para os símbolos
#define CONST 500
#define STATIC 501


//Coercoes
#define FLOAT_TO_INT  1000
#define FLOAT_TO_BOOL 1001
#define INT_TO_FLOAT  1002
#define INT_TO_BOOL   1003
#define BOOL_TO_FLOAT 1004
#define BOOL_TO_INT   1005

//mudança dinâmica de tamanho
#define IDENT    800
#define VECTOR   801
#define USR      802
#define VEC_USR  803

//Uso correto dos identificadores:
#define VAR 600 //variável
#define VET 601 //vetor
#define FUN 602 //função
#define UTN 603 //nome de tipo de usuário
#define UTV 604 // variável de tipo de usuário


//Tipos de argumento de operações ILOC
#define IMED 700   // valor constante imediato
#define REG  701   // registrador
#define LAB  702   // rótulos

/////////////////////////////
///OPCODE de operaçõs ILOC///
/////////////////////////////

//Aritmética 0x10xx

#define ADD        0x1000
#define SUB        0x1001
#define MULT       0x1002
#define DIV        0x1003
#define ADDI       0x1004
#define SUBI       0x1005
#define RSUBI      0x1006
#define MULTI      0x1007
#define DIVI       0x1008
#define RDIVI      0x1009

//Shifts 0x11xx
#define LSHIFT     0x1100
#define LSHIFTI    0x1101
#define RSHIFT     0x1102
#define RSHIFTI    0x1103

//Operações sobre a memória 0x12xx
#define LOAD       0x1200
#define LOADAI     0x1201
#define LOADA0     0x1203
#define CLOAD      0x1204
#define CLOADAI    0x1205
#define CLOADA0    0x1206
#define LOADI      0x1207
#define STORE      0x1208
#define STOREAI    0x1209
#define STOREA0    0x120A
#define CSTORE     0x120B
#define CSTOREAI   0x120C
#define CSTOREA0   0x120D

//Operações de Cópia entre registradores 0x13xx
#define I2I        0x1300
#define C2C        0x1301
#define C2I        0x1302
#define I2C        0x1303

//Operações de fluxo de controle 0x14xx
#define CMP_LT     0x1400
#define CMP_LE     0x1401
#define CMP_EQ     0x1402
#define CMP_GE     0x1403
#define CMP_GT     0x1404
#define CMP_NE     0x1405
#define CBR        0x1406

//Saltos 0x15xx
#define JUMPI      0x1500
#define JUMP       0x1501

//Operações booleanas 0x16xx
#define AND        0x1600
#define ANDI       0x1601
#define OR         0x1602
#define ORI        0x1603
#define XOR        0x1604
#define XORI       0x1605
//NOP 0x1700
#define NOP        0x1700



