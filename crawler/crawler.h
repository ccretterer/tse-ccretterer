#ifndef __CRAWLER_H
#define __CRAWLER_H

#include <stdbool.h>
#include "webpage.h"
#include "bag.h"
#include "hashtable.h"

/* Parse command line arguments and start the crawling process.
 */
int main(const int argc, char *argv[]);

/* Parse command line arguments and set values for seedURL, pageDirectory, and maxDepth.
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth);

/* Perform the crawling process given a seed URL, page directory, and maximum depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth);

/* Scan a webpage for new URLs and process them accordingly.
 */
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);

#endif // __CRAWLER_H
