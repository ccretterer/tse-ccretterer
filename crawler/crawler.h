/*
*
* crawler.h - header file for CS50 crawler module
* The crawler module provides functions to crawl the web starting from a seed URL,
* and finds webpages up to a specified maximum depth, and saving the fetched webpages
* to a specified page directory. This module includes functions to parse command-line
* arguments, initialize the crawler, and perform the actual crawling process.
* 
* Carly Retterer, April 2023
*/


#ifndef __CRAWLER_H
#define __CRAWLER_H

#include <stdbool.h>
#include "webpage.h"
#include "bag.h"
#include "hashtable.h"

/**************** main ****************/
/* Call crawl and parseArgs. 
 *
 * We return:
 *   Nothing
 * We guarantee:
 *   Exit if everything works well. 
 * Caller is responsible for:
 *   Passing in valid arguments. 
 */
int main(const int argc, char *argv[]);

/**************** parseArgs ****************/
/* Parses command-line arguments and initializes the seedURL, pageDirectory, and maxDepth variables.
 *
 * We return:
 *   Nothing
 * We guarantee:
 *   We check for invalid arguments and exit code accordingly. 
 * Caller is responsible for:
 *   Passing in valid arguments. 
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth);

/**************** crawl ****************/
/* Initiates the web crawling process, given a seed URL, a page directory, and a maximum depth.
 *
 * We return:
 *   Nothing
 * We guarantee:
 *   The webpages, hashtable, and bag are freed. 
 * Caller is responsible for:
 *   Providing valid seedURL and pageDirectory strings
 *   Ensuring the pageDirectory exists and is writable
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth);

/**************** pageScan ****************/
/* Scans the given webpage, extracts internal URLs, and updates the pagesToCrawl bag and
 * the pagesSeen hashtable accordingly.
 *
 * We return:
 *   Nothing
 * We gaurantee:
 *   URL's are freed within the scan.
 */
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);

/**************** itemdelete ****************/
/* Itemdelete function to be passed into hashtable_delete. 
 *
 * We return:
 *   nothing
 * We guarantee
 *   The body of itemdelete is empty since 
 *   items are not allocated memory. 
 */
static void itemdelete(void *item);

#endif // __CRAWLER_H
