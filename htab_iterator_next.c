/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

#include "htab.h"
#include "htab_struct.h"

htab_iterator_t htab_iterator_next(htab_iterator_t it) {
    //musim zjist, zda se jedna o posledni element seznamu
    if (it.ptr->next == NULL) {
        //vyhledam zaznam na dalsim indexu tabulky
        for (size_t i = it.idx + 1; i < it.t->arr_size; i++) {
            if (it.t->arr[i] != NULL) {
                //nasel jsem dalsi zaznam
                htab_iterator_t new_iterator;
                new_iterator.ptr = it.t->arr[i];
                new_iterator.t = it.t;
                new_iterator.idx = i;
                return new_iterator;
            }
        }
        //nenasel jsem dalsi zaznam -> vracim prazdny iterator
        return htab_end(it.t);
    }
    else {
        //dasli polozka seznamu neni NULL -> iterator na ni
        htab_iterator_t new_iterator;
        new_iterator.ptr = it.ptr->next;
        new_iterator.t = it.t;
        new_iterator.idx = it.idx;
        return new_iterator;
    }
}