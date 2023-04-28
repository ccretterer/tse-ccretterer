# Makefile for the "crawler" program that uses the "webpage", "bag", and "hashtable" module.
#
# Carly Retterer - April 2023

L = ../libcs50

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$(L) -I../common
LIBS = -lm
LLIBS = $(L)/libcs50.a

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: all valgrind clean

all: crawler

crawler: crawler.o ../common/pagedir.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: $(L)/bag.h $(L)/file.h $(L)/hashtable.h $(L)/webpage.h ../common/pagedir.h

../common/pagedir.o: ../common/pagedir.h ../common/pagedir.c
	$(CC) $(CFLAGS) -c ../common/pagedir.c -o ../common/pagedir.o

test: ./crawler 
	bash -v testing.sh > testing.out

valgrind: ./crawler
	$(VALGRIND) ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ./letters 0
	$(VALGRIND) ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ./toscrape 0
	$(VALGRIND) ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ./wiki 0

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f crawler
	rm -f core



