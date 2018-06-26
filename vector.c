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
    (*p) -> elements = NULL;
    (*p) -> size = (*p) -> alloc_size = 0;
    if(((*p)-> elements = (void **)malloc(sizeof(void*)*INIT_CHOP))== NULL)
    {
        free(*p);
        *p = NULL;
        return ERROR_OUT_OF_MEMORY;
    }
    (*p) -> alloc_size = INIT_CHOP;
    for(i = 0; i < INIT_CHOP; i++)
        (*p) -> elements[i] = NULL;
}

status_t ADT_Vector_delete (void ** pv)
{
    size_t i;
    status_t st;
    ADT_Vector_t **p=(ADT_Vector_t **)pv; /*casteo a ADT_Vector y pongo void como parámetro para no tener errores de punteros. igual funcionaria, pero lo dijo en clase*/

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
            if ((*(p->comparator))(p->elements[min], p->elements[j]) > 0) /*si elements[min] es mayor a elements[j]*/
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

status_t ADT_Vector_append (ADT_Vector_t ** vector, void * element)
{
    void ** aux;
    size_t i;

    if (vector == NULL || element == NULL)
        return ERROR_NULL_POINTER;
    if((*vector)->alloc_size == (*vector)->size)
        if((aux = (void **)realloc((*vector)->elements, ((*vector)->size + CHOP_SIZE)*sizeof(void*))) == NULL)
        {
            ADT_Vector_delete(vector);
            return ERROR_OUT_OF_MEMORY;
        }
    (*vector)->elements = aux;
    (*vector)->alloc_size += CHOP_SIZE;
    (*vector)->elements[(*vector)->size] = element;
    (*vector)->size ++;
    return OK;
}


status_t (*ADT_Vector_print_to_file[MAX_FORMATS]) (ADT_Vector_t * vector, FILE* file) =
        {
                ADT_Vector_print_to_csv,
                ADT_Vector_print_to_xml,

        };

status_t ADT_Vector_print_to_csv ( ADT_Vector_t * vector, FILE * file)
{
    if(vector == NULL || file == NULL)
        return ERROR_NULL_POINTER;
    fprintf(file, "");
}
