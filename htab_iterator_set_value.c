/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

#include "htab.h"
#include "htab_struct.h"

htab_value_t htab_iterator_set_value(htab_iterator_t it, htab_value_t val) {
    it.ptr->data = val;
    return val;
}