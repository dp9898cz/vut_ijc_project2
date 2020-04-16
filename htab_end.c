
#include "htab.h"
#include "htab_struct.h"

htab_iterator_t htab_end(const htab_t * t){
    //vytvoreni neexistujiciho iteratoru na konec tabulky
    htab_iterator_t iterator;
    iterator.ptr = NULL;
    iterator.t = t;
    iterator.idx = t->arr_size;
    return iterator;
}