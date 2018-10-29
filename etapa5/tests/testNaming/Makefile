CC=gcc #C compiler
EXEC=namingTest #Nome do executável

hash:
	$(CC) -c testNaming.c ../../src/naming.c 
	$(CC) -o $(EXEC) testNaming.o naming.o -lfl

clean:
	rm -rf *.o
	rm -rf $(EXEC)

