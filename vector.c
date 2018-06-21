#include <stdio.h>
#include <stdlib.h>
#include "vector.h"



status_t ADT_Vector_new (ADT_Vector_t ** p)
{
    size_t i;

    if (p == NULL)
        return ERROR_NULL_POINTER;
    if((*p = (ADT_Vector_t*)malloc(sizeof(ADT_Vector_t)))==NULL)
        return ERROR_OUT_OF_MEMORY;
    /////(*p) -> elements = NULL;  ESTO NO VA SI SE HACEMOS LO DE LA LINEA 17 ////
    (*p) -> size = (*p) -> alloc_size = 0;
    if(((*p)-> elements = (void **)malloc(sizeof(void*)*INIT_CHOP))== NULL)
    {
        free(*p);
        *p = NULL;
        return ERROR_OUT_OF_MEMORY;
    }
    for(i = 0; i < INIT_CHOP; i++)
        (*p) -> elements[i] = NULL;
}

status_t ADT_Vector_delete (ADT_Vector_t ** p)
{
    size_t i;
    status_t st;

    for(i = 0; i < (*p)->size; i++)
    {
        st = (*p)->destructor ((*p)->elements[i]);/*llama al destructor incluído en el ADT_Vector_t. Debe estar setteado*/
        (*p)->elements[i] = NULL;
    }
    free((*p)->elements);
    (*p)->elements = NULL;
    free(*p);
    *p = NULL;
    return OK;
}

status_t ADT_Vector_set_destructor (ADT_Vector_t * p, destructor_t pf)
{
    if (p == NULL)
        return ERROR_NULL_POINTER;
    p->destructor = pf;
    return OK;
}

status_t ADT_Vector_sort(ADT_Vector_t *p) /*con selection sort*/
{
    size_t i;
    size_t j;
    size_t min;

    if (p == NULL)
        return ERROR_NULL_POINTER;
    for(i=0; i < p -> alloc_size; i++)
    {
        min = i;
        for (j = i +1; j < p-> alloc_size; j++)
        {
            if ((*(p->comparator))(p->elements[min], p->elements[j]) > 0) /*si min es mayor a elements[j]*/
                min = j;
        }
        swap(p->elements[i],p->elements[min]);
    }
    return OK;
}

status_t ADT_Vector_set_comparator(ADT_Vector_t *p, comparator_t pf)
{
    if(p == NULL)
        return ERROR_NULL_POINTER;
    p->comparator = pf;
    return OK;
}

/*faltaría ADT_Vector_load*/

