%{
int num_lines = 0;
%}
DIGIT [0-9]
CAPITALCHAR [A-Z]
SMALLCHAR [a-z]
ALPHABETIC {CAPITALCHAR}|{SMALLCHAR}|_
ALPHANUMERIC {ALPHABETIC}|{DIGIT}
SPECIALCHAR ","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"|"|"?"|"*"|"/"|"<"|">"|"="|"!"|"&"|"%"|"#"|"^"|"."|"$"
INTLIT "+"({DIGIT})+|"-"({DIGIT})+|{DIGIT}+
WHITESPACE " "|"\t"|"\n"
OPENCOMMENT "\/\*"
LINECOMMENT "\/\/"

%%

\n { ++num_lines; } // contador de linhas, mas deve estar errado pois conta \n digitados manualmente pelo usuário numa string, por ex
int|float|bool|char|string|if|then|else|while|do|input|output|return|const|static|foreach|for|switch|case|break|continue|class|private|public|protected { printf("reserved words\n"); } //palavras reservadas
false|true { printf("LITERAL BOOL\n"); } // BOOLLIT
{SPECIALCHAR} { printf("CARACTERE ESPECIAL\n"); } //caracteres especiais
{ALPHABETIC}{ALPHANUMERIC}* { printf("IDENTIFICADOR\n"); } //identificadores
{INTLIT} { printf("LITERAL INT\n"); } // INTLIT considera diversas coisas estranhas, como por exemplo -0 e +0, perguntar pro professor oq ele quer ja que n ta especificado
(E|e)?{INTLIT}"."{DIGIT}+ { printf("LITERAL FLOAT\n"); } // FLOATLIT
'({CAPITALCHAR}|{SMALLCHAR}|{SPECIALCHAR}|" ")' { printf("LITERAL CHAR\n"); } //CHARLIT

{LINECOMMENT}[^\n]*\n   {printf("A line comment: %s\n", yytext);} 
{OPENCOMMENT}[^\*\/]*\*\/ {printf("A multi-line comment: %s\n", yytext);}
{WHITESPACE} {printf("An whitespace: \"%s\"\n", yytext);} // As três expressões regulares anteriores servem para ignorar trechos do código, logo as ações correspondentes devem ser substituídas por "{}" na versão final, ou seja, não retornam tokens

. {printf("Caractere não reconhecido gerou erro léxico\n");}

%%

int main (void)
{
  int token;
  while ((token = yylex())){
  	printf("%d linhas\n", num_lines);
    // do something with token
  }
}
