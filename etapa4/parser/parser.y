%{
#include <stdio.h>
#include "../include/tree.h"
#include "../include/lexVal.h"
#include "../include/userTypeField.h"
#include "../include/natureza.h"
int yylex(void);
extern int get_line_number(void); // avisa que função deve ser lincada e está em outro arquivo
int yyerror (char const *s){
	printf("%s, on line %d\n", s, get_line_number());
	return -1;
}

extern void* arvore;

extern Fields *currentFields;

int parsingSucceded = FALSE;
extern Node *danglingNodes;

//Retorna constante representando o tipo
//opera sobre regra tipo ou tipoPrimitivo
int getType(struct node* type){
	if (strcmp(type->token->value.str, "int") == 0) return INT;
	if (strcmp(type->token->value.str, "float") == 0) return FLOAT;
	if (strcmp(type->token->value.str, "char") == 0) return CHAR;
	if (strcmp(type->token->value.str, "bool") == 0) return BOOL;
	if (strcmp(type->token->value.str, "string") == 0) return STRING;
	return USER;
}

//opera sovre tipo
char* getUserType(struct node* type){
	if (getType(type) != USER){
		return NULL;
	}
	else return type->token->value.str;
}

//TODO: implementar função addArgs ->operar sobre nodo args
void addArgs(char* symbol, struct node* args){

}
//TODO: implementar função addFields -> operar sobre nodo list
void addFields(char* symbol, struct node* list){

}

//TODO: implementar função verifyArguments // operar sobre argsCall
int verifyArguments(char* symbol, struct node* argsCall){
	return TRUE;
}

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


%type <ast> args
%type <ast> argsAndCommands
%type <ast> argCall
%type <ast> argsCall
%type <ast> assignment
%type <ast> blocoComandos
%type <ast> case
%type <ast> campo
%type <ast> comando
%type <ast> comandos
%type <ast> comandoSimples
%type <ast> comandosSemVirgula
%type <ast> componente
%type <ast> componentes
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
%destructor { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */} <valor_lexico>
%destructor {
	//printFields("zorzo");
	if(parsingSucceded == FALSE){
		liberaDanglingParser($$);
	}
} <ast>
%%

////////////////////////////////////////////////////////////////////////////////
/// OBSERVAÇÕES SOBRE AS AÇÕES BISON DEFINIDAS A SEGUIR:                     ///
/// 1 - AS AÇÕES FAZEM USO EXAUSTIVO DAS FUNÇÕES DEFINIDAS EM tree.h PARA    ///
///     CONSTRUIR A AST.                                                     ///
/// 2 - A FUNÇÃO Node* criaNodo(struct lexval* token); É USADA PARA CRIAR UM ///
///     NODO DA AST A PARTIR DO VALOR ASSOCIADO A UM TOKEN NO scanner.l      ///
/// 3 - A FUNÇÃO void adicionaFilho(Node *pai, Node *kid); É USADA PARA      ///
///     ADICIONAR UM NODO FILHO AO NODO ATUAL NA AST.                        ///
/// 4 - NO CASO DE PRODUÇÕES VAZIAS SE CRIA UM NODO COM VALOR DE TOKEN       ///
///     NULL.                                                                ///
/// 5 - A ÁRVORE FOI CONSTRUÍDA DE FORMA QUE NÃO EXISTAM NODOS               ///
///     INTERMEDIÁRIOS, COMO EXISTIRIA EM UMA ÁRVORE DE DERIVAÇÃO.           ///
/// 6 - A AST CORRESPONDENTE À PRODUÇÕES CUJO CORPO TENHA MAIS DE UM SÍMBOLO ///
///     É CONSTRUÍDA DE FORMA QUE O PRIMEIRO SÍMBOLO DA ESQUERDA PARA A      ///
///     DIREITA SEJA O PAI DE TODOS OS DEMAIS SÍMBOLOS DA PRODUÇÃO.          ///
////////////////////////////////////////////////////////////////////////////////

programa: 
	scopeOpenner componentes	{
		$$ = $2; arvore = $$; 
		parsingSucceded = TRUE;
		closeTable(); // fecha escopo global
	}
;

scopeOpenner:                  //Regra usada quando um escopo deve ser aberto
	%empty 						{initTable();}
;

componentes: 
	%empty 						{$$ = criaNodo(NULL);}
	| componente componentes 	{ $$ = $1; adicionaFilho($$, $2);}
;
componente:
	  novoTipo							{$$ = $1;}
	| TK_IDENTIFICADOR depoisDeIdent { // Regra introduzida para resolver conflitos
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
		/*Pode ser:
			1) Declaração de vetor -> cabeça da regra tem valor léxico '[' 
			   correspondente à abertura dos colchetes para declarar o tamanho
			2) Função -> primeiro filho da cabeça é '(' indicando
			   abertura dos parênteses para os parâmetros da função
			3) Variáveis globais -> caso contrário	
		*/
		if ($2->token->value.c == '['){
			//trata vetor
			// kids[0] = TK_LIT_INT
			// kids[1] = ']'
			// kids[2] = static | NULL
			// kids[3] = tipo
			// kids[4] = ';'
			int flag = 0;
			if ($2->kids[2]->token != NULL) 
				flag = STATIC;
			int addSymb = addSymbol(
				$1, NATUREZA_IDENTIFICADOR, getType($2->kids[3]), 
				getUserType($2->kids[3]), $2->kids[0]->token->value.i, 
				FALSE, flag 
			);
			if(addSymb!=0) exit(addSymb);
		}
		if ($2->kids[0]->token->value.c == '('){
			//trata função
			//$1 = tipo
			//head = TK_IDENTIFICADOR -> nome
			//kids[0] = '('
			//kids[0]->kids[0] = args
			//kids[0]->kids[1] = ')' 
			int addSymb = addSymbol($2->token, NATUREZA_IDENTIFICADOR, USER, getUserType($$), 0, TRUE, 0);			
			if(addSymb!=0) exit(addSymb);
			addArgs($2->token->value.str, $2->kids[0]->kids[0]);
		}
		else{
			//Existem diferentes variações:
			//var global com tipos primitivos não estático -> head = tipoPrimitivo, kids[0] = ';'
			//var global estatica -> head = TK_PR_STATIC, kids[0] = tipo, kids[1] = ';'
			//var global não estática com tipo de usuário -> head = tipodeUser, kids[0] = ';'
			
			if ($2->kidsNumber == 2){
				//var global estática
				int addSymb = addSymbol(
					$1, NATUREZA_IDENTIFICADOR, getType($2->kids[0]), 
					getUserType($2->kids[0]), 0, FALSE, STATIC
				);
				if(addSymb!=0) exit(addSymb);
			}else{
				//var global não estática, getType e getUserType devem poder diferenciar entre tipo 
				//de usuário e primitivos
				//int addSymb = addSymbol($1, NATUREZA_IDENTIFICADOR, getType($2), getUserType($2), 0, FALSE, 0);
				//if(addSymb!=0) exit(addSymb);
			}
		}
	}
	// Funções
	| tiposPrimitivos TK_IDENTIFICADOR argsAndCommands {
		$$ = $1; adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, TRUE, 0);		
		if(addSymb!=0) exit(addSymb);		
		addArgs($2->value.str, $3->kids[0]);
	}
	| TK_PR_STATIC tipo TK_IDENTIFICADOR argsAndCommands {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4);
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), getUserType($2), 0, TRUE, STATIC);
		if(addSymb!=0) exit(addSymb);		
		addArgs($3->value.str, $4->kids[0]);
	}
