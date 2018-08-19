
#Definição das variáveis do make
CC=gcc #C compiler
EXEC=analisador #Nome do executável
FLEXOUT=lex.yy.c
SRC=scanner.l tokens.h

all: $(SRC)
	flex scanner.l
	$(CC) $(FLEXOUT) -o $(EXEC) -lfl

clean:
	rm -rf $(EXEC)
	rm -rf $(FLEXOUT)
