#ifndef IJC_PROJ2_STRUCT_H
#define IJC_PROJ2_STRUCT_H

#include "htab.h"

struct htab_item{
    char *key;
    int data;
    struct htab_item *next;
};

struct htab{
    size_t size;
    size_t arr_size;
    struct htab_item *arr[];
};


#endif