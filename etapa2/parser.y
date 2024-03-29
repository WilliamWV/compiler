%{
#include <stdio.h>

int yylex(void);
extern int get_line_number(void); // avisa que função deve ser lincada e está em outro arquivo
int yyerror (char const *s){
	printf("%s, on line %d\n", s, get_line_number());
	return -1;
}
%}
%define parse.error verbose
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
literais: TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_FALSE | TK_LIT_TRUE | TK_LIT_CHAR | TK_LIT_STRING;

//Novos tipos
novoTipo: TK_PR_CLASS TK_IDENTIFICADOR listaCampos ';' ;
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
/**
	Observações gerais sobre comandos:
		* Precisei alterar as regras para comandos pois na especificação existem várias excessões de comandos que podem ou não podem ser aplicados em determinado lugar, separei o case dos comandos simples por não ter ';' e separei os que tem vírgula dos que não tem, pois somente os que não tem vírgula podem aparecer nas listas de comando do for
*/
blocoComandos:
	'{' comandos '}';
comando:
	comandoSimples ';'
	| case; //Coloquei a regra do case aqui pois na especificação ele não está atrelado ao switch, mas apenas como marcador de lugar além disso não possui ';' no final e não pode ser usado no for
comandos :
	%empty
	| comando comandos;


comandoSimples:
	comandosSemVirgula
	| output
	| funcCall
	| foreach
	| for;


comandosSemVirgula: //comandos que são permitidos dentro das listas do for
	localVarDefinition
	| assignment
	| input
	| shift
	| TK_PR_BREAK
	| TK_PR_CONTINUE
	| return
	| ifThenElse
	| while_do
	| do_while
	| switch
	| pipe
	| blocoComandos;

ifThenElse:
	TK_PR_IF '(' expression ')' TK_PR_THEN blocoComandos optElse;
optElse:
	%empty
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
	expression
	| foreachList ',' expression ;
forList:
	comandosSemVirgula
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
	'-' negativeOrPositiveLiteral
	| '-' TK_LIT_INT
	| '-' TK_LIT_FLOAT
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
continueOutput: ',' expression | ',' expression continueOutput

funcCall:
	TK_IDENTIFICADOR '(' argsCall ')'
	| TK_IDENTIFICADOR '(' ')';
argsCall:
	argCall
	| argsCall ',' argCall;
argCall:
	expression
	| '.';

shiftOp: TK_OC_SL | TK_OC_SR;
shift: TK_IDENTIFICADOR shiftOp expression
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR shiftOp expression
	| TK_IDENTIFICADOR '[' expression ']' shiftOp expression
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR shiftOp expression;

return:
	TK_PR_RETURN expression;


expression:
	parenthesisOrOperand operators expression
	| infiniteQuestionMarks operators expression
	| parenthesisOrOperand
	| infiniteQuestionMarks;
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
	| operands
	| '-' parenthesisOrOperand
	| '+' parenthesisOrOperand
	| '!' parenthesisOrOperand
	| '*' parenthesisOrOperand
	| '&' parenthesisOrOperand
	| '#' parenthesisOrOperand;
operands:
	TK_IDENTIFICADOR '[' expression ']'
	|TK_IDENTIFICADOR
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR
	| TK_LIT_INT
	| TK_LIT_FLOAT
	| TK_LIT_TRUE
	| TK_LIT_FALSE
	| TK_LIT_CHAR
	| TK_LIT_STRING
	| funcCall
	| pipe;
operators:
	'+'
	| '-'
	| '*'
	| '/'
	| '%'
	| '^'
	| TK_OC_AND
	| TK_OC_OR
	| '|'
	| '&'
	| TK_OC_EQ
	| TK_OC_NE
	|	TK_OC_GE
	| TK_OC_LE
	| '<'
	| '>';

%%
