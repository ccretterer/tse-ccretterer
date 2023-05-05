/*
 * Index.h - index module
 *
 * Carly Retterer, May 2023
 *
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Include header files for other data structures needed by the index module
#include "index.h"
#include "hashtable.h"
#include "counters.h"
#include "file.h"
#include "set.h"
#include "hash.h"

// Define an opaque type representing the index structure
typedef struct index index_t;

/**************** index_new ***************/
/* Creates a new index with the given number of slots 
* Returns:
* A pointer to the newly created index on success, or NULL on failure.
* Caller is responsible for calling index_delete to free memory when finished using the index.
*/
index_t *index_new(const int num_slots);

/****** index_insert() ******/
/* Inserts the given key-counter pair into the index.
* Returns:
* true if the insert is successful, or false if there is an error or the input parameters are NULL.
* Caller is responsible for freeing the memory allocated for the counters structure.
* Caller is also responsible for calling index_delete to free memory when finished using the index.
*/
bool index_insert(index_t *index, const char *key, counters_t *ctrs);

/****** index_find() ******/
/*  Finds the counters structure associated with the given key in the index.
* Returns:
* A pointer to the counters structure associated with the given key if found, or NULL if not found or the input parameters are NULL.
* Caller is also responsible for calling index_delete to free memory when finished using the index.
*/
counters_t* index_find(index_t *index, const char *key);

/****** index_print() ******/
/* Prints the index to the given file pointer using the provided itemprint function
* Returns:
* Nothing.
* Caller is also responsible for calling index_delete to free memory when finished using the index.
*/
void index_print(index_t *index, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item));

/****** index_iterate() ******/
/*  Iterates over the index and calls the given itemfunc function on each key-counter pair.
* Returns:
* Nothing.
* Caller is also responsible for calling index_delete to free memory when finished using the index.
*/
void index_iterate(index_t *index, void *arg, void (*itemfunc)(void *arg, const char *key, void *item));

/****** index_save() ******/
/* Saves the index to a file. It creates or overwrites the file, and writes each key-counter 
* pair to the file using the printWord function.
* Returns:
* Nothing.
*
* Caller is also responsible for calling index_delete to free memory when finished using the index.
*/
void index_save(index_t *index, const char *filename);


/****** index_load() ******/
/* Loads an index from a file.
* Returns:
* A pointer to the loaded index on success, or NULL on failure.
* Caller is responsible for calling index_delete to free memory when finished using the index.
*/
index_t *index_load(const char *filename);


/****** index_delete() ******/
/* Deletes the index and optionally frees its contents using the provided itemdelete function.
* Returns:
* Nothing.
* Caller is responsible for ensuring that the itemdelete function properly frees the contents of the index.
*/
void index_delete(index_t *index, void (*itemdelete)(void *item));


/****** printWord() ******/
/* Prints a key-counter pair to the given file pointer.
* Returns:
* Nothing.
* Caller is responsible for ensuring that the printCount function properly formats the key and count.
*/
void printWord(void* arg, const char* key, void *ctrs);

/****** printCount() ******/
/* Prints a count to the given file pointer.
* Returns:
* Nothing.
*/
void printCount(void *arg, const int key, int count);


/****** itemdelete() ******/
/* Deletes the counters structure pointed to by the given item pointer.
* Returns:
* Nothing.
*/
void itemdelete(void *item);

#endif // __INDEX_H