;

depoisDeIdent:
	 tamanhoVetor static tipo ';' {
		$$ = $1; 
		adicionaFilho($$, $2); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4));
	}
	| TK_PR_STATIC tipo ';'	{
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3));
	}
	| tiposPrimitivos ';' {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2));
	}
	| TK_IDENTIFICADOR fechaVarOuFunc {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
	}
;
fechaVarOuFunc:
	  ';'				{$$ = criaNodo($1);}
	| argsAndCommands	{$$ = $1;}
;

//Regras gerais
encapsulamento: 
	%empty 				{$$ = criaNodo(NULL);}
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
	| %empty			{$$ = criaNodo(NULL);} 
;
tipoConst: 
	TK_PR_CONST tipo 	{$$ = criaNodo($1); adicionaFilho($$, $2);} 
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
	TK_PR_CLASS TK_IDENTIFICADOR listaCampos ';' {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4));
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, USER, NULL, 0, FALSE, 0);		
		if(addSymb!=0) exit(addSymb);		
		addFields($2->value.str, $3->kids[0]);

		/*printf("currentFields: %d %d %s; simbolo: %s \n", currentFields->field->fieldType, currentFields->field->fieldEncaps, currentFields->field->fieldName, $2->value.str);

		printf("currentFields: %d %d %s; simbolo: %s \n", currentFields->next->field->fieldType, currentFields->next->field->fieldEncaps, currentFields->next->field->fieldName, $2->value.str);

printf("currentFields: %d %d %s; simbolo: %s \n", currentFields->next->next->field->fieldType, currentFields->next->next->field->fieldEncaps, currentFields->next->next->field->fieldName, $2->value.str);*/

		//addSymbol($2, NATUREZA_IDENTIFICADOR, USER, 0, FALSE);
		//addFieldsToSymbol($2->value.str, currentFields);
		clearCurrentFields();
	};
