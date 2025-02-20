/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

#include "htab.h"
#include "htab_struct.h"

htab_iterator_t htab_begin(const htab_t * t) {
    //od zacatku tabulky budu kontrolovat, zda v ni neco je
    for (size_t i = 0; i < t->arr_size; i++) {
        if (t->arr[i] != NULL) {
            //polozka neco obsahuje -> vytvorim iterator na prvni polozku
            htab_iterator_t iterator;
            iterator.ptr = t->arr[i];
            iterator.t = t;
            iterator.idx = i;
            return iterator;
        }
    }
    //tabulka je prazdna -> neexistujici iterator
    return htab_end(t);
}