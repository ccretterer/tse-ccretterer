/*
*  pagedir.c    Carly Retterer   29 April 2023
*  This file helps the crawler function save and write out information about the searched webpages from the crawler function.
*  It uses parameters given to do so. See crawler.h for my descrition.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
#include <ctype.h>


bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(const char* directory);
webpage_t* pagedir_load(const char* pageDirectory, int docID);

/**************** pagedir_init() ****************/
/* see pagedir.h for description */
bool
pagedir_init(const char* pageDirectory){

    //allocating space for paath
    char* dirPath = malloc(sizeof(char) * (strlen(pageDirectory) + 10));
    if (dirPath == NULL) {
        fprintf(stderr, "Path for directory did not allocate space correctly.\n");
        return false;
    }
    //copying path
    strcpy(dirPath, pageDirectory);
    strcat(dirPath, "/.crawler");

    //opening file
    FILE *fp = fopen(dirPath, "w");
    printf("%s\n", dirPath);
    if (fp == NULL) {
        fprintf(stderr, "Error opening file in pagedir_init!\n");
        free(dirPath);
        return false;
    }
    //close file and free path
    fclose(fp);
    free(dirPath);
    return true;
}

/**************** pagedir_save() ****************/
/* see pagedir.h for description */
void 
pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){
    //trying to aniticipate size of filename
    size_t maxFilenameLength = 256;
    size_t totalLength = strlen(pageDirectory) + 1 + maxFilenameLength + 1;

    //allocating space for filename
    char* fileName = malloc(totalLength * sizeof(char));
    snprintf(fileName, totalLength, "%s/%d", pageDirectory, docID);  //creating pathname

    //opening file
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file in pagedir_save!\n");
        exit(1);
    }
    //printing information about webpage
    fprintf(fp, "The URL is: %s\n", webpage_getURL(page));
    fprintf(fp, "The depth is: %d\n", webpage_getDepth(page));
    fprintf(fp, "The contents of the webpage are: %s\n", webpage_getHTML(page));

    //close file and free filename
    fclose(fp);
    free(fileName);
}

/**************** pagedir_validate() ****************/
/* see pagedir.h for description */
bool
pagedir_validate(const char* directory){
    //creating pathname for directory
    char* dirPath = malloc(sizeof(char) * (strlen(directory) + 10));
    if(dirPath == NULL){
        fprintf(stderr, "Error creating directory path!\n");
        return false;
    }
    //validating its a crawler directory 
    strcpy(dirPath, directory);
    strcat(dirPath, "/.crawler");

    //trying to open file, if file can open, it is of the crawler directory
    FILE* file = fopen(dirPath, "r");
    if(file == NULL){
        free(dirPath);
        return false;
    }
    //closing file
    fclose(file);
    free(dirPath);
    return true;

}


/**************** pagedir_load() ****************/
/* see pagedir.h for description */
webpage_t* 
pagedir_load(const char* pageDirectory, int docID){

    //creating path for filename using pageDirectory and docID 
    size_t maxFilenameLength = 256;
    size_t totalLength = strlen(pageDirectory) + 1 + maxFilenameLength + 1;

    //allocating space for filename
    char* fileName = malloc(totalLength * sizeof(char));
    snprintf(fileName, totalLength, "%s/%d", pageDirectory, docID);  //creating pathname

    FILE *fp = fopen(fileName, "r");
    if (fp == NULL){
        printf("docID, %d\n", docID); 
        fprintf(stderr, "Error opening file in pagedir_load!\n");
        free(fileName);
        return NULL;
    }

    webpage_t* page;

    char* url = file_readLine(fp);
    if (url == NULL) {
        fprintf(stderr, "Error: unable to read url from file!\n");
        fclose(fp);
        // free(page); //might not need to do this
        return NULL;
    }

    int depth; 
    char* depthLine = file_readLine(fp);

    if (sscanf(depthLine, "The depth is: %d", &depth) != 1) {
        fprintf(stderr, "Error: unable to read depth from file!\n");
        fclose(fp);
        free(depthLine);
        return NULL;
    }

    free(depthLine); //making sure to free pointer

    char* html = file_readFile(fp);
    if (html == NULL){
        fprintf(stderr, "Error: unable to read html from file!\n");
        fclose(fp);
        return NULL;
    }

    page = webpage_new(url, depth, html);

    fclose(fp);
    free(fileName);
    return page;  

}
