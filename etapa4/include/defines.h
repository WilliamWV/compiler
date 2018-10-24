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
#define IDENT    2000
#define VECTOR   2001
#define USR      2002
#define VEC_USR  2003

//Uso correto dos identificadores:
#define VAR 600 //variável
#define VET 601 //vetor
#define FUN 602 //função
#define UTN 603 //nome de tipo de usuário
#define UTV 604 // variável de tipo de usuário

