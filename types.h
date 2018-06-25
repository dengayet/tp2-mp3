#ifndef TYPES__H
#define TYPES__h

#define MAX_FORMATS 3
#define MAX_SORTING_CRITERION 3
#define MAX_OUTPUT_FORMAT 2

char * formats[MAX_FORMATS]=
        {
                "csv",
                "xml",
                "html"
        };

char * sort_criterion[MAX_SORTING_CRITERION] =
        {
                "name",
                "artist",
                "genre"
        };

typedef status_t (*destructor_t) (void **);
typedef int (*comparator_t) (const void *, const void *);
typedef status_t (*printer_t) (void *);