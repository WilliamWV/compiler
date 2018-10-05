
#Definição das variáveis do make
CC=gcc #C compiler
EXEC=etapa4 #Nome do executável

FLEX_SRC=scanner/scanner.l
FLEX_C=src/lex.yy.c
FLEX_O=obj/lex.yy.o
BISON_SRC=parser/parser.y
BISON_C=src/parser.tab.c
BISON_O=obj/parser.tab.o
BISON_H=include/parser.tab.h
MAIN_C=src/main.c
MAIN_O=obj/main.o
TREE_C=src/tree.c
TREE_O=obj/tree.o
REPORT_FILE = report

all: gen_bin

flex: bison $(FLEX_SRC)
	flex $(FLEX_SRC)
	mv lex.yy.c src
bison: $(BISON_SRC)
	bison -d $(BISON_SRC)
	mv parser.tab.c src
	mv parser.tab.h include
	mv parser.output parser
gen_obj: flex
	$(CC) -c $(FLEX_C) $(BISON_C) $(TREE_C) $(MAIN_C)
	mv *.o obj

gen_bin: gen_obj
	$(CC) -o $(EXEC) $(FLEX_O) $(BISON_O) $(TREE_O) $(MAIN_O) -lfl


clean:
	rm -rf $(BISON_C)
	rm -rf $(FLEX_C)
	rm -rf $(BISON_H)
	rm -rf $(ODIR)/*
	rm -rf $(REPORT_FILE)
	rm -rf $(EXEC)
#Regra para gerar arquivo com descrição da gramática
verb: $(BISON_SRC)
	bison -d $(BISON_SRC) --report-file=report
