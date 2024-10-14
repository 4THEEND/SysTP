SRC = ../src

CC = gcc

CFLAGS = -Wall -Wextra -Wno-unused-parameter
LFLAGS = -g

all : prog

prog : main.o
	$(CC) $(LFLAGS) $< -o $@

main.o : $(SRC)/main.c
	$(CC) $(CFLAGS) -c $<

.PHONY : clear

clear:
	rm -f *.o prog