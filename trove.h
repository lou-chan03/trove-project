// header files required by all files
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

// GLOBAL FUNCTIONS (PARAM TYPE ONLY, NO NAME)
extern void findfiles(char*);
extern void build(char*);
extern void indexing(char*);
extern void words(char*);

// GLOBAL VARIABLES (NO DATA SIZE)
// Store abs pathname of the trovefile (default /tmp/trove)
extern char *trovePath;
// Min word length from -l flag
extern int minLength;

typedef struct _troveInfo{
        char            *pathName;
        struct _troveInfo       *next;
} TINFO;

// THESE ARE THE DATATYPES AND FUNCTION DECLARATIONS FOR THE LIST
// TO BE USED FOR THE HASHTABLE

// LIST DATA TYPE
typedef struct _list{
        char            *word;
        struct _list    *nextWord;
} LIST;

// FUNCTIONS TO BE USED IN LIST FUNCTIONS
extern  LIST *list_new(void);
extern  LIST *list_add(LIST*, char*);
extern  bool list_find(LIST, char*);
extern  void list_print(LIST*);
