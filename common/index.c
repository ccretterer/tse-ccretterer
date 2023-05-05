/**
 *  index.c - CS50 'index' module
 *  see index.h for more information
 *
 *  This program adapted and modified code from bag.c
 *
 *  Carly Retterer, April 20, 2023. 
 */

#include<stdio.h>
#include<stdlib.h>
#include "index.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../libcs50/set.h"
#include "../libcs50/hash.h"


/******* global types ******/
typedef struct index {
  hashtable_t *ht;
} index_t;

//typdef hashtable_t index_t;

/****** index_new() ******/
/* see index.h for description */
index_t* 
index_new(const int num_slots){
  index_t* index = malloc(sizeof(index_t)); //allocating space
  if (index != NULL){
    if (num_slots > 0) {
      index->ht= hashtable_new(num_slots);
      if(!index->ht){
        free(index);   //case where the hashtable isn't correctly implemented
        return NULL;
      }
      return index;
    }
  }
  return NULL;   //case where index isn't initialized
}


/****** index_insert() *******/
/* see index.h for description */
bool
index_insert(index_t* index, const char* key, counters_t *ctrs){

  if(index == NULL || key == NULL || ctrs == NULL){  //checking for null values
    return false;
  }else{
    return hashtable_insert(index->ht, key, ctrs); 
  }
}

/******* index_find() ******/
/* see index.h for description */
counters_t*
index_find(index_t* index, const char* key){
  if (index == NULL || key == NULL){   //checking for null values
    return NULL;
  } else{
    return (counters_t*) hashtable_find(index->ht, key);
  } 
}

/******** index_print() *******/
/* see index.h for description */
void
index_print(index_t* index, FILE* fp, void(*itemprint)(FILE* fp, const char* key, void* item)){
  if (fp == NULL){
    return;
  } else if (index == NULL){   //checking for null values
    printf("(null)");
  } else{ 
    hashtable_print(index->ht, fp, itemprint);
  }
}

/****** index_iterate() *****/
/* see index.h for description */
void
index_iterate(index_t* index, void* arg, void (*itemfunc)(void* arg, const char* key, void* item)){
  if (index == NULL || itemfunc == NULL){  //checking for null values
    return;
  } else{
    hashtable_iterate(index->ht, arg, itemfunc);
  }
}

/****** index_save() ******/
/* see index.h for description */
void index_save(index_t *index, const char *filename) {
    // Implement a function to save the index to a file
    FILE *file = fopen(filename, "w");
    if(file == NULL){
      fprintf(stderr, "Error opening or creating file in index_save: %s\n", filename);
      exit(1); //error reading or opening file
    }
    hashtable_iterate(index->ht, file, printWord); //where arg is a way to set counters?
    fclose(file);
}

/****** printWord() ******/
/* see index.h for description */
void printWord(void* arg, const char* key, void *ctrs){
  FILE *fp = arg;

  fprintf(fp, "%s", key);
  counters_iterate(ctrs, fp, printCount);
  fprintf(fp, "\n");
}

/****** printCount() ******/
/* see index.h for description */
void printCount(void *arg, const int key, int count){
  FILE* fp = arg;
  fprintf(fp, " %d %d", key, count);
}

/****** index_load() ******/
/* see index.h for description */
index_t *index_load(const char *filename) {
    // Implement a function to load an index from a file
    FILE *file = fopen(filename, "r");
    if(file == NULL){
      fprintf(stderr, "Error opening file in index_load: %s\n", filename);
      return NULL; //error opening filename 
    }

    //finding size of file to create an index
    int sizeFile = file_numLines(file);
    index_t* index = index_new(sizeFile);
    if(index == NULL){
      fprintf(stderr, "Index memory cannot be allocated in index_load!\n");
      return NULL;
    }
    char* word;   //keeps track of each word, references file.c
    int docID;    //keeps track of ID
    int count;    //keeps track of count for each word

    while((word = file_readWord(file)) != NULL){
      counters_t* ctrs = counters_new();  //creating new counters object for each word
      if(ctrs == NULL){
        fprintf(stderr, "Counters object could not be intialized in index_load!\n");
        return NULL;
      }
      while(fscanf(file, "%d %d ", &docID, &count) == 2){
        counters_set(ctrs, docID, count);
      }
      index_insert(index, word, ctrs);
      free(word);
    }
    fclose(file);

    return index;
    
}

/****** index_delete() *****/
/* see index.h for description */
void
index_delete(index_t* index, void (*itemdelete)(void* item)){
  if (index == NULL){
    return;
  } else {
    hashtable_delete(index->ht, itemdelete);  //calling hashtable_delete on the index hashtable
    free(index);
  }
}


void itemdelete(void *item) {
  if (item != NULL) {
    counters_t *ctrs = item;
    counters_delete(ctrs);
  }
}
