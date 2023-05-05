# Carly Retterer

## Indexer and Indextest

The indexer file reads in documents from a crawler produced directory and builds an index that keeps track of occurences of words in that document. It then writes out the indexer to a file. The indextest file loads an index file produced by the indexer and rewrites it to another file. 

## Usage:

The indexer is implemented using the 'indexer.c' file. It uses the 'index.c' module that is within the 'common' directory. To compile, you can type "make" in the indexer directory or "make indexer".

Indexer is tested in multiple ways including a 'testing.sh' file and the 'indextest.c' file. 'Indextest.c' is reliant upon 'index.c' module as well as the 'pagedir.c' file. 

Both can be compiled using make or make all. 

## Implementation:

See the implementation spec for more details.

# Assumptions

All assumptions were based on design and requirements spec. 