#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "index.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../libcs50/set.h"
#include "../libcs50/hash.h"


// Test function prototypes
void test_index_new();
void test_index_insert();
void test_index_find();
void test_index_print(); // Add this
void test_index_iterate(); // Add this
void test_index_save(); // Add this
void test_index_load(); // Add this
void test_index_delete(); // Add this
void simpleInsert(void *arg, const char *key, void *item);


int main(void) {
    printf("Starting index module tests...\n");
    
    test_index_new();
    test_index_insert();
    test_index_find();
    test_index_print(); // Call this
    test_index_iterate(); // Call this
    test_index_save(); // Call this
    test_index_load(); // Call this
    test_index_delete(); // Call this

    printf("All index module tests passed.\n");

    return 0;
}

void test_index_new() {
    printf("Testing index_new...\n");

    // Test with valid input
    index_t *index = index_new(10);
    assert(index != NULL);

    // Test with invalid input
    index_t *index2 = index_new(0);
    assert(index2 == NULL);

    // Clean up
    index_delete(index, NULL);

    printf("index_new tests passed.\n");
}

void test_index_insert() {
    printf("Testing index_insert...\n");

    // Create index and counters
    index_t *index = index_new(10);
    counters_t *ctrs = counters_new();

    // Test with valid input
    assert(index_insert(index, "test_key", ctrs));

    // Test with NULL values
    assert(!index_insert(NULL, "test_key", ctrs));
    assert(!index_insert(index, NULL, ctrs));
    assert(!index_insert(index, "test_key", NULL));

    // Clean up
    index_delete(index, NULL);

    printf("index_insert tests passed.\n");
}

void test_index_find() {
    printf("Testing index_find...\n");

    // Create index and counters
    index_t *index = index_new(10);
    counters_t *ctrs = counters_new();
    index_insert(index, "test_key", ctrs);

    // Test with valid input
    counters_t *found = (counters_t *)index_find(index, "test_key");
    assert(found == ctrs);

    // Test with NULL values
    assert(index_find(NULL, "test_key") == NULL);
    assert(index_find(index, NULL) == NULL);

    // Test with a non-existent key
    assert(index_find(index, "non_existent_key") == NULL);

    // Clean up
    index_delete(index, NULL);

    printf("index_find tests passed.\n");
}

// Add more test functions for other index.c functions


// Add this function
void test_index_print() {
    printf("Testing index_print...\n");

    // Create index and counters
    index_t *index = index_new(10);
    counters_t *ctrs = counters_new();
    index_insert(index, "test_key", ctrs);

    // Test with valid input
    index_print(index, stdout, NULL);

    printf("index_print tests passed.\n");
}

// Add this function
void test_index_iterate() {
    printf("Testing index_iterate...\n");

    // Create index and counters
    index_t *index = index_new(10);
    counters_t *ctrs = counters_new();
    index_insert(index, "test_key", ctrs);


    // Test with valid input
    index_iterate(index, NULL, simpleInsert);

    // Test with NULL values
    index_iterate(NULL, NULL, simpleInsert);
    index_iterate(index, NULL, NULL);

    printf("index_iterate tests passed.\n");
}

// Define a simple itemfunc for testing
void simpleInsert(void *arg, const char *key, void *item) {
    printf("Key: %s, Value: %p\n", key, item);
}

// Add this function
void test_index_save() {
    printf("Testing index_save...\n");

    // Create index and counters
    index_t *index = index_new(10);
    counters_t *ctrs = counters_new();
    index_insert(index, "test_key", ctrs);

    // Test with valid input
    index_save(index, "test_index_save.txt");

    // Clean up
    index_delete(index, NULL);
    remove("test_index_save.txt");

    printf("index_save tests passed.\n");
}

// Add this function
void test_index_load() {
    printf("Testing index_load...\n");

    // Create index and counters
    index_t *index = index_new(10);
    counters_t *ctrs = counters_new();
    index_insert(index, "test_key", ctrs);
    index_save(index, "test_index_load.txt");

    // Test with valid input
    index_t *loaded_index = index_load("test_index_load.txt");
    assert(loaded_index != NULL);

    // Test with non-existent file
    index_t *non_existent = index_load("non_existent.txt");
    assert(non_existent == NULL);

    // Clean up
    index_delete(index, NULL);
    index_delete(loaded_index, NULL);
    remove("test_index_load.txt");

    printf("index_load tests passed.\n");
}

// Add this function
void test_index_delete() {
    printf("Testing index_delete...\n");

    // Create index and counters
    index_t *index = index_new(10);
    counters_t *ctrs = counters_new();
    index_insert(index, "test_key", ctrs);

    // Test with valid input
    index_delete(index, NULL);

    // Test with NULL input
    index_delete(NULL, NULL);

    printf("index_delete tests passed.\n");
}

