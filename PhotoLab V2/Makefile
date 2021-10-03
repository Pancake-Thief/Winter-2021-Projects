#Make file for PhotoLab v2

CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -Wall -ansi -std=c99 -c
LFLAGS = -Wall -std=c99

all: PhotoLab_v2 PhotoLabTest

clean:
	rm -f *.o
	rm -f *.a
	rm -f PhotoLab_v2
	rm -f PhotoLabTest
	rm -f age.ppm
	rm -f sharpen.ppm
	rm -f edge.ppm
	rm -f posterize.ppm
	rm -f negative.ppm
	rm -f noise.ppm

FileIO.o: FileIO.c Constants.h FileIO.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c Constants.h DIPs.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

libfilter.a: DIPs.o Advanced.o
	ar rc libfilter.a DIPs.o Advanced.o
	ranlib libfilter.a
PhotoLabTest.o: PhotoLab_v2.c Constants.h DIPs.h FileIO.h
	$(CC) $(CFLAGS) $(DEBUG) PhotoLab_v2.c -o PhotoLabTest.o

PhotoLab.o: PhotoLab_v2.c Constants.h DIPs.h FileIO.h
	$(CC) $(CFLAGS) PhotoLab_v2.c -o PhotoLab.o

PhotoLabTest: FileIO.o libfilter.a PhotoLabTest.o
	$(CC) $(DEBUG) $(LFLAGS) PhotoLabTest.o FileIO.o -L. -lfilter -o PhotoLabTest -lm

PhotoLab_v2: FileIO.o libfilter.a PhotoLab.o
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o -L. -lfilter -o PhotoLab_v2 -lm 
