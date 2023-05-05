# Indexer

## Carly Retterer, CS50, May 2023

## Indexer Implementation

The indexer is implemented with `indexer.c`. `Indexer.c` uses functions defined in the `index` module. The `index.c` module belongs to the common library.

## Indexer.c

The `indexer.c` file uses the `index` module within the common library, but `indexer.c` initializes and executes the indexer.

The pseudocode is as follows:

Parse the command line, validate parameters, initialize other modules
Call indexBuild, with pageDirectory
Call indexPage, with index, webpage, docID 

The `main()` function parses the command line, validates parameters, and initializes other modules, including calling `index_build()` which builds the index by pulling all webpages within the page directory, `index_save()` which saves the index to the input file to be written out to, and `index_delete()` which deletes the index and other objects created.

## Index.c

The `index` module is in the common directory and includes most functions used by indexer and indextest.

The functions within the `index` module are as follows:

- `index_new()` creates a new index data structure. If an index is successfully created it is returned, otherwise a NULL pointer is returned.
- `index_insert()` inserts a key and counter pair to the given index. It returns true if successfully returned, otherwise it returns false.
- `index_delete()` deletes the index. It uses a helper function to delete the counter items within the index.
- `index_save()` takes the input filename and writes the index to it. It is written one word per line, followed by id and count. It also uses helper functions to do so.
- `index_load()` takes a file storing an index. It returns the index if successful or returns a NULL pointer otherwise.

Errors are all printed to stderr and exit with a non-zero exit code.

## Testing Plan

The indexer can be tested using crawler-created directories. It can read, write, and check files. The indexer can also read from an indexer file to an index and rewrite that index to another file. This functionality of indexer is tested and demonstrated in indextest. The pseudocode is as follows:

``` Validate and assign parameters
    Create a new index object
    Call pagedir_load(file1) and store it in the index object
    Call pagedir_save(index, file2)
    Clean up data structures ```
