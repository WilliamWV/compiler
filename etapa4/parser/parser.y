%{
#include <stdio.h>
#include "../include/tree.h"
#include "../include/lexVal.h"
#include "../include/userTypeField.h"
#include "../include/defines.h"
#include "../include/expression.h"
#include "../include/functionArgs.h"
#include "../include/parser.tab.h" 
int yylex(void);
extern int get_line_number(void); // avisa que função deve ser lincada e está em outro arquivo
int yyerror (char const *s){
	printf("%s, on line %d\n", s, get_line_number());
	return -1;
}

extern void* arvore;

extern Fields *currentFields;
extern Args *currentArgs;
extern char *currentFunc;

extern int yylex_destroy  (void); 

//útil quando um componente tem 2 identificadores e não se sabe se é var global
//ou função com tipo de usuário
struct node* firstID;
struct node* secondID;

//útil para verificar o tipo de uma expressão em pipe
struct node* inpPipe;
int parsingSucceded = FALSE;
int returnError = 1;
Node *nodeNotAdded = NULL;
char *identifierError;
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

int verifyArguments(char* symbol, struct node* argsCall){
	Hash* func = getSymbol(symbol);
	int argsNum = func->argsNum;
	if(argsCall == NULL){ // função sem argumentos
		if (argsNum == 0) return TRUE;
		return ERR_MISSING_ARGS;
	}
	if(argsNum == 0){ // argsCall não é nulo mas a função exige 0 argumentos
		return ERR_EXCESS_ARGS;
	}
	/* estrutura de argsCall:
		* Cabeça = NULL -> facilita verificação de excesso ou falta de argumentos
		* kids[0], kids[2], kids[4], ..., kids[(argsNum - 1) * 2] -> argCall ->
			contém expressão que representa o argumento
		* kids[1], kids[3], kids[5], ..., kids[(argsNum-1)*2 - 1] -> vírgula
		
	*/
	if(argsCall->kidsNumber < 2*argsNum -1) return ERR_MISSING_ARGS;
	if(argsCall->kidsNumber > 2*argsNum -1) return ERR_EXCESS_ARGS;
	
	int currentArg = 0;	
	for(int i = 0; i <= ((argsNum-1)* 2); i+=2){
		//pipe
		if (argsCall->kids[i] != NULL)
			if (!(argsCall->kids[i]->token->tokenType == SPEC_CHAR || 
				  argsCall->kids[i]->token->value.c == '.') )
			{		
				parseOperands(argsCall->kids[i]);
				argsCall->kids[i]->type = typeInference();
				int correctOperands =  coercion(func->args[currentArg]->argType, argsCall->kids[i]);
				if (correctOperands != 0){ return ERR_WRONG_TYPE_ARGS; }
				clearCurrentOperands();
				
			}else{
				if(inpPipe==NULL) return ERR_WRONG_TYPE_ARGS;
				else{
					Hash* inPipeFunc = getSymbol(inpPipe->token->value.str);
					if (inPipeFunc->type != func->args[currentArg]->argType){
						return ERR_WRONG_TYPE_ARGS;
					} 

				}
			}
		currentArg++;
	}
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
%type <ast> funcArgs
%type <ast> funcName
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
%type <ast> idThatCanBeFuncType
%type <ast> idThatCanBeFuncName
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
%type <ast> savePipe
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

//As duas regras abaixo servem para a eventual possibilidade do código possuir
//uma função que retorna tipo de usuário. As regras a seguir armazenam os 
//identificadores que representam o tipo e o nome para que possam ser adicionados
//na tabela de símbolos antes da execução do bloco de comandos da função

idThatCanBeFuncType:
	TK_IDENTIFICADOR	{$$ = criaNodo($1); firstID = $$;}
;

idThatCanBeFuncName:
	TK_IDENTIFICADOR	{$$ = criaNodo($1); secondID = $$;}
;

componente:
	  novoTipo							{$$ = $1;}
	| idThatCanBeFuncType depoisDeIdent { // Regra introduzida para resolver conflitos
		$$ = $1; 
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
			int type = getType($2->kids[3]);			
			if (type == USER){
				int isUsr = isUserType($2->kids[3]->token->value.str);
				if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
				int addSymb = addSymbol(
					$1->token, NATUREZA_IDENTIFICADOR, USER, getUserType($2->kids[3]),
					$2->kids[0]->token->value.i, FALSE, flag
				);
				if (addSymb!=0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}
			}
			else{
				int addSymb = addSymbol(
					$1->token, NATUREZA_IDENTIFICADOR, type, NULL, $2->kids[0]->token->value.i, 
					FALSE, flag 
				);
				if (addSymb!=0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}
			}
		}
		else if ($2->kids[0]->token->value.c == '('){ //
			//só precisa adicionar os argumentos, nome da função já foi adicionado em userTypeFunc
			addArgsToSymbol($2->token->value.str, currentArgs);
			clearCurrentArgs();
		}
		else{
			//Existem diferentes variações:
			//var global com tipos primitivos não estático -> head = tipoPrimitivo, kids[0] = ';'
			//var global estatica -> head = TK_PR_STATIC, kids[0] = tipo, kids[1] = ';'
			//var global não estática com tipo de usuário -> head = tipodeUser, kids[0] = ';'
			
			if ($2->kidsNumber == 2){
				//var global estática
				int type = getType($2->kids[0]);				
				if (type == USER){
					int isUsr = isUserType($2->kids[0]->token->value.str);
					if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
					int addSymb = addSymbol(
						$1->token, NATUREZA_IDENTIFICADOR, USER, 
						getUserType($2->kids[0]), 0, FALSE, STATIC
					);
					if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
					if (addSymb!=0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}
				}
				else{
					int addSymb = addSymbol(
						$1->token, NATUREZA_IDENTIFICADOR, type, 
						NULL, 0, FALSE, STATIC
					);
					if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}		
				}
				
			}else{
				int type = getType($2);
				if (type == USER){
					int isUsr = isUserType($2->token->value.str);
					if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
					int addSymb = addSymbol($1->token, NATUREZA_IDENTIFICADOR, USER, getUserType($2), 0, FALSE, 0);
					if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
				}
				else{
					int addSymb = addSymbol($1->token, NATUREZA_IDENTIFICADOR, type, NULL, 0, FALSE, 0);
					if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
				}
			}
		}
	}
	// Funções
	| funcName scopeOpenner funcArgs blocoComandos {
		$$ = $1; 
		adicionaFilho($$, $3); 
		adicionaFilho($$, $4);
		//funcName tem 2 formas possíveis:
		// 1) head = tipoPrimitivo, kids[0] = nome da func
		// 2) head = TK_PR_STATIC, kids[0] = tipo, kids[1] = nome DA FUNC		
		int kid = 0;
		if($1->kidsNumber == 2){
			kid = 1;
		}
			
		addArgsToSymbol($1->kids[kid]->token->value.str, currentArgs);
		//printArgs($1->kids[kid]->token->value.str);
		clearCurrentArgs();
		closeTable();
		
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
	| idThatCanBeFuncName fechaVarOuFunc {
		$$ = $1; 
		adicionaFilho($$, $2);
	}
;
fechaVarOuFunc:
	  ';'									{$$ = criaNodo($1);}
	| userTypeFunc scopeOpenner funcArgs blocoComandos	{
		$$ = $3;
		adicionaFilho($$, $4);
		closeTable();
	}
;
//regra que adiciona à tabela de símbolos o nome da função de tipo de usuário
userTypeFunc:
	%empty {
		int isUsr = isUserType(firstID->token->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; /*nodeNotAdded = $$*/; YYABORT;}
		int addSymb = addSymbol(secondID->token, NATUREZA_IDENTIFICADOR, USER, getUserType(firstID), 0, TRUE, 0);
		if(addSymb != 0){ returnError = addSymb; /*nodeNotAdded = $$*/; YYABORT;}
		saveFunc(secondID->token->value.str);
	}
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
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		addFieldsToSymbol($2->value.str, currentFields);
		//printFields("pessoa");
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
		
		adicionaArg(criaArg($1));

		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);

	}
	| parameter					{$$ = $1; adicionaArg(criaArg($1));}
