%{

#include "parser.tab.h"
#include <string.h> //strdup
#include <stdlib.h> //atoi, atof
#include "lexVal.h"
#include "tree.h"
#define DEBUG 0

int num_lines = 1;

int get_line_number(void){
	return num_lines;

}



/**
	Função usada para associar o valor léxico de um token
	não literal ao yylval
*/
void configLexValueNonLiteral(int tkType){
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	yylval.valor_lexico->lineNumber = num_lines; 
	yylval.valor_lexico->tokenType = tkType;
	yylval.valor_lexico->literType = NONE;
	yylval.valor_lexico->value.str = strdup(yytext); //usa str pois o valor retornado por strdup também é uma cadeia de caracteres
}

%}

DIGIT [0-9]
CAPITALCHAR [A-Z]
SMALLCHAR [a-z]
ALPHABETIC {CAPITALCHAR}|{SMALLCHAR}|_
ALPHANUMERIC {ALPHABETIC}|{DIGIT}
SPECIALCHAR ","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"|"|"?"|"*"|"/"|"<"|">"|"="|"!"|"&"|"%"|"#"|"^"|"."|"$"
ASCIIALPHABET " "|"!"|"#"|"$"|"%"|"&"|"*"|"+"|","|"-"|"."|"/"|":"|";"|"<"|"="|">"|"?"|"@"|"["|"]"|"^"|"_"|"`"|"{"|"|"|"}"|"~"|"\\"|\"|{DIGIT}|{CAPITALCHAR}|{SMALLCHAR}|"'"|"("|")"
CONTROLCHAR "\\0"|"\\t"|"\\n"|"\\v"|"\\f"|"\\r"
INTLIT ({DIGIT})+|({DIGIT})+|{DIGIT}+
FLOATLIT {INTLIT}"."{DIGIT}+
WHITESPACE " "|"\t"|"\n"
OPENCOMMENT "/*"
LINECOMMENT "\/\/"


%x COMMENT
%%

{OPENCOMMENT} 	BEGIN(COMMENT);

\n {
	++num_lines;
}
int { configLexValueNonLiteral(KEYWORD); return TK_PR_INT; }
float { configLexValueNonLiteral(KEYWORD); return TK_PR_FLOAT; }
bool { configLexValueNonLiteral(KEYWORD); return TK_PR_BOOL; }
char { configLexValueNonLiteral(KEYWORD); return TK_PR_CHAR; }
string { configLexValueNonLiteral(KEYWORD); return TK_PR_STRING; }
if { configLexValueNonLiteral(KEYWORD); return TK_PR_IF; }
then { configLexValueNonLiteral(KEYWORD); return TK_PR_THEN; }
else { configLexValueNonLiteral(KEYWORD); return TK_PR_ELSE; }
while { configLexValueNonLiteral(KEYWORD); return TK_PR_WHILE; }
do { configLexValueNonLiteral(KEYWORD); return TK_PR_DO; }
input { configLexValueNonLiteral(KEYWORD); return TK_PR_INPUT; }
output { configLexValueNonLiteral(KEYWORD); return TK_PR_OUTPUT; }
return { configLexValueNonLiteral(KEYWORD); return TK_PR_RETURN; }
const { configLexValueNonLiteral(KEYWORD); return TK_PR_CONST; }
static { configLexValueNonLiteral(KEYWORD); return TK_PR_STATIC; }
foreach { configLexValueNonLiteral(KEYWORD);return TK_PR_FOREACH; }
for { configLexValueNonLiteral(KEYWORD); return TK_PR_FOR; }
switch { configLexValueNonLiteral(KEYWORD); return TK_PR_SWITCH; }
case { configLexValueNonLiteral(KEYWORD); return TK_PR_CASE; }
break { configLexValueNonLiteral(KEYWORD); return TK_PR_BREAK; }
continue {configLexValueNonLiteral(KEYWORD);return TK_PR_CONTINUE;}
class { configLexValueNonLiteral(KEYWORD); return TK_PR_CLASS; }
private {configLexValueNonLiteral(KEYWORD); return TK_PR_PRIVATE; }
public { configLexValueNonLiteral(KEYWORD); return TK_PR_PUBLIC; }
protected { configLexValueNonLiteral(KEYWORD); return TK_PR_PROTECTED; }

