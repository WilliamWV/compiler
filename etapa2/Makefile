
#Definição das variáveis do make
CC=gcc #C compiler
EXEC=etapa2 #Nome do executável
FLEX_SRC=scanner.l
FLEX_C=lex.yy.c
FLEX_O=lex.yy.o
BISON_SRC=parser.y
BISON_C=parser.tab.c
BISON_O=parser.tab.o
BISON_H=parser.tab.h
TEST_IN_FILE=testInput
TEST_OUT_FILE=output
EXPECTED_RESULTS=expectedOutput

all: $(FLEX_SRC) $(BISON_SRC)
	bison -d $(BISON_SRC)
	flex $(FLEX_SRC)
	$(CC) -c $(FLEX_C) $(BISON_C) main.c
	$(CC) -o $(EXEC) $(FLEX_O) $(BISON_O) main.o -lfl

clean:
	rm -rf $(BISON_C)
	rm -rf $(BISON_O)
	rm -rf $(BISON_H)
	rm -rf $(FLEX_C)
	rm -rf $(FLEX_O)
	rm -rf $(TEST_OUT_FILE)

test:
	cat $(TEST_IN_FILE) | ./$(EXEC) > $(TEST_OUT_FILE)
	diff $(TEST_OUT_FILE) $(EXPECTED_RESULTS)
