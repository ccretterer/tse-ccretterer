# Makefile for the "crawler" program that uses the "webpage", "bag", and "hashtable" module.
#
# Carly Retterer - April 2023

L = ../libcs50

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I..$L

OBJS = pagedir.o index.o word.o 
LIB = common.a

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS) 

.PHONY: all clean

all: $(LIB)

word.o: 	word.h

index.o: word.h index.h 
	$(CC) $(CFLAGS) -I../libcs50 -L../libcs50 -lcs50 -c index.c ../libcs50/libcs50.a

pagedir.o: pagedir.h
	$(CC) $(CFLAGS) -I../libcs50 -L../libcs50 -lcs50 -c pagedir.c

clean:
	rm -f $(LIB)
	rm -f *~ *.o
	rm -rf *.dSYM

