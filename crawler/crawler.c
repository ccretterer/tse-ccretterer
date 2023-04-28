/*
* Crawler.c   Carly Retterer   22 April 2023
*  
*  This is the crawler.c file that contains five functions. It takes in arguments from the user, parses those arguments,
* crawls webpages using the seedURL to the given maximum depth and then scans those pages for additional URLs. See crawler.h for 
* more description. 
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "hashtable.h"
#include "webpage.h"
#include "../common/pagedir.h"

int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
static void itemdelete(void *item);

/**************** main() ****************/
/* see crawler.h for description */
int 
main(const int argc, char* argv[]){
    int maxDepth = 0;   //initializing variables
    char* seedURL = NULL;       //initializing variables
    char* pageDirectory = NULL;  //initializing variables

    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
    crawl(seedURL, pageDirectory, maxDepth);

    free(pageDirectory);  //free memory for pagedirectory

    exit(0); //exiting if program run is successful
}

/**************** parseArgs() ****************/
/* see parseArgs.h for description */
static void
parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth){

    //parse args
    if (argc != 4){
        fprintf(stderr, "Usage: %s seedURL, pageDirectory, maxDepth\n", argv[0]);
        exit(1);
    }

    //checking for the case in which any arguments are NULL
    if (argv[1] == NULL|| argv[2] == NULL|| argv[3] == NULL) {
        fprintf(stderr, "Arguments passed in are incorrect!\n");
        exit(5);
    }

    *maxDepth = strtol(argv[3], NULL, 10);  //converting string to integer
    //for maxDepth, ensure it an integer in a specified range
    if (*maxDepth < 0 || *maxDepth > 10){
        fprintf(stderr, "Usage %d max depth is not within the specified range\n", *maxDepth);
        exit(1);
    }
   //if any trouble is found, print an error to stderr and exit non-zero

    //do I need to do other things here?
    *pageDirectory = malloc(sizeof(char) * (strlen(argv[2]) + 1)); // Allocate space for pageDirectory
    strcpy(*pageDirectory, argv[2]);
    //is this the proper way of mallocing space for pageDirectory
    if(*pageDirectory == NULL){
        free(*pageDirectory);
        fprintf(stderr, "Memory for page directory was not properly allocated!\n");
        exit(1);
    }

      //for pageDirectory, call pagedir_init()
    if(pagedir_init(*pageDirectory) == false) {
        free(*pageDirectory);
        exit(1);
    }

    //normalizing URL 
    *seedURL = normalizeURL(argv[1]);
    if(!isInternalURL(*seedURL)){
        free(*seedURL);
        free(*pageDirectory);
        fprintf(stderr, "Usage: URL is not internal\n");
        exit(1);
    }   
}

/**************** crawl() ****************/
/* see crawl.h for description */
static void
crawl(char* seedURL, char* pageDirectory, const int maxDepth)
{
    hashtable_t* pagesSeen = NULL;   //stores all pages seen
    int numSlots = 200;              //number of slots for hashtable
    bag_t* pagesToCrawl = NULL;     //stores all urls found, but that need to be searched
    int currDepth = 0;              //keeps track of the depth of the current webpagae 
    webpage_t* seedPage = NULL;     //webpage for the seedPage
    webpage_t* currPage = NULL;     //webpage for the current page
    char* useless = "a";      //for the item in hashtable

    // initialize hashtable and bag
    pagesSeen = hashtable_new(numSlots);
    pagesToCrawl = bag_new();

    if (pagesSeen == NULL || pagesToCrawl == NULL) {
        fprintf(stderr, "Error creating pagesSeen or pagesToCrawl!\n");
        exit(1);
    }

    // create new page for seedURL
    seedPage = webpage_new(seedURL, currDepth, NULL);
    if (seedPage == NULL) {
        fprintf(stderr, "Error creating seed page!\n");
        exit(1);
    }
    //inserting into data structures 
    hashtable_insert(pagesSeen, seedURL, useless);
    bag_insert(pagesToCrawl, seedPage);

    int docID = 1;

    //while there a page to be explored in the ball
    while ((currPage = bag_extract(pagesToCrawl)) != NULL) {
        if (webpage_fetch(currPage)) {
            // save webpage to pageDirectory
            pagedir_save(currPage, pageDirectory, docID);
            currDepth = webpage_getDepth(currPage);
            if (currDepth < maxDepth) {
                pageScan(currPage, pagesToCrawl, pagesSeen);
            }
            docID++;
        }
        //delete the webpage
        webpage_delete(currPage);
    }

    // delete hashtable and bag
    hashtable_delete(pagesSeen, itemdelete);
    bag_delete(pagesToCrawl, NULL);
}

/**************** pageScan() ****************/
/* see pageScan.h for description */
static void 
pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){
    int pos = 0;   
    char* url;
    webpage_t* newPage = NULL;
    int depth;    
    char* useless = "a";   //for the hashtable

    //while there is another url 
    while ((url = webpage_getNextURL(page, &pos)) != NULL) {
        if (isInternalURL(url)) {
            if (hashtable_insert(pagesSeen, url, useless) == false) {
                free(url);  
            } else {
                //getting information about the url 
                depth = webpage_getDepth(page);
                newPage = webpage_new(url, depth + 1, NULL);
                if (newPage != NULL) {
                    bag_insert(pagesToCrawl, newPage);
                } else {
                    free(url);
                }
            }
        } else {
              free(url);
        }
        
    }    
}

/**************** itemdelete() ****************/
/* see itemdelete.h for description */
static void itemdelete(void *item) {
}


