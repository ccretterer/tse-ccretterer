/**
 *  hashtable.c - CS50 'hashtable' module
 *  see hashtable.h for more information
 *
 *  This program adapted and modified code from bag.c
 *
 *  Carly Retterer, April 20, 2023. 
 */

#include<stdio.h>
#include<stdlib.h>
#include "hashtable.h"
#include "set.h"
#include "hash.h"

/******* global types ******/
typedef struct hashtable {
  set_t **set;
  int num_slots;
} hashtable_t;


/****** hashtable_new() ******/
/* see hashtable.h for description */
hashtable_t* 
hashtable_new(const int num_slots){
  hashtable_t* ht = malloc(sizeof(hashtable_t)); //allocating space
  if (ht != NULL){
    if (num_slots > 0) {
      ht->set = malloc(sizeof(set_t*)*num_slots);
      ht->num_slots = num_slots;
      
      //initializing sets into hash slots
      for(int i = 0; i < num_slots; i++){
        ht->set[i] = set_new();
      }
      return ht;
    }
  }
  return NULL;   //case where hash table isn't initialized
}


/****** hashtable_insert() *******/
/* see hashtable.h for description */
bool
hashtable_insert(hashtable_t* ht, const char* key, void* item){

  if(ht == NULL || key == NULL || item == NULL){  //checking for null values
    return false;
  }else{
    int hash = hash_jenkins(key, ht->num_slots);  //use hash_jenkins function provided by hash.h
    return set_insert(ht->set[hash], key, item);
  }
}

/******* hashtable_find() ******/
/* see hashtable.h for description */
void*
hashtable_find(hashtable_t* ht, const char* key){
  if (ht == NULL || key == NULL){   //checking for null values
    return NULL;
  } else{
    int hash = hash_jenkins(key, ht->num_slots);  //use hash_jenkins function provided by hash.h
    return set_find(ht->set[hash], key);
  } 
  return NULL;   //the case where key is not found
}

/******** hashtable_print() *******/
/* see hashtable.h for description */
void
hashtable_print(hashtable_t* ht, FILE* fp, void(*itemprint)(FILE* fp, const char* key, void* item)){
  if (fp == NULL){
    return;
  } else if (ht == NULL){   //checking for null values
    printf("(null)");
  } else{ 
    if (itemprint != NULL){
      for(int i = 0; i<ht->num_slots; i++){
        set_print(ht->set[i], fp, (*itemprint));  //iterating through set, callign itemprint
      }
    } else{
      for(int i = 0; i<ht->num_slots; i++){
        printf(" \n");
      }
    }
  }

}

/****** hashtable_iterate() *****/
/* see hashtable.h for description */
void
hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item)){
  if (ht == NULL || itemfunc == NULL){  //checking for null values
    return;
  } else{
    for(int i = 0; i<ht->num_slots; i++){
      set_iterate(ht->set[i], arg, (*itemfunc)); //iterating through set
    }
  }
}

/****** hashtable_delete() *****/
/* see hashtable.h for description */
void
hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item)){
  if (ht == NULL){
    return;
  } else if (itemdelete != NULL){
    for (int i = 0; i<ht->num_slots; i++){
      set_delete(ht->set[i], itemdelete);  //callign set_delete on each set, and itemdelete 
    }
    free(ht->set);   //freeing the set 
    free(ht);   //freeing the table
  }
}
