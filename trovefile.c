/**
 * This is to compress / unzip
 * trovefile and save to disk
 * write trove file data to gzip using pipes
 */

#include "trove.h"

void trovefile(void){
        int thepipe[2];

        if(pipe (thepipe) != 0){
                perror("Error creating pipe!\n");
                exit(EXIT_FAILURE);
        }

        switch(fork()){
                case -1 :
                        printf("fork() failed\n");
                        exit(EXIT_FAILURE);
                // THIS IS THE CHILD PROGRESS THAT WRITES TO THE FILE AND COMPRESSES
                case 0 :
                        // reads from parent process
                        // writes to stdout
                        close(thepipe[1]);
                        dup2(thepipe[0], 0);
                        char buf;
                        int fd1 = open(trovePath, O_WRONLY | O_CREAT);
                        while(read(0, &buf, thepipe[1]) > 0){
                                write(fd1, &buf, thepipe[1]);
                        }
                        close(thepipe[0]);
                        execl("/usr/bin", "gzip", fd1, (char*) NULL);
                        break;
                // THIS IS THE PARENT PROCESS THAT'LL READ THE HASHTABLE
                default:
                        // writes to the pipe for the child to read
                        close(thepipe[0]);

                        for(int i = 0 ; i < ARRAYSIZE ; i ++){
                                if(hashtable[i] != NULL){
                                        while(hashtable[i] != NULL){
                                                printf("%s\n", hashtable[i]->word);
                                                if(hashtable[i]->nextWord != NULL){
                                                        printf("->");
                                                }
                                                hashtable[i] = hashtable[i]->nextWord;
                                        }
                                        printf("\n");
                                }
                                //      troveLine = realloc(troveLine, sizeof(troveLine) + 1);
                                //      strcat(troveLine, "\n");
                                //write(thepipe[1], troveLine, sizeof(troveLine));
                        }

                        close(thepipe[1]);
                        break;
        }
}
