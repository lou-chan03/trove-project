/**
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

// ITERATES THROUGH THE GIVEN ARRAY AND VERIFIES THE GIVEN WORD
// IS NOT CONTAINED WITHIN THE ARRAY

bool notInArray(char *word, char *wordsArr[], int numWords) {
        for(int i = 0; i < numWords; i ++){
                if(strlen(wordsArr[i]) == strlen(word)){
                        if(strcmp(wordsArr[i], word) == 0){
                                return false;
                        }
                }
        }
        return true;
}

void list_print(LIST *list){
        if(list != NULL){
                while(list != NULL){
                        printf("%s", list->word);
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

        // CONSIDER CASE THAT ALL THE WORDS IN THE FILE ARE UNIQUE AND MIN LENGTH
        // FOR THIS CASE NUM OF UNIQUE WORDS = NUMBER OF CHAR / (MINLENGTH-1)
        // -1 ACCOUNTS FOR THE NON ALPHANUMERIC CHAR

        // MAKING NEW LIST
        char *uniqueWords[strlen(fileContents) / (minLength - 1)];
        int numUniqueWords = 0;

        // INITIALIZES currentWord TO BE A SINGLE CHARACTER STRING
        currentWord = (char *) malloc(sizeof(char));

        // WHILE NOT NULL BYTE
        while(character != '\0'){
                // IF ALNUM CHAR BUILD UP THE WORD
                if(isalnum(character)){
                        // INCREASES THE SIZE OF THE CURRENT WORD STRIGN BY ONE CHAR
                        currentWord = (char *) realloc(currentWord, sizeof(currentWord) + sizeof(char));
                        strncat(currentWord, &character, 1);
                }
                else{
                        // IF LENGTH OF WORD IS GREATER THAN MINLENGTH AND NOT IN THE LIST
                        if(strlen(currentWord) >= minLength && notInArray(currentWord, uniqueWords,numUniqueWords)) {
                                int wordLength = strlen(currentWord);
                                // ALLOCATE MEMORY IN UNIQUEWORDS ARRAY FOR THE CURRENT WORD
                                uniqueWords[numUniqueWords] = (char *) malloc(sizeof(char) * (wordLength + 1));
                                // COPIES CURRENTWORD INTO UNIQUE WORDS ARRAY
                                strcpy(uniqueWords[numUniqueWords], currentWord);
                                numUniqueWords++;
                        }

                        // RESETS CURRENT WORD STRING
                        memset(currentWord, 0, strlen(currentWord));
                }
                // MOVES TO NEXT CHAR
                i++;
                character = fileContents[i];
        }

        // CREATING A LIST
        LIST *wordList = list_new();

        // ADD CONTENTS OF ARRAY TO THE LIST
        for(int w = 0; w < numUniqueWords; w++){
                wordList = list_add(wordList, uniqueWords[w]);
        }

        // PRINT THE LIST
        list_print(wordList);
}
