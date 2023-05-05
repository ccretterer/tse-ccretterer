/*
 * counters.c Carly Retterer April 20, 2023
 *
 * see counters.h for more information
 *
 * Spring 2023, CS50
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"



counters_t* counters_new(void);
int counter_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);

/*********local types********/
typedef struct countersnode {
  int count;
  int  key;
  struct countersnode *next;
} countersnode_t;

/*******global types*******/
typedef struct counters{
  countersnode_t* head;
} counters_t;

/*****counters_new()*********/
/* see counters.h for description */
counters_t*
counters_new(void){

  counters_t* counters = malloc(sizeof(counters_t));  //allocating space
  if (counters != NULL){
    counters->head = NULL;
  }
  return counters;
}

/**********counters_add()*************/
/* see counters.h for description */
int counters_add(counters_t* ctrs, const int key) {
  if (ctrs == NULL || key <= 0) {   //checking to see if CTRS and key are valid inputs 
    return 0;
  }

  // Iterate through the counters to find the key
  for (countersnode_t* countersnode = ctrs->head; countersnode != NULL; countersnode = countersnode->next) {
    if (countersnode->key == key) {
      // If key is found, increment the count and return the updated count
      countersnode->count++;
      return countersnode->count;
    }
  }

  // If the key is not found in the counters, create a new node
  countersnode_t* node = malloc(sizeof(countersnode_t));  // create new node

  if (node == NULL) {
    return 0;
  } else {
    node->key = key;
    node->count = 1;
    node->next = ctrs->head;
    ctrs->head = node;
  }

  return 1;  // Return the initial count for the newly added key
}

/*************counters_get()*******/
/* see counters.h for description */
int 
counters_get(counters_t* ctrs, const int key){
  //checking to see if ctrs is null
  if (ctrs == NULL) {
    return 0;
  }

  //iterating through the ctrs set
  for (countersnode_t* countersnode = ctrs->head; countersnode != NULL; countersnode=countersnode->next){
    if (countersnode->key == key){
      return countersnode->count;
    }
  }
  return 0; //case where the key doesn't exist
}

/*********counters_set()*********/
/*  see counters.h              */
bool 
counters_set(counters_t* ctrs, const int key, const int count){
  if (ctrs == NULL || key < 0 || count < 0 ){ //add some check to see if out of memory???
    return false;
  }

  //iterating through counters
  for (countersnode_t* countersnode = ctrs->head; countersnode != NULL; countersnode=countersnode->next){
    if (countersnode->key == key){
      countersnode->count = count;
      return true;
    }
  }

  //if the key is not found, add it
  //countersnode_t* node = malloc(sizeof(counters_t));
  countersnode_t* node = malloc(sizeof(countersnode_t));


  if (node == NULL){
    return false;   //returns false if out of memory 
  } else {
    node->key = key;
    node->count = count;
    node->next = ctrs->head;
    ctrs->head = node;
    return true;
  }
}

/*******counters_print()******/
/* see counters.h for description */
void
counters_print(counters_t* ctrs, FILE* fp){
  //checking for NULL ctrs, fp
  if (fp == NULL){
    return;
  }

  if (ctrs == NULL){
    printf("null\n");
    return;
  }
  
  //printing out the counters 
  fprintf(fp, "{");
  for (countersnode_t* countersnode = ctrs->head; countersnode != NULL; countersnode = countersnode->next) {
      fprintf(fp, " %d: %d", countersnode->key, countersnode->count);
      if(countersnode->next != NULL){
        fprintf(fp, ", ");
      }
  }
  fprintf(fp, " }\n");
}

/*******counters_iterate()******/
/* see counters.h description */
void
counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void*arg, const int key, const int count)){
  if (ctrs == NULL || itemfunc == NULL){
    return;
  } else { 
    //looping through ctrs 
    for(countersnode_t* countersnode = ctrs->head; countersnode != NULL; countersnode = countersnode->next){
      itemfunc(arg, countersnode->key, countersnode->count);
    }
  }
}

/*******counters_delete*****/
/* see counters.h description */
void
counters_delete(counters_t* ctrs){
  if (ctrs != NULL) {
    countersnode_t* countersnode = ctrs->head;
    //iterating through counters
    while (countersnode != NULL) {
      countersnode_t* next = countersnode->next;
      free(countersnode);   //freeing countersnode
      countersnode = next;
    }
    free(ctrs);  //freeing ctrs 
  }
}

