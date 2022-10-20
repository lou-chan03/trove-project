/**:
 * This is to validate
 * the length of the
 * words in the file
 */
#include "trove.h"
#include <ctype.h>
#include <stdbool.h>

// JUST A NULL POINTER FOR THE LIST
LIST *list_new(void){
        return NULL;
}

// DETERMINE IF A REQUIRED ITEM IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *wanted) {
        while(list != NULL){
                if(strcmp(list->word, wanted) == 0){
                        return true;
                }
                list    = list->nextWord;
        }
        return false;
}

// ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
LIST *list_new_item(char *newWord){
        LIST *new       = calloc(1, sizeof(LIST));
        CHECK_ALLOC(new);
        new->word       = strdup(newWord);
        CHECK_ALLOC(new->word);
        new->nextWord   = NULL;
        return new;
}

// ADDS TO EXISTING LIST
LIST *list_add(LIST *list, char *newstring){
        if(list_find(list, newstring)){
                return list;
        }
        else{
                LIST *new = list_new_item(newstring);
                new->nextWord = list;
                return new;
        }
}

// PRINTS OUT EACH ITEM IN THE LIST
void list_print(LIST *list){
        if(list != NULL){
                while(list != NULL){
                        printf("%s\n", list->word);
                        if(list->nextWord != NULL){
                                printf("->");
                        }
                        list = list->nextWord;
                }
                printf("\n");
        }
}

void words(char *fileContents){
        // INITIALIZE AND DECLARE SIZE OF FILE CONTENT STRING
        int i = 0;
        char character = fileContents[i];
        char *currentWord;

        // INITIALIZES currentWord TO BE A SINGLE CHARACTER STRING
        currentWord = (char *) malloc(sizeof(char));

        // WHILE NOT NULL BYTE
        while(character != '\0'){
                // IF ALNUM CHAR, BUILD UP THE WORD
                if(isalnum(character)){
                        // INCREASES THE SIZE OF THE CURRENT WORD STRING BY ONE CHAR
                        currentWord = (char *) realloc(currentWord, sizeof(currentWord) + sizeof(char));
                        strncat(currentWord, &character, 1);
                }
                else{
                        // IF LENGTH OF WORD IS GREATER THAN MINLENGTH
                        if(strlen(currentWord) >= minLength) {
                                // ALLOCATE MEMORY IN UNIQUEWORDS LIST FOR THE CURRENT WORD AND ADD TO IT
                                uniqueWords = list_add(uniqueWords, currentWord);
                        }
                        memset(currentWord, 0, strlen(currentWord));
                }
                // MOVES TO NEXT CHAR
                i++;
                character = fileContents[i];
        }
        list_print(uniqueWords);
}
