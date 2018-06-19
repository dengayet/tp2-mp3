#ifndef VECTOR__H
#define VECTOR__H

#include <stdio.h>
#include "errors.h"
#include "mp3.h"
#include "types.h"
#include "utils.h"

#define INIT_CHOP 15
#define CHOP_SIZE 7

typedef struct
{
    void ** elements;
    size_t size;
    size_t alloc_size;
    destructor_t destructor;
    comparator_t comparator;
}ADT_Vector_t;

status_t ADT_Vector_new (ADT_Vector_t **);
status_t ADT_Vector_delete (ADT_Vector_t **);
status_t ADT_Vector_set_destructor (ADT_Vector_t *, destructor_t);

#endif