;
parameter: //nodo raiz vai ter ou um filho (TK_IDENTIFICADOR; tipo vai ser o nodo raiz) ou dois (tipo e TK_IDENTIFICADOR)
	tipoConst TK_IDENTIFICADOR	{
		$$ = $1; adicionaFilho($$, criaNodo($2));
		//tipo const = TK_PR_CONST tipo || tipo
		int flag = 0;
		struct node* aux = $1;
		if ($1->kidsNumber==2){
			flag = CONST;
			aux = $1->kids[0];
		}
		int type = getType(aux);
		if (type == USER){
			int isUsr = isUserType(aux->token->value.str);
			if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
			int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, USER, getUserType(aux), 0, FALSE, flag);		
			if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		}	
		else{	
			int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, type, NULL, 0, FALSE, flag);		
			if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		}
	}
;
//precisa executar antes do bloco de comandos da função e adicionar o nome 
//em escopo global
funcName:
	tiposPrimitivos TK_IDENTIFICADOR {
		$$ = $1;
		adicionaFilho($$, criaNodo($2));
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, TRUE, 0);		
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		saveFunc($2->value.str);	
	}
	|TK_PR_STATIC tipo TK_IDENTIFICADOR{
		$$ = criaNodo($1);
		adicionaFilho($$, $2);	
		adicionaFilho($$, criaNodo($3));
		int type = getType($2);
		if(type == USER){
			int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, USER, getUserType($2), 0, TRUE, STATIC);
			if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		}
		else{
			int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, type, NULL, 0, TRUE, STATIC);
			if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		}
		saveFunc($3->value.str);	

	}
