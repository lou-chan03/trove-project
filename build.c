#include "trove.h"

#define HASHTABLE_SIZE 997

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
        HASHTABLE *new = calloc(HASHTABLE_SIZE, sizeof(LIST *));
        CHECK_ALLOC(new);
        return new;
}

void hashtable_add(HASHTABLE *hashtable, char *string){
        u_int32_t h = hash_string(string) % HASHTABLE_SIZE;
        hashtable[h] = list_add(hashtable[h], string);
}

bool hashtable_find(HASHTABLE *hashtable, char *string){
        u_int32_t h = hash_string(string) % HASHTABLE_SIZE;
        return list_find(hashtable[h], string);
}

void build(char *pathName) {
        struct stat path;
        stat(pathName, &path);

        // initialize array of structs
        LIST * uniqueWords = list_new();

        // checks if pathName corresonds to a file or a directory
        if (S_ISDIR(path.st_mode)) {
                findfiles(pathName);
        }
        else if (S_ISREG(path.st_mode)){
                // stop recursion
                printf("FILE FOUND: %s\n", pathName);
                indexing(pathName);
                list_print(uniqueWords);
        }
        else{
                printf("Could not locate directory or file named <%s>.\n", pathName);
        }
}
