
#include "htab.h"
#include "htab_struct.h"

htab_t *htab_init(size_t n) {
    htab_t *table = malloc(sizeof(htab_t) + n * sizeof(struct htab_item));
    if (!table) {
        return NULL;
    }
    table->arr_size = n;
    table->size = 0;
    for(int i = 0; i < n; i++) {
        table->arr[i] = NULL;
    }
    return table;
}