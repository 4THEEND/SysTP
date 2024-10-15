SRC = ../src

CC = gcc

CFLAGS = -Wall -Wextra -Wno-unused-parameter
LFLAGS = -g

all : prog

prog : main.o board.o stack.o
	$(CC) $(LFLAGS) $^ -o $@

main.o : $(SRC)/main.c
	$(CC) $(CFLAGS) -c $<

board.o : $(SRC)/board.c
	$(CC) $(CFLAGS) -c $<

stack.o : $(SRC)/stack.c
	$(CC) $(CFLAGS) -c $<


prog_test : test.o stack.o
	$(CC) $(LFLAGS) $^ -o $@

test.o : $(SRC)/test.c
	$(CC) $(CFLAGS) -c $<

.PHONY : clear run test

clear :
	rm -f *.o prog prog_test

run : prog
	./prog

test : prog_test
	./prog_test