listaCampos: 
	'[' list ']'{
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3));
	}
;
list: 
	campo 				{adicionaCampo(criaCampo($1)); $$ = $1;}
	| campo ':' list{		
		adicionaCampo(criaCampo($1));

		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
;
campo: 
	encapsulamento tiposPrimitivos TK_IDENTIFICADOR	{
		$$ = $1; 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3));
	}
;

//Variáveis globais
tamanhoVetor: 
	'[' TK_LIT_INT ']'	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3));
	}
;
//Funções
args: 
	%empty 				{$$ = criaNodo(NULL);}
	| parameters		{$$ = $1;}
;		
parameters : 
	parameter ',' parameters {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
	| parameter					{$$ = $1;}
;
parameter: 
	tipoConst TK_IDENTIFICADOR	{$$ = $1; adicionaFilho($$, criaNodo($2));}
;
argsAndCommands : 
	'(' args ')' blocoComandos {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4);
	}
;
//Bloco de comandos
/**
	Observações gerais sobre comandos:
		* Precisei alterar as regras para comandos pois na especificação existem várias excessões de comandos que podem ou não podem ser aplicados em determinado lugar, separei o case dos comandos simples por não ter ';' e separei os que tem vírgula dos que não tem, pois somente os que não tem vírgula podem aparecer nas listas de comando do for
*/
blocoComandos:
	'{' scopeOpenner comandos '}' {
		$$ = criaNodo($1); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4));
		closeTable();                     //Fecha escopo local
	}
;
comando:
	comandoSimples ';'		{$$ = $1; adicionaFilho($$, criaNodo($2));}
	| case					{$$ = $1;}
; //Coloquei a regra do case aqui pois na especificação ele não está atrelado ao switch, mas apenas como marcador de lugar além disso não possui ';' no final e não pode ser usado no for
comandos :
	%empty					{$$ = criaNodo(NULL);}
	| comando comandos		{$$ = $1; adicionaFilho($$, $2);}
;


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
	TK_PR_IF '(' expression ')' TK_PR_THEN blocoComandos optElse {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6); 
		adicionaFilho($$, $7);
	}
;
optElse:
	%empty							{$$ = criaNodo(NULL);}
	| TK_PR_ELSE blocoComandos		{$$ = criaNodo($1); adicionaFilho($$, $2);}
;
foreach:
	TK_PR_FOREACH '(' TK_IDENTIFICADOR ':' foreachList ')' blocoComandos {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5); 
		adicionaFilho($$, criaNodo($6)); 
		adicionaFilho($$, $7);
		int isVar = isVariable($3->value.str);
		if(isVar!=TRUE) exit(isVar);
	}
;

//Para o for se cria um escopo onde estarão definidos eventuais símbolos 
//definidos nas forLists, esse escopo terá o escopo do blocoComandos acima
//de si na pilha, enquanto os comandos do for são executados 
for:
	scopeOpenner TK_PR_FOR '(' forList ':' expression ':' forList ')' blocoComandos	{
		$$ = criaNodo($2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6); 
		adicionaFilho($$, criaNodo($7)); 
		adicionaFilho($$, $8); 
		adicionaFilho($$, criaNodo($9)); 
		adicionaFilho($$, $10);
		closeTable();
	}
