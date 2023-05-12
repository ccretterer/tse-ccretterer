#ifndef QUERIER_H
#define QUERIER_H

#include <stdlib.h>
#include "../common/pagedir.h"
#include "../common/index.h"
#include <string.h>
#include "../libcs50/counters.h"
#include <ctype.h>
#include"../common/word.h"
#include"../libcs50/file.h"
#include"../common/webpage.h"
#include"../libcs50/hashtable.h"

/**************** Function Prototypes ****************/

/*
 * Validate the command-line parameters.
 * Returns true if the parameters are valid, false otherwise.
 */
bool validateParameters(char* fileName, char* pageDirectory);

/*
 * Validate the indexer file.
 * Returns true if the file is valid, false otherwise.
 */
bool indexer_validate(char* fileName);

/*
 * Read search queries from stdin and process them.
 */
void readSearchInqueries(char* pageDirectory, index_t* index);

/*
 * Store words from a line into an array.
 * Returns the number of words stored.
 */
int storeWords(char* line, char** words);

/*
 * Print the clean query to stdout.
 */
void print_clean_query(char** words, int count);

/*
 * Validate the query.
 * Returns true if the query is valid, false otherwise.
 */
bool validate_query(char** words, int count);

/*
 * Parse the query using the BNF grammar.
 */
void parse_query_bnf(char** words, int count, index_t* index, char* pageDirectory);

/*
 * Process the "and" and "or" sequences in the query and calculate scores.
 */
void process_and_or_sequences(index_t* index, char** words, int count, counters_t* total_scores);

/*
 * Copy a counter to another counter.
 */
void copy_counter(void* arg, const int key, int count);

/*
 * Intersect two counters.
 */
void counters_intersect(counters_t* ctrs1, counters_t* ctrs2);

/*
 * Helper function for counters_intersect.
 */
void counters_intersect_helper(void* arg, int key, int count);

/*
 * Union two counters.
 */
void counters_union(counters_t* result, counters_t* ctrs);

/*
 * Helper function for counters_union.
 */
void counters_union_helper(void* arg, int key, int count);

/*
 * Find the document with the maximum score in a counters object.
 * Returns the maximum score and stores the document ID in max_doc_id.
 */
int find_max_scoring_doc(counters_t* scores, int* max_doc_id);

/*
 * Helper function for find_max_scoring_doc.
 */
void find_max_helper(void* arg, const int key, const int count);

/*
 * Print the document information based on its ID and score.
 */
void print_doc_info(int doc_id, int score, char* page_directory);

/*
 * Counts documents with scores
 */
void count_docs_with_scores(void *arg, int key, int count);

/*
 * Rank and print all the results.
 */
void rank_and_print_all_results(counters_t* scores, char* pageDirectory);

#endif // QUERIER_H
