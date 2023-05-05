
/*
*  Indextest.c   Carly Retterer 5 May 2023 
*
*  This program tests the index.c module. It takes a file and an index to read in and writes out to another file. The first parameters is 
*  the file to read into and second argument is the file to read out too. It cleans up all data structures used at the end of the test. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <index.h>

/******** main () ********/
int
main(int argc, char* argv[]){

    //validating parameters
    if (argc != 3){
        fprintf(stderr, "Wrong number of parameters passed!\n");
        exit(1);
    }

    //assigning arguments
    char* fileReadIn = argv[1];
    char* fileReadOut = argv[2];

    //creating new index object, loading, and saving files
    index_t *index = index_load(fileReadIn);
    index_save(index, fileReadOut);

    //cleaning up data structures
    index_delete(index, itemdelete);
    exit(0);

}