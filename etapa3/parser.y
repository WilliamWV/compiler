%{
#include <stdio.h>
#include "tree.h"
#include "lexVal.h"
int yylex(void);
extern int get_line_number(void); // avisa que função deve ser lincada e está em outro arquivo
int yyerror (char const *s){
	printf("%s, on line %d\n", s, get_line_number());
	return -1;
}

extern void* arvore;

%}
%define parse.error verbose
%verbose

%union {
	struct lexval* valor_lexico;
	struct node* ast;
}
//Todos os nodos tem valor léxico, portanto o tipo do seu valor semântico será struct lexval representado
//por valor_lexico do %union acima e será adicionado aos tokens
%token <valor_lexico> TK_PR_INT
%token <valor_lexico> TK_PR_FLOAT
%token <valor_lexico> TK_PR_BOOL
%token <valor_lexico> TK_PR_CHAR
%token <valor_lexico> TK_PR_STRING
%token <valor_lexico> TK_PR_IF
%token <valor_lexico> TK_PR_THEN
%token <valor_lexico> TK_PR_ELSE
%token <valor_lexico> TK_PR_WHILE
%token <valor_lexico> TK_PR_DO
%token <valor_lexico> TK_PR_INPUT
%token <valor_lexico> TK_PR_OUTPUT
%token <valor_lexico> TK_PR_RETURN
%token <valor_lexico> TK_PR_CONST
%token <valor_lexico> TK_PR_STATIC
%token <valor_lexico> TK_PR_FOREACH
%token <valor_lexico> TK_PR_FOR
%token <valor_lexico> TK_PR_SWITCH
%token <valor_lexico> TK_PR_CASE
%token <valor_lexico> TK_PR_BREAK
%token <valor_lexico> TK_PR_CONTINUE
%token <valor_lexico> TK_PR_CLASS
%token <valor_lexico> TK_PR_PRIVATE
%token <valor_lexico> TK_PR_PUBLIC
%token <valor_lexico> TK_PR_PROTECTED
%token <valor_lexico> TK_OC_LE
%token <valor_lexico> TK_OC_GE
%token <valor_lexico> TK_OC_EQ
%token <valor_lexico> TK_OC_NE
%token <valor_lexico> TK_OC_AND
%token <valor_lexico> TK_OC_OR
%token <valor_lexico> TK_OC_SL
%token <valor_lexico> TK_OC_SR
%token <valor_lexico> TK_OC_FORWARD_PIPE
%token <valor_lexico> TK_OC_BASH_PIPE
%token <valor_lexico> TK_LIT_INT
%token <valor_lexico> TK_LIT_FLOAT
%token <valor_lexico> TK_LIT_FALSE
%token <valor_lexico> TK_LIT_TRUE
%token <valor_lexico> TK_LIT_CHAR
%token <valor_lexico> TK_LIT_STRING
%token <valor_lexico> TK_IDENTIFICADOR
%token <valor_lexico> TOKEN_ERRO
//tokens para caracteres especiais, declarados para poder usar seu valor semântico atribuido no scanner
%token <valor_lexico> ',' ';' ':' '(' ')' '[' ']' '{' '}' '+' '-' '|' '?' '*' '/' '<' '>' '=' '!' '&' '%' '#' '^' '.' '$'
%start programa

//Regras, em ordem alfabética, cujo tipo será ast, ou seja, seu valor semântico é representado como uma árvore

%type <ast> assignment
%type <ast> args
%type <ast> argsAndCommands
%type <ast> argCall
%type <ast> argsCall
%type <ast> blocoComandos
%type <ast> case
%type <ast> campo
%type <ast> comando
%type <ast> comandos
%type <ast> comandoSimples
%type <ast> comandosSemVirgula
%type <ast> componente
%type <ast> continueOutput
%type <ast> depoisDeIdent
%type <ast> do_while
%type <ast> encapsulamento
%type <ast> expression
%type <ast> fechaVarOuFunc
%type <ast> for
%type <ast> foreach
%type <ast> foreachList
%type <ast> forList
%type <ast> funcCall
%type <ast> ifThenElse
%type <ast> infiniteQuestionMarks
%type <ast> input
%type <ast> list
%type <ast> listaCampos
%type <ast> literais
%type <ast> localVarDefinition
%type <ast> negativeOrPositiveIdentifier
%type <ast> negativeOrPositiveLiteral
%type <ast> novoTipo
%type <ast> operands
%type <ast> operators
%type <ast> optElse
%type <ast> output
%type <ast> parameter
%type <ast> parameters
%type <ast> parenthesisOrOperand
%type <ast> pipe
%type <ast> programa
%type <ast> return
%type <ast> shift
%type <ast> shiftOp
%type <ast> static
%type <ast> switch
%type <ast> tamanhoVetor
%type <ast> tipo
%type <ast> tipoConst
%type <ast> tiposPrimitivos
%type <ast> while_do
%%

