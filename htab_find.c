#include "htab.h"
#include "htab_struct.h"

htab_iterator_t htab_find(htab_t * t, htab_key_t key) {
    unsigned int hash = htab_hash_fun(key);
    size_t index = hash % t->arr_size;
    struct htab_item *item = t->arr[index];

    //zkontroluji prvni polozku v seznamu
    if (strlen(key) == strlen(item->key)) {
        if (strncmp(key, item->key, strlen(key)) == 0) {
            //polozky jsou shodne -> vracim iterator
            htab_iterator_t iterator;
            iterator.ptr = item;
            iterator.t = t;
            iterator.idx = index;
            return iterator;
        }
    }

    while (item->next != NULL) {
        //existuje dalsi polozka
        //musim zjistit, zda je aktualni polozka uplne stejna
        if (strlen(key) == strlen(item->key)) {
            if (strncmp(key, item->key, strlen(key)) == 0) {
                //polozky jsou shodne -> vracim iterator
                htab_iterator_t iterator;
                iterator.ptr = item;
                iterator.t = t;
                iterator.idx = index;
                return iterator;
            }
        }

        //dalsi polozka
        item = item->next;
    }

    //zkontroluji posledni polozku listu
    if (strlen(key) == strlen(item->key)) {
        if (strncmp(key, item->key, strlen(key)) == 0) {
            //polozky jsou shodne -> vracim iterator
            htab_iterator_t iterator;
            iterator.ptr = item;
            iterator.t = t;
            iterator.idx = index;
            return iterator;
        }
    }

    //polozka nebyla nalezena
    return htab_end(t);
}