//  CITS2002 Project 2 2022
//  Student1:   23362432   CHAN   LOUISE   CONTRIBUTION
//  Student2:   STUDENT-NUMBER2   FAMILY-NAME   FIRST-NAME   CONTRIBUTION

#include "trove.h"

#define OPTLIST "bf:l:ru"
#define USAGE_FMT       "Usage:\t%s [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist\nor\t./trove [-f trovefile] word\n"

// USAGE FUNCTION TO PRINT SYNOPSIS OF PROG
void usage(char *progName){
        fprintf(stderr, USAGE_FMT, progName);
        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
        // INITIALIZES FLAGS FOR LATER USE
        int opt;
        int bFlag = 0;
        int fFlag = 0;
        int lFlag = 0;
        int rFlag = 0;
        int uFlag = 0;
        int limitFlag = 0;
        char *progName = argv[0];

        while((opt = getopt(argc, argv, OPTLIST)) != -1){
                switch(opt){
                        case 'b':
                                if (limitFlag) {
                                        usage(progName);
                                }
                                bFlag++;
                                limitFlag++;
                                break;
                        case 'f':
                                if (fFlag){
                                        usage(progName);
                                }
                                fFlag++;
                                trovePath = optarg;
                                break;
                        case 'l':
                                if (lFlag){
                                        usage(progName);
                                }
                                lFlag++;
                                minLength = atoi(optarg);
                                break;
                        case 'r':
                                if(limitFlag){
                                        usage(progName);
                                }
                                rFlag++;
                                limitFlag++;
                                break;
                        case 'u':
                                if (limitFlag){
                                        usage(progName);
                                }
                                uFlag++;
                                limitFlag++;
                                break;
                        case '?':
                                fprintf(stderr, "%s: unknown option [%c]\n", progName, optopt);
                                exit(EXIT_FAILURE);
                        case ':':
                                fprintf(stderr, "%s: unknown option [%c]\n", progName, optopt);
                                exit(EXIT_FAILURE);
                }
        }

        if(optind < argc) {
                while (optind < argc) {
                        if(bFlag) {
                                char *pathName = argv[optind];
                                build(pathName);
                        }
                        else if(rFlag){
                                ;
                        }
                        else if(uFlag){
                                ;
                        }
                        else{
                                //non option arg is a word
                                //search trovefile
                        }
                        optind++;
                }
        }

        exit(EXIT_SUCCESS);
}
