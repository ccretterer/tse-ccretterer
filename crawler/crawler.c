/*
* Crawler.c   Carly Retterer   22 April 2023
*  
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

int 
main(const int argc, char* argv[]){
    int maxDepth = 0;
    char* seedURL = NULL;
    char* pageDirectory = NULL;

    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
    crawl(seedURL, pageDirectory, maxDepth);

    free(pageDirectory);


    exit(0); 
    
}

static void
parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth){

    //parse args
    if (argc != 4){
        fprintf(stderr, "Usage: %s seedURL, pageDirectory, maxDepth\n", argv[0]);
        exit(1);
    }
 //creating space for seedURL
    if (*seedURL == NULL){
        fprintf(stderr, "Memory for seed url was not properly allocated!\n");
        exit(1);
    }
    *seedURL = normalizeURL(argv[1]);
    if(!isInternalURL(*seedURL)){
        free(*seedURL);
        fprintf(stderr, "Usage: URL is not internal\n");
        exit(1);
    }   

    
    //copying in order to be used in normalizeURL
    //for seedURL, normalize the URL and validate it is an internal URL 
    // if (!normalizeURL(*seedURL)){
    //     free(*seedURL);
    //     fprintf(stderr, "Usage: URL failed to normalize\n");
    //     exit(1);
    // } 

    
    //do I need to do other things here?
    *pageDirectory = malloc(sizeof(char) * (strlen(argv[2]) + 1)); // Allocate space for pageDirectory
    strcpy(*pageDirectory, argv[2]);
    //is this the proper way of mallocing space for pageDirectory
    if(*pageDirectory == NULL){
        fprintf(stderr, "Memory for page directory was not properly allocated!\n");
        exit(1);
    }
    //for pageDirectory, call pagedir_init()
    pagedir_init(*pageDirectory);

    *maxDepth = strtol(argv[3], NULL, 10);  //converting string to integer
    //for maxDepth, ensure it an integer in a specified range
    if (*maxDepth < 0 || *maxDepth > 10){
        fprintf(stderr, "Usage %d max depth is not within the specified range\n", *maxDepth);
        exit(1);
    }
   //if any trouble is found, print an error to stderr and exit non-zero
}

static void
crawl(char* seedURL, char* pageDirectory, const int maxDepth)
{
    hashtable_t* pagesSeen = NULL;
    int numSlots = 200;
    bag_t* pagesToCrawl = NULL;
    int currDepth = 0;
    webpage_t* seedPage = NULL;
    webpage_t* currPage = NULL;
    //creating an item for hashtable insert
    // char* useless = malloc(2);
    // strcpy(useless, "a");
    char* useless = "a";

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
    hashtable_insert(pagesSeen, seedURL, useless);
    bag_insert(pagesToCrawl, seedPage);

    int docID = 1;
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
        webpage_delete(currPage);
    }

    // delete hashtable and bag
    hashtable_delete(pagesSeen, itemdelete);
    bag_delete(pagesToCrawl, NULL);



//initialize the hashtable and add the seedURL
// initialize the bag and add a webpage representing the seedURL at depth 0
// while bag is not empty
// 	pull a webpage from the bag
// 	fetch the HTML for that webpage
// 	if fetch was successful,
// 		save the webpage to pageDirectory
// 		if the webpage is not at maxDepth,
// 			pageScan that HTML
// 	delete that webpage
// delete the hashtable
// delete the bag

}

static void 
pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){
    int pos = 0;
    char* url;
    webpage_t* newPage = NULL;
    int depth;

    char* useless = "a";

    while ((url = webpage_getNextURL(page, &pos)) != NULL) {
        if (isInternalURL(url)) {
            if (hashtable_insert(pagesSeen, url, useless) == false) {
                free(url);  
            } else {
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

// static void 
// pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){
//      int pos = 0;
//      char* url;
//      webpage_t* newPage = NULL;
//      int depth;

//      char* useless = "a";

//      while ((url = webpage_getNextURL(page, &pos)) != NULL) {
//         if (normalizeURL(url)) {
//              if (hashtable_insert(pagesSeen, url, useless) == true) {
//                  depth = webpage_getDepth(page);
//                  newPage = webpage_new(url, depth + 1, NULL);
//                  if (newPage != NULL) {
//                      bag_insert(pagesToCrawl, newPage);
//                  }
//             }
        
//         }
//         free(url);
//     }    
// }


static void itemdelete(void *item) {
}





//     // while there is another URL in the page
// 	// if that URL is Internal,
// 	// 	insert the webpage into the hashtable
// 	// 	if that succeeded,
// 	// 		create a webpage_t for it
// 	// 		insert the webpage into the bag
// 	// free the URL


// }