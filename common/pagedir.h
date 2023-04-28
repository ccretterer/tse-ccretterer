/*
*
* pagedir.h - header file for CS50 crawler page directory module
* The page directory module provides functions to initialize a page directory,
* and to save the information of crawled webpages into the specified page directory.
* It supports the creation of a .crawler file within the page directory during initialization,
* and the saving of each crawled webpage's URL, depth, and HTML content to a separate file
* using the document ID as the file name.
* Carly Retterer, April 2023
*/

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdbool.h>
#include "webpage.h"

/**************** pagedir_init ****************/
/* Initializes the page directory by creating a .crawler file in the specified directory
 *
 * We return:
 *   a boolean value: true if the initialization is successful, false otherwise
 * We guarantee:
 *   A .crawler file is created within the specified pageDirectory upon successful initialization
 * Caller is responsible for:
 *   Providing a valid pageDirectory string
 *   Ensuring the pageDirectory exists and is writable
 */
bool pagedir_init(const char *pageDirectory);

/**************** pagedir_save ****************/
/* Saves the given webpage's information to a file within the specified page directory, using the docID as the file name. 
 *
 * We return:
 *   Nothing
 * We guarantee:
 *   The given webpage's information is saved to a file with the name format "{docID}" within the pageDirectory
 * Caller is responsible for:
 *   Providing a valid webpage pointer, pageDirectory string, and docID
 *   Ensuring the pageDirectory exists and is writable
 */
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID);

#endif // __PAGEDIR_H