;
//precisa executar antes do bloco de comandos da função
//e adicionar os nomes no escopo da função
funcArgs:
	'(' args ')' {
		$$ = criaNodo($1);
		adicionaFilho($$, $2);
		adicionaFilho($$, criaNodo($3));
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

		parseOperands($3);
		int correctOperands =  coercion(BOOL, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
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
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = $$; YYABORT;}
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

		parseOperands($6);
		int correctOperands =  coercion(BOOL, $6);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();

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

		parseOperands($3);
		int correctOperands =  coercion(BOOL, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
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

		parseOperands($5);
		int correctOperands =  coercion(BOOL, $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
;


foreachList:
	expression						{
		$$ = $1;

		parseOperands($1);
		int correctOperands =  coercion(NONE, $1);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
	| foreachList ',' expression {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);

		parseOperands($3);
		int correctOperands =  coercion(NONE, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
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
		
		parseOperands($3);
		int correctOperands =  coercion(INT, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
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
		int isUsr = isUserType($2->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, USER, getUserType($$->kids[0]), 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
	}
	| TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3));
		int isUsr = isUserType($2->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, USER, getUserType($$->kids[0]), 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
	}
	| TK_PR_STATIC TK_PR_CONST TK_IDENTIFICADOR TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4));
		int isUsr = isUserType($3->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, USER, getUserType($$->kids[1]), 0, FALSE, STATIC + CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		
	}
	| TK_IDENTIFICADOR TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
		int isUsr = isUserType($1->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, USER, getUserType($$), 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		
	}
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3));
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3));
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		
	}
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4));
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
	}
	| tiposPrimitivos TK_IDENTIFICADOR {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2));
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
	}

	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5));
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		int isVar = isVariable($5->value.str);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = $$; YYABORT;}
		parseOperands($$->kids[3]);
		int correctOperands =  coercion(getType($2), $$->kids[3]);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();
		if (getType($2) == STRING){
			//atualiza tamanho
			updateStringSize($3->value.str, $$->kids[3], IDENT, NULL);
		}
		
	}
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}
				
		// o identificador é sempre o útimo filho desse nodo
		int isVar = isVariable($5->kids[$5->kidsNumber - 1]->token->value.str);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = $$; YYABORT;}
		parseOperands($5);
		int correctOperands =  coercion(getType($2), $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
		
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5));
		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		int isVar = isVariable($5->value.str);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = $$; YYABORT;}
		parseOperands($$->kids[3]);
		int correctOperands =  coercion(getType($2), $$->kids[3]);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();
		if (getType($2) == STRING){
			//atualiza tamanho
			updateStringSize($3->value.str, $$->kids[3], IDENT, NULL);
		}
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		// o identificador é sempre o útimo filho desse nodo
		int isVar = isVariable($5->kids[$5->kidsNumber - 1]->token->value.str);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = $$; YYABORT;}
		parseOperands($5);
		int correctOperands =  coercion(getType($2), $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
	}
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, criaNodo($6));
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		int isVar = isVariable($6->value.str);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = $$; YYABORT;}
		parseOperands($$->kids[4]);
		int correctOperands =  coercion(getType($3), $$->kids[4]);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();
		if (getType($3) == STRING){
			//atualiza tamanho
			updateStringSize($4->value.str, $$->kids[4], IDENT, NULL);
		}

	}
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);		
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		// o identificador é sempre o útimo filho desse nodo
		int isVar = isVariable($6->kids[$6->kidsNumber - 1]->token->value.str);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = $$; YYABORT;}
		parseOperands($6);
		int correctOperands =  coercion(getType($3), $6);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
	}
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE TK_IDENTIFICADOR {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4));
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		int isVar = isVariable($4->value.str);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = $$; YYABORT;}
		parseOperands($$->kids[2]);
		int correctOperands =  coercion(getType($1), $$->kids[2]);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();
		if (getType($1) == STRING){
			//atualiza tamanho
			updateStringSize($2->value.str, $$->kids[2], IDENT, NULL);
		}
	}
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveIdentifier {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4);
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		// o identificador é sempre o útimo filho desse nodo
		int isVar = isVariable($4->kids[$4->kidsNumber - 1]->token->value.str);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = $$; YYABORT;}
		parseOperands($4);
		int correctOperands =  coercion(getType($1), $4);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
	}

	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		parseOperands($6);
		int correctOperands =  coercion(getType($3), $6);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
		if (getType($3) == STRING){
			//atualiza tamanho
			updateStringSize($4->value.str, $6, IDENT, NULL);
		}
	}
	| TK_PR_STATIC TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);
		int addSymb = addSymbol($4, NATUREZA_IDENTIFICADOR, getType($3), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}
		parseOperands($6);
		int correctOperands =  coercion(getType($3), $6);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
	}
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);		
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		parseOperands($5);
		int correctOperands =  coercion(getType($2), $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
		if (getType($2) == STRING){
			//atualiza tamanho
			updateStringSize($3->value.str, $5, IDENT, NULL);
		}
	}
	| TK_PR_STATIC tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}
		parseOperands($5);
		int correctOperands =  coercion(getType($2), $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();		
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}
		parseOperands($5);
		int correctOperands =  coercion(getType($2), $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
		if (getType($2) == STRING){
			//atualiza tamanho
			updateStringSize($3->value.str, $5, IDENT, NULL);
		}	
	}
	| TK_PR_CONST tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		int addSymb = addSymbol($3, NATUREZA_IDENTIFICADOR, getType($2), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		parseOperands($5);
		int correctOperands =  coercion(getType($2), $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();
	}
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE literais {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4);
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		parseOperands($4);
		int correctOperands =  coercion(getType($1), $4);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();	
		if (getType($1) == STRING){
			//atualiza tamanho
			updateStringSize($2->value.str, $4, IDENT, NULL);
		}	
	}
	| tiposPrimitivos TK_IDENTIFICADOR TK_OC_LE negativeOrPositiveLiteral {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3)); 
		adicionaFilho($$, $4);
		int addSymb = addSymbol($2, NATUREZA_IDENTIFICADOR, getType($1), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = $$; YYABORT;}	
		parseOperands($4);
		int correctOperands =  coercion(getType($1), $4);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT; }
		clearCurrentOperands();
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
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = $$; YYABORT;}

		parseOperands($3);
		int correctOperands =  coercion(identifierType($1->value.str), $3);
		//printf("%d\n\n", correctOperands);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		//if (correctOperands != 0) exitAndFree(correctOperands, NULL, $$);
		//printCurrentOperands();
		clearCurrentOperands();
		if(identifierType($1->value.str) == STRING){
			//atualizar tamanho
			updateStringSize($1->value.str, $3, IDENT, NULL);
			
		}
	}
	| TK_IDENTIFICADOR '[' expression ']' '=' expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, $6);
		int isVec = isVector($1->value.str);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = $$; YYABORT;}
		
		parseOperands($3);
		int correctOperands =  coercion(INT, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();

		parseOperands($6);
		correctOperands =  coercion(identifierType($1->value.str), $6);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();

		if(identifierType($1->value.str) == STRING){
			updateStringSize($1->value.str, $6, VECTOR, NULL);
		}
	}
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR '=' expression {//
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodoCampo($3, $1->value.str)); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		int isUsr = isUserVar($1->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int hasF = hasField($1->value.str, $3->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = $$; YYABORT;}
		
		parseOperands($5);
		int correctOperands =  coercion(fieldType($1->value.str, $3->value.str), $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
		if (fieldType($1->value.str, $3->value.str) == STRING){
			updateStringSize($1->value.str, $5, USR, $3->value.str);
		}
	}
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR '=' expression {//
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, criaNodoCampo($6, $1->value.str)); 
		adicionaFilho($$, criaNodo($7)); 
		adicionaFilho($$, $8);
		int isVec = isVector($1->value.str);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = $$; YYABORT;}
		int isUsr = isUserVar($1->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int hasF = hasField($1->value.str, $6->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = $$; YYABORT;}

		parseOperands($3);
		int correctOperands =  coercion(INT, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();

		parseOperands($8);
		correctOperands =  coercion(fieldType($1->value.str, $6->value.str), $8);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}	
;
input:
	TK_PR_INPUT expression		{
		$$ = criaNodo($1); adicionaFilho($$, $2);
		if($2->token->tokenType!=IDS){ returnError = ERR_WRONG_PAR_INPUT; nodeNotAdded = $$; YYABORT;}	
		int isVar = isVariable($2->token->value.str);	
		if (isVar != TRUE){ returnError = ERR_VARIABLE; nodeNotAdded = $$; YYABORT;}
	}
;
/**
	Considera que expressão aritmética tem tipo:
		int ou float
	
*/
output:
	TK_PR_OUTPUT expression continueOutput {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, $3);
		parseOperands($2);
		$2->type = typeInference();
		if($2->type == BOOL){
			int correctOperands =  coercion(INT, $2);
			if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		}
		else{
			int correctOperands =  coercion(NONE, $2);
			if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		}
		if($2->type != INT && $2->type != FLOAT && $2->type != BOOL && $2->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
	| TK_PR_OUTPUT expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
		parseOperands($2);
		$2->type = typeInference();
		if($2->type == BOOL){
			int correctOperands =  coercion(INT, $2);
			if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		}
		else{
			int correctOperands =  coercion(NONE, $2);
			if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		}
		if($2->type != INT && $2->type != FLOAT && $2->type != BOOL && $2->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
;
continueOutput: 
	',' expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, $2);
		if($2->type != INT && $2->type != FLOAT && $2->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = $$; YYABORT;}
	}
	| ',' expression continueOutput	{
		$$ = criaNodo($1); 
		adicionaFilho($$, $2); 
		adicionaFilho($$, $3);
		if($2->type != INT && $2->type != FLOAT && $2->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = $$; YYABORT;}
	}
;
funcCall:
	TK_IDENTIFICADOR '(' argsCall ')'{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4));
		int isFunc = isFunction($1->value.str);
		if (isFunc != TRUE){ returnError = isFunc; nodeNotAdded = $$; YYABORT;}
		int correctArgs = verifyArguments($1->value.str, $3);
		if (correctArgs != TRUE){ returnError = correctArgs; nodeNotAdded = $$; YYABORT;}
	}
	| TK_IDENTIFICADOR '(' ')' {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodo($3));
		int isFunc = isFunction($1->value.str);
		if (isFunc != TRUE){ returnError = isFunc; nodeNotAdded = $$; YYABORT;}
		int correctArgs = verifyArguments($1->value.str, NULL);
		if (correctArgs != TRUE){ returnError = correctArgs; nodeNotAdded = $$; YYABORT;}
	}
