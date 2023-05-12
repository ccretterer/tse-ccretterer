/*
 * querier.c
 *
 * Description: This program reads a text file created by the crawler and performs search queries.
 *
 * The program has several key functions: 
 * - It validates the parameters for the program, including a filename and a page directory.
 * - It reads the search queries from the user.
 * - It stores the words from the search query and normalizes them.
 * - It validates the search queries based on certain criteria.
 * - It parses the queries using a Boolean Retrieval Model, implementing AND and OR operators.
 * - It ranks and prints the results of the search queries.
 *
 * Input: Filename and page directory.
 * Output: Results of the search queries, including document ID, score, and URL.
 *
 *
 * Note: This program uses the common library provided by the Tiny Search Engine (TSE) architecture.
 * The common library provides functions for web crawling, parsing HTML, normalizing words, and manipulating data structures.
 */

#include <stdlib.h>
#include "../common/pagedir.h"
#include "../common/index.h"
#include <string.h>
#include "../libcs50/counters.h"
#include <ctype.h>
#include"../common/word.h"
#include"../libcs50/file.h"
#include"../libcs50/webpage.h"
#include"../libcs50/hashtable.h"



/**************** local types ****************/
typedef struct twoCounters {
    counters_t *ctrs1;  //result ctrs
    counters_t *ctrs2; 
} twoCounters_t;

typedef struct max_data {
    int max_doc_id;
    int max_score;
} max_data_t;

/**************** Function Prototypes ****************/
bool validateParameters(char* fileName, char* pageDirectory);
bool indexer_validate(char* fileName);
void readSearchInqueries(char* pageDirectory, index_t* index);
int storeWords(char* line, char** words);
void print_clean_query(char** words, int count);
bool validate_query(char** words, int count);
void parse_query_bnf(char** words, int count, index_t *index, char* pageDirectory);
void process_and_or_sequences(index_t* index, char **words, int count, counters_t* total_scores);
void copy_counter(void* arg, const int key, int count);
void counters_intersect(counters_t *ctrs1, counters_t *ctrs2);
void counters_intersect_helper(void* arg, int key, int count);
void counters_union(counters_t *result, counters_t *ctrs);
void counters_union_helper(void *arg, int key, int count);
int find_max_scoring_doc(counters_t *scores, int *max_doc_id);
void find_max_helper(void *arg, const int key, const int count);
void print_doc_info(int doc_id, int score, char *page_directory);
void rank_and_print_all_results(counters_t *scores, char *pageDirectory, int num_docs);
void count_docs_with_scores(void *arg, int key, int count);


int 
main(int argc, char* argv[]){
    //parse args
    if (argc != 3){
        fprintf(stdout, "Error: incorrect parameters passed!\n");
        exit(1);
    }
    
    //assign values 
    char* pageDirectory = argv[1];
    char* fileName = argv[2];
    //validate pathways
    if(!validateParameters(fileName, pageDirectory)){
        fprintf(stdout, "Error: parameters are not created by indexer or crawler!\n");
        exit(1);
    }

    // // Try to open the file for reading
    // FILE* file = fopen(fileName, "r");

    index_t *index = index_load(fileName);
    if (index == NULL) {
        fprintf(stderr, "Error loading indexer file into index structure!\n");
        exit(1);
    }

    readSearchInqueries(pageDirectory, index);
    index_delete(index, itemdelete);

    exit(0);
}


/**************** validateParameters() ****************/
bool
validateParameters(char* fileName, char* pageDirectory){
    if(!pagedir_validate(pageDirectory)){
        return false;
    }
    if (!indexer_validate(fileName)){
        return false;
    }
    return true;  

}

/**************** indexer_validate() ****************/
bool
indexer_validate(char* fileName){

    // Check if the indexFilename is not NULL
    if (fileName == NULL) {
        fprintf(stderr, "indexFilename is NULL!\n");
        return false;
    }

    // Try to open the file for reading
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open the file: %s\n", fileName);
        return false;
    }

    //check if file is required format
    //closing file
    fclose(file);
    return true;
}

/**************** readSearchInqueries() ****************/
void
readSearchInqueries(char* pageDirectory, index_t* index){
    char* line;
    printf("Query: ");
    while((line = file_readLine(stdin)) != NULL){
        char** words = malloc(sizeof(char*) * 20);  //array for words

        int count = storeWords(line, words);
        //check to ensure there were words in the query
        if (count != 0 && words != NULL){
            print_clean_query(words, count);
            if(validate_query(words, count)){
                parse_query_bnf(words, count, index, pageDirectory);
            }
        }

        printf("Query: ");

        //free all the words in the array
        for (int i = 0; i < count; i++) {
            free(words[i]);
        }
        free(words);

        // free line
        free(line);
    }
}


