
#Definição das variáveis do make
CC=gcc #C compiler
EXEC=analisador #Nome do executável
FLEXOUT=lex.yy.c
SRC=scanner.l tokens.h
TEST_IN_FILE=testInput
TEST_OUT_FILE=output
EXPECTED_RESULTS=expectedOutput
all: $(SRC)
	flex scanner.l
	$(CC) $(FLEXOUT) -o $(EXEC) -lfl

clean:
	rm -rf $(EXEC)
	rm -rf $(FLEXOUT)
	rm -rf $(TEST_OUT_FILE)

test:
	cat $(TEST_IN_FILE) | ./$(EXEC) > $(TEST_OUT_FILE)
	diff $(TEST_OUT_FILE) $(EXPECTED_RESULTS)
