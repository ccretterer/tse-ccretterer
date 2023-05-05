/*
 * set.c Carly Retterer 20 April 2023
 *
 * This program defines and creates the structure set. The struct set has multiple capacities. 
 * It stores key,item pairs. Users can insert, remove, iterate, print, and find items. Much of the code written here
 * was adapted from example code from bag.
 *
 */

#include <stdio.h>
#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void(*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t*, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void(*itemdelete)(void* item) );

/******* local types **********/
typedef struct setnode {
  void* item;
  char* key;
  struct setnode* next;
} setnode_t;

/********** global types **********/
typedef struct set {
  setnode_t* head;
} set_t;

/******* set_new() *******/
/* see set.h for description */
set_t* 
set_new(void){
  set_t* set = malloc(sizeof(set_t));

  if (set == NULL) {
    return NULL;  //Error: memory allocation failed
  }

  set->head = NULL;
  return set;
}

/****** set_insert() *******/
/* see set.h for description */

bool
set_insert(set_t* set, const char* key, void* item){
  
  char* cpKey;
  //checking to see if parameters are NULL
  if (set == NULL || key == NULL || item == NULL){
    return false;
  }

  //check to see if key is already present
  for (setnode_t* curr = set->head; curr != NULL && curr->key != NULL; curr = curr->next){
    if (strcmp(curr->key, key) == 0){
      return false;
    }
  }

  setnode_t* node = malloc(sizeof(setnode_t));
  if (node == NULL) {
    return false;
  }
  
  //come back and look at this?
  cpKey = (char*) malloc(strlen(key) +1);
  strcpy(cpKey, key);
  node->key = cpKey;
  if(node->key == NULL){
    free(node);
    return false;
  }

  //node->key = key;
  node->next = set->head;
  node->item = item;
  set->head = node;

  return true;

}

/********** set_find() ******/
/*  see set.h for description */
void*
set_find(set_t* set, const char* key){

  //if set or key are NULL
  if (set == NULL || key == NULL){
    return NULL;
  }

  //iterating through set
  for (setnode_t* curr = set->head; curr != NULL; curr = curr->next){
    if (strcmp(curr->key, key) == 0){
      return curr->item;
    }
  }

  return NULL;  //if no key is found

}

/******* set_print() *****/
/* see set.h for description */
void
set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) ) {
  if (set == NULL) {
    printf("hello");
    return;
  } else {
    fprintf(fp, "{");
    //iterating through set 
    for (setnode_t* node = set->head; node != NULL; node = node->next){
      if (itemprint != NULL) {
        (*itemprint)(fp, node->key, node->item);
      }   
      if (node->next != NULL) {
        fprintf(fp, ",");
      }
    }
    fprintf(fp, "}");
    fprintf(fp, "\n");
  }
}

/****** set_iterate() *****/
/* see set.h for description */
void
set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) {
  if (set == NULL || itemfunc == NULL) {
    return;
  } else{
    //iterating through set
    for (setnode_t* node = set->head; node != NULL; node = node->next){
      itemfunc(arg, node->key, node->item);
    }
  }
}

/****** set_delete() *******/
/* see set.h fro description */
void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    if (set == NULL) {
        return;
    } else {
        setnode_t *node = set->head;
        setnode_t *next;
        while (node != NULL) {
            next = node->next;
            if (itemdelete != NULL) {
                itemdelete(node->item);   //calling itemdelete
            }
            free(node->key);   //free node key
            free(node);        //free node
            node = next;
        }
        free(set);   //freeing set
    }
}




