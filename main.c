#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "types.h"
#include "vector.h"
#include "mp3.h"

#define MIN_NUMBER_OF_ARGUMENTS 7
#define FORMAT_FLAG "-fmt"
#define FORMAT_FLAG_POS 1
#define FORMAT_POSITION 2
#define SORT_FLAG "-sort"
#define SORT_FLAG_POSITION 3
#define SORT_POSITION 4
#define FO_FLAG "-out"
#define FO_FLAG_POSITION 5
#define FO_POSITION 6

status_t validate_arguments(int, char **, size_t *, size_t *);

int main(int argc, char * argv[])
{
    ADT_Vector_t * vector;
    ADT_Track_t  * track;
    FILE * fi;
    FILE * fo;
    status_t st;
    size_t format;
    size_t sort;
    size_t i;

    if((st = validate_arguments(argc, argv, &format, &sort)) != OK)
    {
        /*imprimir error*/
        return st;
    }
    if((st = ADT_Vector_new(&vector)) != OK)
        return st;
    if((st = ADT_Vector_set_destructor(vector, ADT_Vector_delete)) != OK)
        return st;
    /*todo esto debería ir en una sola función*/ 
    for (i = MIN_NUMBER_OF_ARGUMENTS; i < argc; i++)
    {
        if((fi = fopen(argv[i],"rb")) == NULL)
            return st;
        if ((st = ADT_Track_new_from_binary_file(fi, &track)) != OK)
        {
            fclose(fi);
            /*imprimir error*/
            return st;
        }
        if((st = ADT_Vector_append(&vector, track)) != OK);
        {
            /*imprimir error*/
            ADT_Track_delete(&track);
            ADT_Vector_delete(&vector);
            fclose(fi);
        }
        fclose(fi);
    }
    if ((st = ADT_Vector_sort(vector)) != OK)
    {
        ADT_Vector_delete(&vector);
        /*imprimir error*/
        return st;
    }
    if((fo = fopen(argv[FO_POSITION], "wt")) == NULL)
    {
        ADT_Vector_delete(&vector);
        /*imprimir error*/
        return st;
    }
    /*imprimir a archivo*/
    if(fclose(fo) == EOF)
    {
        //imprimir archivo
        ADT_Vector_delete(&vector);
        return ERROR_CANNOT_WRITE_FILE;
    }
    ADT_Vector_delete(&vector);
    return OK;
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