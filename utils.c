#include <stdio.h>
#include "utils.h"

void swap (void *a, void *b)
{
    void * aux;
    aux = a;
    a = b;
    b = aux;
}