/**************** storeWords() ****************/
int
storeWords(char* line, char** words){
    int sizeLine = strlen(line);
    int count = 0;

    int c;
    char* currWord;

    // Check for invalid characters in the query
    for (int i = 0; i < sizeLine; i++) {
        int k = line[i];
        if (!isalpha(k) && !isspace(k)) {
            fprintf(stderr, "Error: character in input is non-alphanumeric or a space!\n");
            printf("--------------\n");
            return 0;
        }
    }

    // Add characters to the word array
    for (int i = 0; i < sizeLine; i++) {
        c = line[i];
        if (isalpha(c)) {
            currWord = &line[i];

            // Find the end of the word
            int j = i;
            while (isalpha(line[j])) {
                j++;
            }
            int wordLength = j - i;
            
            // Allocate memory for the word
            words[count] = malloc(sizeof(char) * (wordLength + 1));  //i need to free this memory somewhere
            
            // Copy the word to the words array
            strncpy(words[count], currWord, wordLength);
            words[count][wordLength] = '\0';

            // Normalize the word
            normalizeWord(words[count]);

            count++;
            // Update the loop variable
            i = j - 1;
        }
    }
    
    return count;
}


/**************** print_clean_query() ****************/
void
print_clean_query(char** words, int count) {

    printf("Query: ");
    for (int i = 0; i < count; i++){
        printf("%s ", words[i]);
    }
    printf("\n");
    printf("--------------\n");
}

/**************** valdiate_query() ****************/
bool
validate_query(char** words, int count){

    char* currWord = words[0];
    char* prevWord = currWord;

    for(int i = 0; i < count; i++){
        currWord = words[i];

        if(i == 0 && (strcmp(currWord, "and") == 0 || strcmp(currWord, "or") == 0)){
            fprintf(stdout, "Error: operator placed at beginning of query!\n");
            printf("--------------\n");
            return false;
        }
        if(i == count - 1 && (strcmp(currWord, "and") == 0 || strcmp(currWord, "or") == 0)){
            fprintf(stdout, "Error: operator placed at end of query!\n");
            printf("--------------\n");
            return false;
        }
        if((strcmp(currWord, "and") == 0 || strcmp(currWord, "or") == 0) && (strcmp(prevWord, "and") == 0 || strcmp(prevWord, "or") == 0)){
            fprintf(stdout, "Error: two operators in a row!\n");
            printf("--------------\n");
            return false;
        }
        prevWord = currWord;
        
    }
    return true;
}

/**************** parse_query_bnf() ****************/
void
parse_query_bnf(char** words, int count, index_t *index, char* pageDirectory){

    counters_t* total_scores = counters_new();  //stores final score for each document

    process_and_or_sequences(index, words, count, total_scores); //calculate scores

    //get the documents that have scores
    int num_doc_with_scores = 0;
    counters_iterate(total_scores, &num_doc_with_scores, count_docs_with_scores);

    if(num_doc_with_scores == 0){
        printf("No documents match!\n");
    }
    
    //selection sort of the scores
    rank_and_print_all_results(total_scores, pageDirectory, num_doc_with_scores);

    //clean up data structures
    counters_delete(total_scores);
    
}

/**************** count_docs_with_scores() ****************/
void
count_docs_with_scores(void *arg, int key, int count){
    int *countDocs = arg;

    if(countDocs != NULL && count != 0){
        (*countDocs)++;
    }
} 

