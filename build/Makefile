SRC = ../src

CC = gcc

CFLAGS = -Wall -Wextra -Wno-unused-parameter
LFLAGS = -g
LIBS = `sdl2-config --libs --cflags` -lSDL2

all : prog

prog : main.o board.o stack.o maingame.o
	$(CC) $(LFLAGS) $^ -o $@

prog_test : test.o stack.o g_interface.o board.o
	$(CC) $(LFLAGS) $^ $(LIBS) -o $@

%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -c $<


.PHONY : clear run test

clear :
	rm -f *.o prog prog_test

run : prog
	./prog

test : prog_test
	./prog_test