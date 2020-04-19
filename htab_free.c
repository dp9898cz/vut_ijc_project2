/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

#include "htab.h"
#include "htab_struct.h"

void htab_free(htab_t * t) {
    //vymazu obsah tabulky a tabulku samotnou
    htab_clear(t);
    free(t);
}