;

while_do:
	TK_PR_WHILE '(' expression ')' TK_PR_DO blocoComandos {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);
	}
;
do_while:
	TK_PR_DO blocoComandos TK_PR_WHILE '(' expression ')' {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5); 
		adicionaFilho($$, criaNodo($6));
	}
;


foreachList:
	expression						{$$ = $1;}
	| foreachList ',' expression {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
;
forList:
	comandosSemVirgula					{$$ = $1;}
	| forList ',' comandosSemVirgula {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
;

switch:
	TK_PR_SWITCH '(' expression ')' blocoComandos {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
	}
;
case:
	TK_PR_CASE TK_LIT_INT ':' {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3));
	}
;


/*Definição de Variáveis*/
localVarDefinition:
	TK_PR_STATIC TK_IDENTIFICADOR TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3));
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, USER, getUserType(criaNodo($2)), 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3));
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, USER, getUserType(criaNodo($2)), 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_STATIC TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4));
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, USER, getUserType(criaNodo($3)), 0, FALSE, STATIC + CONST);
		if(addSymb!=0) exit(addSymb);
		
	}
	| TK_IDENTIFICADOR TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, USER, getUserType(criaNodo($1)), 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
		
	}
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3));
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3));
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
		
	}
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4));
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| tiposPrimitivos TK_IDENTIFICADOR {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2));
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}

	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5));		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
		
	}
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5));
		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, criaNodo($6));
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);		
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4));
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4);
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}

	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4);
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4);
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
;
negativeOrPositiveIdentifier:
	'-' negativeOrPositiveIdentifier {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
	}
	| '-' TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
	}
	| '+' negativeOrPositiveIdentifier {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
	}
	| '+' TK_IDENTIFICADOR{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
	}
;

negativeOrPositiveLiteral:
	'-' negativeOrPositiveLiteral {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
	}
	| '-' TK_LIT_INT {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
	}
	| '-' TK_LIT_FLOAT {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
	}
	| '+' negativeOrPositiveLiteral {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
	}
	| '+' TK_LIT_INT {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
	}
	| '+' TK_LIT_FLOAT {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
	}
;


assignment:
	TK_IDENTIFICADOR '=' expression	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
		int isVar = isVariable($1->value.str);
		if (isVar!=TRUE) exit(isVar);
	}
	| TK_IDENTIFICADOR '[' expression ']' '=' expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);
		int isVec = isVector($1->value.str);
		if (isVec != TRUE) exit(isVec);
	}
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR '=' expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		int isUsr = isUserType($1->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField($1->value.str, $3->value.str);
		if(hasF != TRUE) exit(hasF);
	}
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR '=' expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, criaNodo($6)); 
		adicionaFilho($$, criaNodo($7)); 
		adicionaFilho($$, $8);
		int isVec = isVector($1->value.str);
		if (isVec != TRUE) exit(isVec);
		int isUsr = isUserType($1->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField($1->value.str, $6->value.str);
		if(hasF != TRUE) exit(hasF);
	}	
;
input:
	TK_PR_INPUT expression		{$$ = criaNodo($1); adicionaFilho($$, $2);}
;

output:
	TK_PR_OUTPUT expression continueOutput {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, $3);
	}
	| TK_PR_OUTPUT expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
	}
;
continueOutput: 
	',' expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
	}
	| ',' expression continueOutput	{
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, $3);
	}
;
funcCall:
	TK_IDENTIFICADOR '(' argsCall ')'{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4));
		int isFunc = isFunction($1->value.str);
		if(isFunc!=TRUE) exit(isFunc);
		int correctArgs = verifyArguments($1->value.str, $3);
		if(correctArgs != TRUE) exit(correctArgs);
	}
	| TK_IDENTIFICADOR '(' ')' {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3));
		int isFunc = isFunction($1->value.str);
		if(isFunc!=TRUE) exit(isFunc);
		int correctArgs = verifyArguments($1->value.str, NULL);
		if(correctArgs != TRUE) exit(correctArgs);
	}
