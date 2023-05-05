/*
* Word.c Carly Retterer 5 May 2023
* Word module. Normalizes a word by bringing it all to lower cases. 
* 
*/
#include <ctype.h>

/********* normalizeWord() *******/
/* see word.h for description */
char*
normalizeWord(char* currWord){
    for (int i = 0; currWord[i]; i++) {
        currWord[i] = tolower((unsigned char)currWord[i]);
    }
    return currWord;
}