programa: 
	%empty 					{$$ = criaNodo(NULL);}
	| componente programa //{arvore = $$;}; // assinala a estrutura árvore a AST final
componente:
	  novoTipo				{$$ = $1;}
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
	  ';'				{$$ = criaNodo($1);}
	| argsAndCommands	{$$ = $1;}
;

//Regras gerais
encapsulamento: 
	%empty 				{$$ = NULL;}
	| TK_PR_PRIVATE 	{$$ = criaNodo($1);}
	| TK_PR_PUBLIC 		{$$ = criaNodo($1);}
	| TK_PR_PROTECTED	{$$ = criaNodo($1);}
;
tiposPrimitivos: 
	TK_PR_INT 			{$$ = criaNodo($1);}
	| TK_PR_FLOAT 		{$$ = criaNodo($1);}
	| TK_PR_BOOL 		{$$ = criaNodo($1);}
	| TK_PR_CHAR 		{$$ = criaNodo($1);}
	| TK_PR_STRING		{$$ = criaNodo($1);}
;
tipo : 
	tiposPrimitivos 	{$$ = $1;}
	| TK_IDENTIFICADOR	{$$ = criaNodo($1);}// TK_IDENTIFICADOR para tipo do usuário
; 
static: 
	TK_PR_STATIC 		{$$ = criaNodo($1);}
	| %empty			{$$ = NULL;} 
;
tipoConst: 
	TK_PR_CONST tipo 	//{$$ = criaNodo();} 
	| tipo				{$$ = $1;}
;
literais: 
	TK_LIT_INT 			{$$ = criaNodo($1);}
	| TK_LIT_FLOAT 		{$$ = criaNodo($1);}
	| TK_LIT_FALSE 		{$$ = criaNodo($1);}
	| TK_LIT_TRUE 		{$$ = criaNodo($1);}
	| TK_LIT_CHAR 		{$$ = criaNodo($1);}
	| TK_LIT_STRING		{$$ = criaNodo($1);}
;

//Novos tipos
novoTipo: 
	TK_PR_CLASS TK_IDENTIFICADOR listaCampos ';' ;
listaCampos: 
	'[' list ']';
list: 
	campo 				{$$ = $1;}
	| campo ':' list;
campo: 
	encapsulamento tiposPrimitivos TK_IDENTIFICADOR;

//Variáveis globais
tamanhoVetor: 
	'[' TK_LIT_INT ']';

//Funções
args: 
	%empty 				{$$ = criaNodo(NULL);}
	| parameters		{$$ = $1;}
;		
parameters : 
	parameter ',' parameters
	| parameter			{$$ = $1;}
;
parameter: 
	tipoConst TK_IDENTIFICADOR;
argsAndCommands : 
	'(' args ')' blocoComandos;
//Bloco de comandos
/**
	Observações gerais sobre comandos:
		* Precisei alterar as regras para comandos pois na especificação existem várias excessões de comandos que podem ou não podem ser aplicados em determinado lugar, separei o case dos comandos simples por não ter ';' e separei os que tem vírgula dos que não tem, pois somente os que não tem vírgula podem aparecer nas listas de comando do for
*/
blocoComandos:
	'{' comandos '}';
comando:
	comandoSimples ';'
	| case					{$$ = $1;}
; //Coloquei a regra do case aqui pois na especificação ele não está atrelado ao switch, mas apenas como marcador de lugar além disso não possui ';' no final e não pode ser usado no for
comandos :
	%empty					{$$ = criaNodo(NULL);}
	| comando comandos;


comandoSimples:
	comandosSemVirgula		{$$ = $1;}
	| output				{$$ = $1;}
	| funcCall				{$$ = $1;}
	| foreach				{$$ = $1;}
	| for					{$$ = $1;}
;


comandosSemVirgula: //comandos que são permitidos dentro das listas do for
	localVarDefinition		{$$ = $1;}
	| assignment			{$$ = $1;}
	| input					{$$ = $1;}
	| shift					{$$ = $1;}
	| TK_PR_BREAK			{$$ = criaNodo($1);}
	| TK_PR_CONTINUE		{$$ = criaNodo($1);}
	| return				{$$ = $1;}
	| ifThenElse			{$$ = $1;}
	| while_do				{$$ = $1;}
	| do_while				{$$ = $1;}
	| switch				{$$ = $1;}
	| pipe					{$$ = $1;}
	| blocoComandos			{$$ = $1;}
;

ifThenElse:
	TK_PR_IF '(' expression ')' TK_PR_THEN blocoComandos optElse;
optElse:
	%empty					{$$ = criaNodo(NULL);}
	| TK_PR_ELSE blocoComandos;
foreach:
	TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' foreachList ')' blocoComandos;

for:
	TK_PR_FOR '(' forList ':' expression ':' forList ')' blocoComandos;

while_do:
	TK_PR_WHILE '(' expression ')' TK_PR_DO blocoComandos;
do_while:
	TK_PR_DO blocoComandos TK_PR_WHILE '(' expression ')';


