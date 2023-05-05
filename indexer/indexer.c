/*
 * Indexer.c  Carly Retterer  April 30, 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "../common/index.h"
#include "webpage.h"
#include "counters.h"
#include "../common/pagedir.h"

int main(const int argc, char* argv[]);
void indexBuild(char *pageDirectory, index_t *index);
void indexPage(index_t *index, webpage_t *webpage, int id);

//parse the command line, validate parameters, initialize other modules
//call indexBuild, with pageDirectory

int main(const int argc, char *argv[]) {

    // Check the number of arguments
    if (argc != 3) {
        fprintf(stderr, "Error: Incorrect number of arguments.\n");
        exit(1);
    }

    // Set pageDirectory and fileName
    char *pageDirectory = argv[1];
    char *fileName = argv[2];

    // Check if the file is writable
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: File is not writable!\n");
        exit(1);
    } else {
        fclose(fp);
    }

    // Create a new index
    index_t *index = index_new(900);

    // Build the index
    indexBuild(pageDirectory, index);

    // Save the index to a file
    index_save(index, fileName);

    // Clean up
    index_delete(index, itemdelete);

    return 0;
}

/*
 * This function builds an index of words found in webpages in the given directory and adds their corresponding counts
 * to the index. It takes two parameters.
 *
 * pageDirectory: the directory containing the webpages to build the index from
 * index: the index to add the word counts to
 */
void indexBuild(char *pageDirectory, index_t *index) {
    int id = 1;
    webpage_t *webpage;

    //validating page directory
    if(pagedir_validate(pageDirectory) == false){
        fprintf(stderr, "Error: Pagedirectory is not a crawler created directory or path.\n");
        index_delete(index, itemdelete);
        exit(1);

    }

    // Load webpages from the page directory
    while ((webpage = pagedir_load(pageDirectory, id)) != NULL) {
        indexPage(index, webpage, id);
        id++;
        webpage_delete(webpage);
    }
}

/*
 * This function adds the words and their corresponding document IDs to the given index
 * for a single webpage. Normalizes the words before inserting them into the index. It takes three parameters.
 * 
 * index - the index to add the words to
 * webpage - the webpage to extract words from
 * id - the document ID of the webpage
 */
void indexPage(index_t *index, webpage_t *webpage, int id) {
    int pos = 0;
    char *currWord;
    counters_t *ctrs;

    // Iterate over each word in the webpage
    while ((currWord = webpage_getNextWord(webpage, &pos)) != NULL) {
        if (strlen(currWord) > 2) {
            currWord = normalizeWord(currWord);
            ctrs = index_find(index, currWord);

            //creating ctrs objects for words
            if (ctrs == NULL) {
                ctrs = counters_new();
                if (ctrs == NULL) {
                    fprintf(stderr, "Counters object failed to initialize!\n");
                    exit(1);
                }
                counters_add(ctrs, id);
                index_insert(index, currWord, ctrs);
            } else {
                counters_add(ctrs, id);
            }
        }
        free(currWord);  //free words
    }
}
