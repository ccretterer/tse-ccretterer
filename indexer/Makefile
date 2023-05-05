# Makefile for the "crawler" program that uses the "webpage", "bag", and "hashtable" module.
#
# Carly Retterer - April 2023

L = ../libcs50
C = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$(L) -I../common
LIBS = -lm
CLIB = $(C)/common.a
LLIB = $(L)/libcs50.a
LLIBS = $(CLIB) $(LLIB)


# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all valgrind clean

all: indexer indextest

indexer: indexer.o  $(LLIBS) 
	$(CC) $(CFLAGS) $^  -o $@

indextest: indextest.o  $(LLIBS) 
	$(CC) $(CFLAGS) $^  -o $@

indexer.o: $(L)/counters.h $(L)/webpage.h $(C)/word.h $(C)/index.h  $(C)/pagedir.h $(L)/hashtable.h

indextest.o: $(C)/index.h

test: ./indexer
	bash -v testing.sh > testing1.out

valgrind: ./indexer
	$(VALGRIND) valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./indexer ./letters outputLetters
	$(VALGRIND) valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./indexer ./toscrape outputToScrape
	$(VALGRIND) valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./indextest ./outputLetters indexTestOutputLetters

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f crawler
	rm -f core



