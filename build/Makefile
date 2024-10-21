SRC = ../src

CC = gcc
TIDY = clang-tidy

CFLAGS = -Wall -Wextra -Wno-unused-parameter
LFLAGS = -g
LIBS = `sdl2-config --libs --cflags` -lSDL2 -lSDL2_ttf

all : igel

igel : main.o board.o stack.o maingame.o g_interface.o
	$(CC) $(LFLAGS) $^ $(LIBS) -o $@

prog_test : test.o stack.o
	$(CC) $(LFLAGS) $^ -o $@

%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -c $<


.PHONY : clear run test tidy

clear :
	rm -f *.o igel prog_test

run : igel
	./igel

test : prog_test
	./prog_test

tidy :
	$(TIDY) --config-file=clang-tidy -header-filter=.* $(SRC)/* -- $(CFLAGS)
