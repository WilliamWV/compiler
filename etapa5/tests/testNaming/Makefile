CC=gcc #C compiler
EXEC=namingTest #Nome do executável

naming:
	$(CC) -c testNaming.c ../../src/naming.c ../../src/everybodyHateLeaks.c
	$(CC) -o $(EXEC) testNaming.o naming.o everybodyHateLeaks.o -lfl

clean:
	rm -rf *.o
	rm -rf $(EXEC)

