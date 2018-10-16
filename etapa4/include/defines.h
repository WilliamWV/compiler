#define NATUREZA_LITERAL_INT        1
#define NATUREZA_LITERAL_FLOAT      2
#define NATUREZA_LITERAL_CHAR       3
#define NATUREZA_LITERAL_STRING     4
#define NATUREZA_LITERAL_BOOL       5
#define NATUREZA_IDENTIFICADOR      6


#define ERR_UNDECLARED  100 //identificador não declarado
#define ERR_DECLARED    101 //identificador já declarado

/* Uso correto de identificadores */
#define ERR_VARIABLE    102 //identificador deve ser utilizado como variável
#define ERR_VECTOR      103 //identificador deve ser utilizado como vetor
#define ERR_FUNCTION    104 //identificador deve ser utilizado como função
#define ERR_USER        105 //identificador deve ser utilizado como de usuário

/* Tipos e tamanho de dados */
#define ERR_WRONG_TYPE  106 //tipos incompatíveis
#define ERR_STRING_TO_X 107 //coerção impossível de var do tipo string
#define ERR_CHAR_TO_X   108 //coerção impossível de var do tipo char
#define ERR_USER_TO_X   109 //coerção impossível de var do tipo de usuário

/* Argumentos e parâmetros */
#define ERR_MISSING_ARGS    110 //faltam argumentos 
#define ERR_EXCESS_ARGS     111 //sobram argumentos 
#define ERR_WRONG_TYPE_ARGS 112 //argumentos incompatíveis

/* Verificação de tipos em comandos */
#define ERR_WRONG_PAR_INPUT  113 //parâmetro não é identificador
#define ERR_WRONG_PAR_OUTPUT 114 //parâmetro não é literal string ou expressão
#define ERR_WRONG_PAR_RETURN 115 //parâmetro não é expressão compatível com tipo do retorno


#define HASH_SIZE 40009


//Flags para os símbolos
#define CONST 0x1
#define STATIC 0x2


//Tipo do token não é um tipo de dado, mas os tipos definidos pelo
//analisador léxico, ou seja:
// 1) Palavra reservada
// 2) Caracteres especiais
// 3) operadores compostos
// 4) Identificadores
// 5) Literais
// Portanto o tipo do token será representado por um inteiro que será um dos valores definidos a seguir.
/*******TIPOS DE TOKENS*******/
#define KEYWORD 0x0
#define SPEC_CHAR 0x1
#define COMP_OPER 0x2
#define IDS 0x3
#define LITERAL 0x4
/*******TIPOS DE LITERAIS*****/
#define INT 0X8
#define FLOAT 0x9
#define CHAR 0xA
#define BOOL 0XB
#define STRING 0XC
#define USER 0xD //adiciona tipo de usuário
#define VEC 0xE  //adiciona tipo vetor

/*Valor NONE é usado no campo para tipo do literal quando o token não é literal*/
#define NONE 0xF


//valores booleanos
#define FALSE 0
#define TRUE 1


//Definição dos modificadores de encapsulamento
#define PUBLIC_ENCAPS     0x10
#define PRIVATE_ENCAPS    0x11
#define PROTECTED_ENCAPS  0X12
#define NOT_DEFINED_ENCAPS 0X13


//Coercoes
#define FLOAT_TO_INT  1000
#define FLOAT_TO_BOOL 1001
#define INT_TO_FLOAT  1002
#define INT_TO_BOOL   1003
#define BOOL_TO_FLOAT 1004
#define BOOL_TO_INT   1005
