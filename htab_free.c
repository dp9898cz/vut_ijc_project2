
#include "htab.h"
#include "htab_struct.h"

void htab_free(htab_t * t) {
    //vymazu obsah tabulky a tabulku samotnou
    htab_clear(t);
    free(t);
}