// /**************** process_and_or_sequences() ****************/
void
process_and_or_sequences(index_t *index, char **words, int count, counters_t *total_scores) {
    int i = 0;
    counters_t *or_result = counters_new(); // Initialize the result counter for OR sequences


    while (i < count) {
        counters_t *and_result = NULL; // Initialize a new counter to store the result of the AND sequence
        bool found_missing_word = false; // Initialize a flag to track if any word in the AND sequence is missing from the index

        // Process AND sequences within the current OR sequence
        while (i < count && strcmp(words[i], "or") != 0) {
            // If the word is not "and", process the word
            if (strcmp(words[i], "and") != 0) {
                counters_t *ctrs = index_find(index, words[i]); // Find counters for the current word

                if (ctrs != NULL) { // If the counters exist
                    if (and_result == NULL) { // If and_result is not initialized, copy the current counters
                        and_result = counters_new();
                        counters_iterate(ctrs, and_result, copy_counter);
                    } else { // Otherwise, intersect the current counters with and_result
                        counters_intersect(and_result, ctrs);
                    }
                } else { // If the counters do not exist, set the found_missing_word flag to true
                    found_missing_word = true;
                }
            }
            i++; // Move to the next word
        }

        if (!found_missing_word && and_result != NULL) { // If no missing word found and and_result has a valid value
            counters_union(or_result, and_result); // Combine the scores of the AND sequence with the OR result
            counters_delete(and_result); // Delete the and_result counter
        } else if (and_result != NULL) { // If found_missing_word is true, delete and_result
            counters_delete(and_result);
        }

        if (i < count && strcmp(words[i], "or") == 0) {
            i++; // Move to the next word after "or"
        }
    }

    // Copy the OR result to the total scores
    counters_iterate(or_result, total_scores, copy_counter);
    counters_delete(or_result); // Delete the or_result counter
}


/**************** Functions to help with parsing query ****************/
/**************** copy_counter() ****************/
void 
copy_counter(void *arg, const int key, int count){
    counters_t* copy_counter = arg;
    counters_set(copy_counter, key, count);
}

/**************** counters_intersect() ****************/
void 
counters_intersect(counters_t *ctrs1, counters_t *ctrs2){
    twoCounters_t counters = {ctrs1, ctrs2}; // fixed
    counters_iterate(ctrs1, &counters, counters_intersect_helper);
}

/**************** counters_intersect_helper() ****************/
void 
counters_intersect_helper(void* arg, int key, int count) {
    twoCounters_t* counters = arg;
    int num = 0;
    if (count > counters_get(counters->ctrs2, key)) {
        num = counters_get(counters->ctrs2, key);
    } else {
        num = count;
    }
    counters_set(counters->ctrs1, key, num);
}

/**************** counters_union() ****************/
void 
counters_union(counters_t *result, counters_t *ctrs) {
    //assert(result, "Counters union error: result");
    //assert(ctrs, "Counters union error: ctrs");

    counters_iterate(ctrs, result, counters_union_helper);
}

/**************** counters_union_helper() ****************/
void 
counters_union_helper(void *arg, int key, int count) {
    counters_t *result = arg;

    int sum = counters_get(result, key) + count;
    counters_set(result, key, sum);
}


/**************** Functions to help with printing the results and doing a selection sort****************/
/* Find the maximum scoring document in the counters object This function will iterate through 
the scores counters object to find the document with the maximum score.
/**************** find_max_scoring_doc() ****************/
int
find_max_scoring_doc(counters_t *scores, int *max_doc_id) {
    max_data_t data = { .max_doc_id = -1, .max_score = 0 };

    //iterate through and get max score of document
    counters_iterate(scores, &data, find_max_helper);
    *max_doc_id = data.max_doc_id;
    return data.max_score;
}

/**************** find_max_helper() ****************/
void
find_max_helper(void *arg, const int key, const int count) {
    max_data_t *data = arg;

    if (count > data->max_score) {
        data->max_doc_id = key;
        data->max_score = count;
    }
}


/* Print the document information based on its ID and score */
/**************** print_doc_info() ****************/
void 
print_doc_info(int doc_id, int score, char *page_directory) {
    // Load the webpage details using the pagedir_load() function
    webpage_t *page = pagedir_load(page_directory, doc_id);

    if (page == NULL) {
        fprintf(stderr, "Error: unable to load webpage details for doc_id %d\n", doc_id);
        return;
    }

    // Fetch the URL and title of the document from the webpage_t structure
    char *url = webpage_getURL(page);

    // Print the document details
    printf("Document ID: %d\n", doc_id);
    printf("Score: %d\n", score);
    printf("URL: %s\n", url);
    printf("\n");

    // Cleanup
    webpage_delete(page);
}

/* Rank and print the results*/
/**************** rank_and_print_results() ****************/
void 
rank_and_print_all_results(counters_t *scores, char *pageDirectory, int num_docs) {
    int max_doc_id;
    int max_score;
    int i = 0;


    // Iterate through the documents with non-zero scores
    while (i <= num_docs) {
        max_score = find_max_scoring_doc(scores, &max_doc_id);

        // If a valid document was found, print its information and set its score to zero
        if (max_score > 0) {
            print_doc_info(max_doc_id, max_score, pageDirectory);
            counters_set(scores, max_doc_id, 0);
        }
        i++;
    }
    printf("--------------\n");
}