foreachList:
	expression				{$$ = $1;}
	| foreachList ',' expression ;
forList:
	comandosSemVirgula		{$$ = $1;}
	| forList ',' comandosSemVirgula ;

switch:
	TK_PR_SWITCH '(' expression ')' blocoComandos;
case:
	TK_PR_CASE TK_LIT_INT ':';


/*Definição de Variáveis*/
localVarDefinition:
	TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR
	| TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR
	| TK_PR_STATIC TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR
	| TK_IDENTIFICADOR TK_IDENTIFICADOR
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR
	| tiposPrimitivos TK_IDENTIFICADOR

	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier

	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral;

negativeOrPositiveIdentifier:
	'-' negativeOrPositiveIdentifier
	| '-' TK_IDENTIFICADOR
	| '+' negativeOrPositiveIdentifier
	| '+' TK_IDENTIFICADOR;

negativeOrPositiveLiteral:
	'-' negativeOrPositiveLiteral 		//{$$ = }
	| '-' TK_LIT_INT					//{$$ = }
	| '-' TK_LIT_FLOAT					//{$$ = }
	| '+' negativeOrPositiveLiteral
	| '+' TK_LIT_INT
	| '+' TK_LIT_FLOAT;


assignment:
	TK_IDENTIFICADOR '=' expression
	| TK_IDENTIFICADOR '[' expression ']' '=' expression
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR '=' expression
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR '=' expression;

input:
	TK_PR_INPUT expression;

output:
	TK_PR_OUTPUT expression continueOutput
	| TK_PR_OUTPUT expression;
continueOutput: 
	',' expression 
	| ',' expression continueOutput;

funcCall:
	TK_IDENTIFICADOR '(' argsCall ')'
	| TK_IDENTIFICADOR '(' ')';
argsCall:
	argCall				{$$ = $1;}
	| argsCall ',' argCall;
argCall:
	expression			{$$ = $1;}
	| '.'				{$$ = criaNodo($1);};

shiftOp: 
	TK_OC_SL 			{$$ = criaNodo($1);}
	| TK_OC_SR			{$$ = criaNodo($1);};
shift: 
	TK_IDENTIFICADOR shiftOp expression
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR shiftOp expression
	| TK_IDENTIFICADOR '[' expression ']' shiftOp expression
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR shiftOp expression;

return:
	TK_PR_RETURN expression;


expression:
	parenthesisOrOperand operators expression
	| infiniteQuestionMarks operators expression
	| parenthesisOrOperand		{$$ = $1;}
	| infiniteQuestionMarks		{$$ = $1;}
;
infiniteQuestionMarks:
	parenthesisOrOperand '?'
	| infiniteQuestionMarks '?';
pipe:
	funcCall TK_OC_FORWARD_PIPE funcCall;
 	|pipe TK_OC_FORWARD_PIPE funcCall
	|funcCall TK_OC_BASH_PIPE funcCall
	|pipe TK_OC_BASH_PIPE funcCall;

parenthesisOrOperand:
	'(' expression ')'
	| operands			{$$ = $1;}
	| '-' parenthesisOrOperand
	| '+' parenthesisOrOperand
	| '!' parenthesisOrOperand
	| '*' parenthesisOrOperand
	| '&' parenthesisOrOperand
	| '#' parenthesisOrOperand;
operands:
	TK_IDENTIFICADOR '[' expression ']'
	| TK_IDENTIFICADOR	{$$ = criaNodo($1);}
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR
	| TK_LIT_INT		{$$ = criaNodo($1);}
	| TK_LIT_FLOAT		{$$ = criaNodo($1);}
	| TK_LIT_TRUE		{$$ = criaNodo($1);}
	| TK_LIT_FALSE		{$$ = criaNodo($1);}
	| TK_LIT_CHAR		{$$ = criaNodo($1);}		
	| TK_LIT_STRING		{$$ = criaNodo($1);}
	| funcCall			{$$ = $1;}
	| pipe				{$$ = $1;}
;	
operators:
	'+'				{$$ = criaNodo($1);}
	| '-'			{$$ = criaNodo($1);}
	| '*'			{$$ = criaNodo($1);}
	| '/'			{$$ = criaNodo($1);}
	| '%'			{$$ = criaNodo($1);}
	| '^'			{$$ = criaNodo($1);}
	| TK_OC_AND		{$$ = criaNodo($1);}
	| TK_OC_OR		{$$ = criaNodo($1);}
	| '|'			{$$ = criaNodo($1);}
	| '&'			{$$ = criaNodo($1);}
	| TK_OC_EQ		{$$ = criaNodo($1);}
	| TK_OC_NE		{$$ = criaNodo($1);}
	| TK_OC_GE		{$$ = criaNodo($1);}
	| TK_OC_LE		{$$ = criaNodo($1);}
	| '<'			{$$ = criaNodo($1);}
	| '>'			{$$ = criaNodo($1);}
;

%%


