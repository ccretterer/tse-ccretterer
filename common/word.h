/*
* Word.h Carly Retterer
* Header file for word module. 
*/
#ifndef WORD_H
#define WORD_H

#include <ctype.h>

/*
 * Function: normalizeWord
 * -----------------------
 * Takes a pointer to a string, converts all characters in the string to lowercase.
 *
 * currWord: pointer to the string to be normalized.
 *
 * Returns: pointer to the normalized string.
 */
char* normalizeWord(char* currWord);

#endif // WORD_H
