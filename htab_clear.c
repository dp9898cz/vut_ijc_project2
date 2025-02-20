/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

#include "htab.h"
#include "htab_struct.h"

void htab_clear(htab_t * t) {
    struct htab_item *current_item;
    struct htab_item *toErase;
    //musim projit celou tabulku a najit vsechny seznamy, ktere taky musim vsechny projit
    for(size_t i = 0; i < t->arr_size; i++) {
        current_item = t->arr[i];
        while(current_item != NULL){
            toErase = current_item;
            current_item = current_item->next;
            free(toErase->key);
            free(toErase);
        }
        //seznam je prazdny, nastavim na NULL
        t->arr[i] = NULL;
    }
    //tabulka bude prazdna
    t->size = 0;
}