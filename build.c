/**
 * THIS IS FOR THE BUILDING OF A NEW FILE
 * AND CONTAINS HASHTABLE FUNCTION CODE
 */

#include "trove.h"

// THIS IS TO HASH THE ABSOLUTE PATHNAME
u_int32_t hash_string(char *string){
        u_int32_t hash = 0;

        while(*string != '\0'){
                hash = hash*33 + *string;
                ++string;
        }
        return hash;
}

HASHTABLE *hashtable_new(void){
        HASHTABLE *new = calloc(ARRAYSIZE, sizeof(LIST *));
        CHECK_ALLOC(new);
        return new;
}

void hashtable_add(HASHTABLE *hashtable, char *string, char* pathName){
        u_int32_t h = hash_string(string) % ARRAYSIZE;
        hashtable[h] = list_add(hashtable[h], pathName);
}

bool hashtable_find(HASHTABLE *hashtable, char *string, char *pathName){
        u_int32_t h = hash_string(string) % ARRAYSIZE;
        return list_find(hashtable[h], pathName);
}

void hashtable_print(void){
        for(int i = 0; i < ARRAYSIZE ; i++){
                printf("\n-----[%i]-----\n", i);
                list_print(hashtable[i]);
        }
}

void build(char *pathName) {
        struct stat path;
        stat(pathName, &path);

        hashtable = hashtable_new();

        // checks if pathName corresonds to a file or a directory
        if (S_ISDIR(path.st_mode)) {
                findfiles(pathName);
        }
        else if (S_ISREG(path.st_mode)){
                // stop recursion
                printf("FILE FOUND: %s\n", pathName);
                indexing(pathName);
        }
        else{
                printf("Could not locate directory or file named <%s>.\n", pathName);
        }
        hashtable_print();
}
