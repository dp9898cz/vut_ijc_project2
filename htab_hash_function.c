/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

#include "htab.h"
#include "stdint.h"

size_t htab_hash_fun(const char *str) {
    uint32_t h = 0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p = (const unsigned char*) str; *p != '\0'; p++) {
        h = 65599 * h + *p;
    }
    return h;
}