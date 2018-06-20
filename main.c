#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "types.h"

#define MIN_NUMBER_OF_ARGUMENTS 7
#define FORMAT_FLAG "-fmt"
#define FORMAT_FLAG_POS 1
#define FORMAT_POSITION 2
#define SORT_FLAG "-sort"
#define SORT_FLAG_POSITION 3
#define SORT_POSITION 4
#define FO_FLAG "-out"
#define FO_FLAG_POSITION 5


status_t validate_arguments(int, char **, size_t *, size_t *);

int main(int argc, char * argv[])
{
}

status_t validate_arguments(int argc, char ** argv, size_t * i, size_t * j)
{
    if(argc <= MIN_NUMBER_OF_ARGUMENTS)
        return ERROR_INVALID_ARGUMENTS;
    if(strcmp(argv[FORMAT_FLAG_POS],FORMAT_FLAG))
        return ERROR_INVALID_ARGUMENTS;
    else{
        for (*i = 0; *i < MAX_FORMATS; (*i)++) {
            if (!strcmp(argv[FORMAT_POSITION], formats[*i]))
                break;
        }
        if (*i >= MAX_FORMATS)
            return ERROR_INVALID_ARGUMENTS;
    }
    if(strcmp(argv[SORT_FLAG_POSITION],SORT_FLAG))
        return ERROR_INVALID_ARGUMENTS;
    else{
        for(*j = 0; *j < MAX_SORTING_CRITERION; (*j)++)
        {
            if(!strcmp(argv[SORT_POSITION], sort_criterion[*j]))
                break;
        }
        if(*j >= MAX_SORTING_CRITERION)
            return ERROR_INVALID_ARGUMENTS;
    }
    if(strcmp(argv[FO_FLAG_POSITION],FO_FLAG))
        return ERROR_INVALID_ARGUMENTS;
    return OK;
}
