SRC = ../src

CC = gcc

CFLAGS = -Wall -Wextra -Wno-unused-parameter
LFLAGS=-g

all : prog

main.o : $(SRC)/main.c:
	$(CC) -CFLAGS $< -o $@

prog : main.o
	$(CC) -LFLAGS $< -o $@

.PHONY : clean

clean:
	rm -f *.o