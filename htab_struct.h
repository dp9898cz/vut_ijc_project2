/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

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