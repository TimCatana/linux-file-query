CC = gcc
CFLAGS = -Wall -pedantic -g -I$(INC)

INC = inc/
SRC = src/
BIN = bin/

all: $(BIN)FSreport

$(BIN)FSreport: $(SRC)FSreport.c $(BIN)FSreportHelpers.o $(BIN)printInode.o $(BIN)printTree.o
	$(CC) $(CFLAGS) $(SRC)FSreport.c $(BIN)FSreportHelpers.o $(BIN)printInode.o $(BIN)printTree.o -o $(BIN)FSreport

$(BIN)FSreportHelpers.o: $(SRC)FSreportHelpers.c $(INC)FSreportHelpers.h
	$(CC) $(CFLAGS) -c $(SRC)FSreportHelpers.c -o $(BIN)FSreportHelpers.o  

$(BIN)printInode.o: $(SRC)printInode.c $(INC)printInode.h
	$(CC) $(CFLAGS) -c $(SRC)printInode.c -o $(BIN)printInode.o  

$(BIN)printTree.o: $(SRC)printTree.c $(INC)printTree.h
	$(CC) $(CFLAGS) -c $(SRC)printTree.c -o $(BIN)printTree.o  

clean:
	rm $(BIN)FSreport  $(BIN)*.o