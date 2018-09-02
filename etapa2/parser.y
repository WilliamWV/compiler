%{
#include <stdio.h>
int yylex(void);
void yyerror (char const *s){
	printf("%s\n", s);
}
%}
%verbose
%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_OC_FORWARD_PIPE
%token TK_OC_BASH_PIPE
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO
%start programa


%%

programa: %empty | componente programa;
componente: 
	  novoTipo 
	| TK_IDENTIFICADOR depoisDeIdent // Regra introduzida para resolver conflitos 
	// Funções
	| tiposPrimitivos TK_IDENTIFICADOR argsAndCommands
	| TK_PR_STATIC tipo TK_IDENTIFICADOR argsAndCommands

;

depoisDeIdent: 
	  tamanhoVetor static tipo ';'
	| TK_PR_STATIC tipo ';'
	| tiposPrimitivos ';'
	| TK_IDENTIFICADOR fechaVarOuFunc
;
fechaVarOuFunc:
	  ';'
	| argsAndCommands
;

//Regras gerais
encapsulamento: %empty | TK_PR_PRIVATE | TK_PR_PUBLIC | TK_PR_PROTECTED;
tiposPrimitivos: TK_PR_INT | TK_PR_FLOAT | TK_PR_BOOL | TK_PR_CHAR | TK_PR_STRING;
tipo : tiposPrimitivos | TK_IDENTIFICADOR; // TK_IDENTIFICADOR para tipo do usuário
static: TK_PR_STATIC | %empty;
tipoConst: TK_PR_CONST tipo | tipo;

//Novos tipos
novoTipo: TK_PR_CLASS TK_IDENTIFICADOR listaCampos;
listaCampos: '[' list ']';
list: campo | campo ':' list;
campo: encapsulamento tiposPrimitivos TK_IDENTIFICADOR;

//Variáveis globais
tamanhoVetor: '[' TK_LIT_INT ']';

//Funções 
args: %empty | parameters;
parameters : parameter ',' parameters| parameter;
parameter: tipoConst TK_IDENTIFICADOR;
argsAndCommands : '(' args ')' blocoComandos;
//Bloco de comandos
blocoComandos: '{' comandos '}';
comando: blocoComandos | comandoSimples ';';
comandos : %empty | comando comandos;
comandoSimples: TK_PR_IF ;//COMANDOS SIMPLES // COLOQUEI TK_PR_IF PARA TESTAR BLOCOS DE COMANDOS

%%

