SRC = ../src

CC = gcc

CFLAGS = -Wall -Wextra -Wno-unused-parameter
LFLAGS = -g
LIBS = `sdl2-config --libs --cflags` -lSDL2

all : prog

prog : main.o board.o stack.o
	$(CC) $(LFLAGS) $^ -o $@

main.o : $(SRC)/main.c
	$(CC) $(CFLAGS) -c $<

board.o : $(SRC)/board.c
	$(CC) $(CFLAGS) -c $<

stack.o : $(SRC)/stack.c
	$(CC) $(CFLAGS) -c $<

g_interface.o : $(SRC)/g_interface.c
	$(CC) $(CFLAGS) -c $<

prog_test : test.o stack.o g_interface.o
	$(CC) $(LFLAGS) $^ $(LIBS) -o $@

test.o : $(SRC)/test.c
	$(CC) $(CFLAGS) -c $<



.PHONY : clear run test

clear :
	rm -f *.o prog prog_test

run : prog
	./prog

test : prog_test
	./prog_test