;
argsCall:
	argCall					{$$ = $1;}
	| argsCall ',' argCall {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
;
argCall:
	expression			{$$ = $1;}
	| '.'				{$$ = criaNodo($1);};

shiftOp: 
	TK_OC_SL 			{$$ = criaNodo($1);}
	| TK_OC_SR			{$$ = criaNodo($1);};
shift: 
	TK_IDENTIFICADOR shiftOp expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, $3);
		int isVar = isVariable($1->value.str);
		if (isVar!=TRUE) exit(isVar);
	}
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR shiftOp expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4); 
		adicionaFilho($$, $5);
		int isUsr = isUserType($1->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField($1->value.str, $3->value.str);
		if(hasF != TRUE) exit(hasF);
	}
	| TK_IDENTIFICADOR '[' expression ']' shiftOp expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		adicionaFilho($$, $6);
		int isVec = isVector($1->value.str);
		if (isVec != TRUE) exit(isVec);
	}
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR shiftOp expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, criaNodo($6)); 
		adicionaFilho($$, $7); 
		adicionaFilho($$, $8);
		int isVec = isVector($1->value.str);
		if (isVec != TRUE) exit(isVec);
		int isUsr = isUserType($1->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField($1->value.str, $6->value.str);
		if(hasF != TRUE) exit(hasF);
	}
;


return:
	TK_PR_RETURN expression		{$$ = criaNodo($1); adicionaFilho($$, $2);}
;

expression:
	parenthesisOrOperand operators expression {
		$$ = $1; 
		adicionaFilho($$, $2); 
		adicionaFilho($$, $3);
	}
	| infiniteQuestionMarks operators expression {
		$$ = $1; 
		adicionaFilho($$, $2); 
		adicionaFilho($$, $3);
	}
	| parenthesisOrOperand			{$$ = $1;}
	| infiniteQuestionMarks			{$$ = $1;}
;
infiniteQuestionMarks:
	parenthesisOrOperand '?'		{$$ = $1; adicionaFilho($$, criaNodo($2));}
	| infiniteQuestionMarks '?'		{$$ = $1; adicionaFilho($$, criaNodo($2));}
;
pipe:
	funcCall TK_OC_FORWARD_PIPE funcCall {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
 	|pipe TK_OC_FORWARD_PIPE funcCall {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
	|funcCall TK_OC_BASH_PIPE funcCall {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
	|pipe TK_OC_BASH_PIPE funcCall {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
;

parenthesisOrOperand:
	'(' expression ')' {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3));
	}
	| operands					{$$ = $1;}
	| '-' parenthesisOrOperand	{$$ = criaNodo($1); adicionaFilho($$, $2);}
	| '+' parenthesisOrOperand	{$$ = criaNodo($1); adicionaFilho($$, $2);}
	| '!' parenthesisOrOperand	{$$ = criaNodo($1); adicionaFilho($$, $2);}
	| '*' parenthesisOrOperand	{$$ = criaNodo($1); adicionaFilho($$, $2);}
	| '&' parenthesisOrOperand	{$$ = criaNodo($1); adicionaFilho($$, $2);}
	| '#' parenthesisOrOperand	{$$ = criaNodo($1); adicionaFilho($$, $2);}
;
operands:
	TK_IDENTIFICADOR '[' expression ']' {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4));
		int isVec = isVector($1->value.str);
		if (isVec != TRUE) exit(isVec);
	}
	| TK_IDENTIFICADOR							{
		$$ = criaNodo($1);
		int isVar = isVariable($1->value.str);
		if (isVar != TRUE) exit(isVar);
	}
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR		{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3));
		int isUsr = isUserType($1->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField($1->value.str, $3->value.str);
		if(hasF != TRUE) exit(hasF);
	}
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, criaNodo($6));
		int isVec = isVector($1->value.str);
		if (isVec != TRUE) exit(isVec);
		int isUsr = isUserType($1->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField($1->value.str, $6->value.str);
		if(hasF != TRUE) exit(hasF);
	}
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


