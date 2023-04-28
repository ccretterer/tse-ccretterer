# Makefile for the "crawler" program that uses the "webpage", "bag", and "hashtable" module.
#
# Carly Retterer - April 2023

L = ../libcs50

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

OBJS = pagedir.o
LIBS = -lm

.PHONY: all clean

all: pagedir

pagedir: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

pagedir.o: pagedir.c pagedir.h

clean:
	rm -f pagedir
	rm -f *~ *.o
	rm -rf *.dSYM
