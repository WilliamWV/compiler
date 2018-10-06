CC=gcc #C compiler
EXEC=hashTest #Nome do executável

hash:
	$(CC) -c testHash.c ../src/hash.c ../src/util.c
	$(CC) -o $(EXEC) testHash.o hash.o util.o -lfl

clean:
	rm -rf *.o
	rm -rf $(EXEC)

