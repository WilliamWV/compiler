%{

#include "parser.tab.h"

#define DEBUG 0

int num_lines = 1;

int get_line_number(void){
	return num_lines;
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
INTLIT "+"({DIGIT})+|"-"({DIGIT})+|{DIGIT}+
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
int { return TK_PR_INT; }
float { return TK_PR_FLOAT; }
bool { return TK_PR_BOOL; }
char { return TK_PR_CHAR; }
string { return TK_PR_STRING; }
if { return TK_PR_IF; }
then { return TK_PR_THEN; }
else { return TK_PR_ELSE; }
while { return TK_PR_WHILE; }
do { return TK_PR_DO; }
input { return TK_PR_INPUT; }
output { return TK_PR_OUTPUT; }
return { return TK_PR_RETURN; }
const { return TK_PR_CONST; }
static { return TK_PR_STATIC; }
foreach { return TK_PR_FOREACH; }
for { return TK_PR_FOR; }
switch { return TK_PR_SWITCH; }
case { return TK_PR_CASE; }
break { return TK_PR_BREAK; }
continue { return TK_PR_CONTINUE; }
class { return TK_PR_CLASS; }
private { return TK_PR_PRIVATE; }
public { return TK_PR_PUBLIC; }
protected { return TK_PR_PROTECTED; }
"<=" { return TK_OC_LE; }
">=" { return TK_OC_GE; }
"==" { return TK_OC_EQ; }
"!=" { return TK_OC_NE; }
"&&" { return TK_OC_AND; }
"||" { return TK_OC_OR; }
">>" { return TK_OC_SR; }
"<<" { return TK_OC_SL; }
"%>%" { return TK_OC_FORWARD_PIPE; }
"%|%" { return TK_OC_BASH_PIPE; }
false { return TK_LIT_FALSE; }
true { return TK_LIT_TRUE; }
{SPECIALCHAR} {	return *yytext; }
{INTLIT} { return TK_LIT_INT; }
{FLOATLIT} { return TK_LIT_FLOAT; }
({FLOATLIT}|{INTLIT})(E|e){INTLIT} { return TK_LIT_FLOAT; } // notacao cientifica
'({ASCIIALPHABET}|{CONTROLCHAR})' { return TK_LIT_CHAR; }
{ALPHABETIC}{ALPHANUMERIC}* { return TK_IDENTIFICADOR; }
\"[^\"\n]*\" {return TK_LIT_STRING;}
{LINECOMMENT}[^\n]*\n   { ++num_lines; }
<COMMENT>[^*\n]*	{/*eat chars that is not a '*' */}
<COMMENT>\*+[^*/\n]*	{/*eat chars '*' not followed by '/' */}
<COMMENT>\n 		{++num_lines;}
<COMMENT>"*"+"/"	{BEGIN(INITIAL);}
{WHITESPACE} {} // As três expressões regulares anteriores servem para ignorar trechos do código, logo as ações correspondentes devem ser substituídas por "{}" na versão final, ou seja, não retornam tokens

. { return TOKEN_ERRO; }

%%
