/**
 * This is the file used to index the contents
 * of the files
 */
#include "trove.h"
#include <fcntl.h>

// THIS IS TO READ THE CONTENTS OF THE FILE
// AND WRITE TO THE FILE TO BE BUILT/MODIFIED
void indexing(char filefound[]){
        // FIRST OPEN THE TWO FILES
        FILE    *fp_in = fopen(filefound, "r");
        //FILE  *fp_out = fopen(trovefile, "r+");

        // ENSURE BOTH OPENINGS ARE SUCCESSFUL
        if(fp_in != NULL){ //&& fp_out != NULL){
                // DETERMINING THE SIZE OF THE FILE
                struct stat st;
                stat(filefound, &st);
                int size = st.st_size;

                // ALLOCATING BUFFER SIZE
                char buffer[size];
                size_t got;

                // REXTRACTING LARGE STRING THEN INDIVIDUAL WORDS
                while( (got = fread(buffer, 1, sizeof buffer, fp_in)) > 0) {
                        printf("%s\n", buffer);
                }
                words(buffer);
        }

        // ENSURE THAT WE ONLY CLOSE FILES THAT ARE OPEN
        if(fp_in != NULL){
                fclose(fp_in);
        }

        
//      if(fp_out != NULL){
//              fclose(fp_out);
//      }
}
