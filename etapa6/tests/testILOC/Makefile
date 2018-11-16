CC=gcc #C compiler
EXEC=ILOCTest #Nome do executável

iloc:
	$(CC) -c testILOC.c ../../src/util.c ../../src/everybodyHateLeaks.c ../../src/iloc.c ../../src/naming.c ../../src/hash.c
	$(CC) -o $(EXEC) testILOC.o util.o everybodyHateLeaks.o iloc.o naming.o hash.o -lfl 

clean:
	rm -rf *.o
	rm -rf $(EXEC)

