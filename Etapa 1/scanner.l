%{
int num_lines = 1;
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

\n { printf("Fim da linha %d\n", num_lines); ++num_lines; } // contador de linhas
int|float|bool|char|string|if|then|else|while|do|input|output|return|const|static|foreach|for|switch|case|break|continue|class|private|public|protected { printf("PALAVRAS RESERVADAS\n"); } //palavras reservadas
"<="|">="|"=="|"!="|"&&"|"||"|">>"|"<<"|"%>%"|"%|%" { printf("OPERADORES COMPOSTOS\n"); } // BOOLLIT
{SPECIALCHAR} { printf("CARACTERE ESPECIAL\n"); } //caracteres especiais
{INTLIT} { printf("LITERAL INT\n"); } // INTLIT considera diversas coisas estranhas, como por exemplo -0 e +0, perguntar pro professor oq ele quer ja que n ta especificado
{INTLIT}"."{DIGIT}+ { printf("LITERAL FLOAT\n"); } // FLOATLIT
(E|e){INTLIT} { printf("LITERAL FLOAT notacao cientifica\n"); } // FLOATLIT (notacao cientifica)
'({CAPITALCHAR}|{SMALLCHAR}|{SPECIALCHAR}|" ")' { printf("LITERAL CHAR\n"); } //CHARLIT
false|true { printf("LITERAL BOOL\n"); } // BOOLLIT
{ALPHABETIC}{ALPHANUMERIC}* { printf("IDENTIFICADOR\n"); } //identificadores

{LINECOMMENT}[^\n]*\n   { printf("A line comment: %s\n", yytext); ++num_lines; } 
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
