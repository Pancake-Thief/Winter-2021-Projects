#Makefile for Samuel Briones-Plascencia's TicTac v2

# design names
DESIGN = TicTacWowWeeWow

# libraries
LIBS = libAI.a

CC = gcc
DEBUG = -DDEBUG -g
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall
AR = ar rc
RANLIB = ranlib

all: TicTacWowWeeWow

## generate the obj. files ##
AI.o: AI.c AI.h Board.h Settings.h
	$(CC) $(CFLAGS) -g AI.c -o AI.o
Board.o: Board.c Board.h Constants.h Settings.h
	$(CC) $(CFLAGS) -g Board.c -o Board.o

FileIO.o: FileIO.c FileIO.h Board.h Settings.h
	$(CC) $(CFLAGS) -g FileIO.c -o FileIO.o

Game.o: Game.c Game.h Board.h Settings.h
	$(CC) $(CFLAGS) -g Game.c -o Game.o

Settings.o: Settings.c Settings.h
	$(CC) $(CFLAGS) -g Settings.c -o Settings.o

TicTacWowWeeWow.o: TicTacWowWeeWow.c FileIO.h Game.h Settings.h Board.h
	$(CC) $(CFLAGS) -g TicTacWowWeeWow.c -o TicTacWowWeeWow.o

## generate library files ##

libAI.a: AI.o
	$(AR) libAI.a AI.o
	$(RANLIB) libAI.a

## generate the executeable ##

TicTacWowWeeWow: TicTacWowWeeWow.o Settings.o Game.o FileIO.o Board.o libAI.a
	$(CC) $(LFLAGS) -g TicTacWowWeeWow.o Settings.o Game.o FileIO.o Board.o -L. -lAI -o TicTacWowWeeWow

## clean ##
clean: 
	rm -f *.o $(DESIGN) *.a 
