/**
 * This is the header file to be used for the CITS2002 Sem 2 Project 2
 */

// THESE ARE THE INCLUDE FILES FOR THE PROGRAM
#define _GNU_SOURCE
#include <getopt.h>
#include <dirent.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// GLOBAL PREPROCESSOR CONSTANTS

// GLOBAL VARIABLES (NO DATA SIZE)
// Store abs pathname of the trovefile (default /tmp/trove)
extern char *trovePath;
// Min word length from -l flag
extern int minLength;

// THESE ARE THE DATATYPES AND FUNCTION DECLARATIONS FOR THE LIST
// TO BE USED FOR THE HASHTABLE

//PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define CHECK_ALLOC(p) if(p == NULL) {perror(__func__); exit(EXIT_FAILURE);}
#define ARRAYSIZE 997 // the potential size of the array of tinfo structs
// LIST DATA TYPE
typedef struct _list{
        char            *word;
        struct _list    *nextWord;
} LIST;

// FUNCTIONS TO BE USED IN LIST FUNCTIONS
extern  LIST *list_new(void);
extern  LIST *list_add(LIST*, char*);
extern  bool list_find(LIST*, char*);
extern  void list_print(LIST*);

// HASHTABLE FUNCTIONS AND DEFINITION
typedef LIST * HASHTABLE;

extern HASHTABLE *hashtable;
extern HASHTABLE *hashtable_new(void);
extern void hashtable_add(HASHTABLE*, char *, char *);
extern bool hastable_find(HASHTABLE *, char*, char*);

// GLOBAL FUNCTIONS
extern void findfiles(char*);
extern void build(char*);
extern void indexing(char*);
extern void words(char*, char*);
extern void filenames(char *);
extern void removeData(char*);
extern void updateData(char*);