"<=" { configLexValueNonLiteral(COMP_OPER); return TK_OC_LE; }
">=" { configLexValueNonLiteral(COMP_OPER); return TK_OC_GE; }
"==" { configLexValueNonLiteral(COMP_OPER); return TK_OC_EQ; }
"!=" { configLexValueNonLiteral(COMP_OPER); return TK_OC_NE; }
"&&" { configLexValueNonLiteral(COMP_OPER); return TK_OC_AND; }
"||" { configLexValueNonLiteral(COMP_OPER); return TK_OC_OR; }
">>" { configLexValueNonLiteral(COMP_OPER); return TK_OC_SR; }
"<<" { configLexValueNonLiteral(COMP_OPER); return TK_OC_SL; }
"%>%" { configLexValueNonLiteral(COMP_OPER); return TK_OC_FORWARD_PIPE; }
"%|%" { configLexValueNonLiteral(COMP_OPER); return TK_OC_BASH_PIPE; }

{SPECIALCHAR} {
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	yylval.valor_lexico->lineNumber = num_lines;
	yylval.valor_lexico->tokenType = SPEC_CHAR;
	yylval.valor_lexico->literType = NONE;
	yylval.valor_lexico->value.c = yytext[0];//um caractere
	return *yytext;
}

false { 
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));	
	yylval.valor_lexico->lineNumber = num_lines;
	yylval.valor_lexico->tokenType = LITERAL;
	yylval.valor_lexico->literType = BOOL;
	yylval.valor_lexico->value.b = FALSE;
	return TK_LIT_FALSE; 
}
true { 
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	yylval.valor_lexico->lineNumber = num_lines;
	yylval.valor_lexico->tokenType = LITERAL;
	yylval.valor_lexico->literType = BOOL;
	yylval.valor_lexico->value.b = TRUE;
	return TK_LIT_TRUE; 
}

{ALPHABETIC}{ALPHANUMERIC}* { configLexValueNonLiteral(IDS); return TK_IDENTIFICADOR; }

{INTLIT} { 
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	yylval.valor_lexico->lineNumber = num_lines;
	yylval.valor_lexico->tokenType = LITERAL;
	yylval.valor_lexico->literType = INT;
	yylval.valor_lexico->value.i = atoi(yytext);
	return TK_LIT_INT; 
}
{FLOATLIT} { 
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	yylval.valor_lexico->lineNumber = num_lines;
	yylval.valor_lexico->tokenType = LITERAL;
	yylval.valor_lexico->literType = FLOAT;
	yylval.valor_lexico->value.f = atof(yytext);
	return TK_LIT_FLOAT; 
}
({FLOATLIT}|{INTLIT})(E|e){INTLIT} { // notacao cientifica
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	yylval.valor_lexico->lineNumber = num_lines;
	yylval.valor_lexico->tokenType = LITERAL;
	yylval.valor_lexico->literType = FLOAT;
	yylval.valor_lexico->value.f = atof(yytext);
	return TK_LIT_FLOAT; 
} 
'({ASCIIALPHABET}|{CONTROLCHAR})' { 
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	yylval.valor_lexico->lineNumber = num_lines;
	yylval.valor_lexico->tokenType = LITERAL;
	yylval.valor_lexico->literType = CHAR;
	yylval.valor_lexico->value.c = yytext[1];//um caractere que esta entre duas aspas simples
	return TK_LIT_CHAR; 
}
\"[^\"\n]*\" {
	yylval.valor_lexico = (struct lexval*) malloc(sizeof(struct lexval));
	yylval.valor_lexico->lineNumber = num_lines;
	yylval.valor_lexico->tokenType = LITERAL;
	yylval.valor_lexico->literType = STRING;
	yylval.valor_lexico->value.str = strdup(yytext);
	return TK_LIT_STRING;
}

{LINECOMMENT}[^\n]*   { }
<COMMENT>[^*\n]*	{/*eat chars that is not a '*' */}
<COMMENT>\*+[^*/\n]*	{/*eat chars '*' not followed by '/' */}
<COMMENT>\n 		{++num_lines;}
<COMMENT>"*"+"/"	{BEGIN(INITIAL);}
{WHITESPACE} {} // As três expressões regulares anteriores servem para ignorar trechos do código, logo as ações correspondentes devem ser substituídas por "{}" na versão final, ou seja, não retornam tokens

. { printf("Lexical error: "); return TOKEN_ERRO; }

%%