;
argsCall:
	argCall					{
		$$ = criaNodo(NULL);	//tem cabeça NULL para facilitar verificação dos argumentos
		adicionaFilho($$, $1);
	} 
	| argsCall ',' argCall {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
;
argCall:
	expression			{$$ = $1;
		parseOperands($1);
		int correctOperands =  coercion(NONE, $1);
		//printf("tipo da expressao: %d\n", $1->type);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		//printf("tipo da expressao: %d\n", $1->type);
		clearCurrentOperands();
	}
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
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = $$; YYABORT;}

		parseOperands($3);
		int correctOperands =  coercion(INT, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR shiftOp expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
		adicionaFilho($$, criaNodoCampo($3, $1->value.str));
		adicionaFilho($$, $4); 
		adicionaFilho($$, $5);
		int isUsr = isUserVar($1->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int hasF = hasField($1->value.str, $3->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = $$; YYABORT;}

		parseOperands($5);
		int correctOperands =  coercion(INT, $5);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
	| TK_IDENTIFICADOR '[' expression ']' shiftOp expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, $5);
		adicionaFilho($$, $6);
		int isVec = isVector($1->value.str);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = $$; YYABORT;}

		parseOperands($3);
		int correctOperands =  coercion(INT, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
		
		parseOperands($6);
		correctOperands =  coercion(INT, $6);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR shiftOp expression {
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2));
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, criaNodoCampo($6, $1->value.str));
		adicionaFilho($$, $7); 
		adicionaFilho($$, $8);
		int isVec = isVector($1->value.str);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = $$; YYABORT;}
		int isUsr = isUserVar($1->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int hasF = hasField($1->value.str, $6->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = $$; YYABORT;}

		parseOperands($3);
		int correctOperands =  coercion(INT, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();

		parseOperands($8);
		correctOperands =  coercion(INT, $8);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
;


return:
	TK_PR_RETURN expression		{
		$$ = criaNodo($1); adicionaFilho($$, $2);
		int verifRet = verifyReturn($2);
		if (verifRet != TRUE){ returnError = verifRet; nodeNotAdded = $$; YYABORT;}
	}
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

savePipe:
	funcCall 	{$$ = $1; inpPipe = $1;}
;
pipe:
	savePipe TK_OC_FORWARD_PIPE funcCall {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
 	|pipe TK_OC_FORWARD_PIPE funcCall {
		$$ = $1; 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3);
	}
	|savePipe TK_OC_BASH_PIPE funcCall {
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

		parseOperands($2);
		int correctOperands =  coercion(NONE, $2);
		//printf("tipo do parentesis: %d\n", $2->type);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
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
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = $$; YYABORT;}
		
		parseOperands($3);
		int correctOperands =  coercion(INT, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
	}
	| TK_IDENTIFICADOR							{
		$$ = criaNodo($1);
		int isVar = isVariable($1->value.str);
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = $$; YYABORT;}
	}
	| TK_IDENTIFICADOR '$' TK_IDENTIFICADOR		{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, criaNodoCampo($3, $1->value.str));
		int isUsr = isUserVar($1->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int hasF = hasField($1->value.str, $3->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = $$; YYABORT;}
	}
	| TK_IDENTIFICADOR '[' expression ']' '$' TK_IDENTIFICADOR	{
		$$ = criaNodo($1); 
		adicionaFilho($$, criaNodo($2)); 
		adicionaFilho($$, $3); 
		adicionaFilho($$, criaNodo($4)); 
		adicionaFilho($$, criaNodo($5)); 
		adicionaFilho($$, criaNodoCampo($6, $1->value.str));
		int isVec = isVector($1->value.str);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = $$; YYABORT;}
		int isUsr = isUserVar($1->value.str);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = $$; YYABORT;}
		int hasF = hasField($1->value.str, $6->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = $$; YYABORT;}

		parseOperands($3);
		int correctOperands =  coercion(INT, $3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = $$; YYABORT;}
		clearCurrentOperands();
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


