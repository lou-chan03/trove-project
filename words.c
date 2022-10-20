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

bool notInArray(char *word, char *wordsArr[], int numWords) {
        for(int i = 0; i < numWords ; i ++){
                if(strlen(wordsArr[i]) == strlen(word)){
                        if(strcmp(wordsArr[i], word) == 0){
                                return false;
                        }
                }
        }
        return true;
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

// return the list of unique words for each file
void words(char *fileContents, char *fileName){
        // INITIALIZE AND DECLARE SIZE OF FILE CONTENT STRING
        int i = 0;
        char character = fileContents[i];
        char *currentWord;

        // INITIALIZES currentWord TO BE A SINGLE CHARACTER STRING
        currentWord = (char *) malloc(sizeof(char));

        char *uniqueWords[strlen(fileContents)/(minLength-1)];
        int numUniqueWords = 0;

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
                        if(strlen(currentWord) >= minLength && notInArray(currentWord, uniqueWords, numUniqueWords)) {
                                int wordLength = strlen(currentWord);
                                uniqueWords[numUniqueWords] = (char*) malloc(sizeof(char) * (wordLength + 1));
                                strcpy(uniqueWords[numUniqueWords], currentWord);
                                numUniqueWords++;
                        }
                        memset(currentWord, 0, strlen(currentWord));
                }
                // MOVES TO NEXT CHAR
                i++;
                character = fileContents[i];
        }
        // HASH EACH WORD AND ADD TO THE HASHTABLE
        for(int j = 0; j < numUniqueWords; j ++){
                hashtable_add(hashtable, uniqueWords[j], fileName);
        }
}
