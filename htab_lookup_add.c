/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

#include "htab.h"
#include "htab_struct.h"

htab_iterator_t htab_lookup_add(htab_t *t, htab_key_t key) {
    unsigned int hash = htab_hash_fun(key);
    size_t index = hash % t->arr_size;
    struct htab_item *item = t->arr[index];

    if (item == NULL) {
        //jeste zde zadna polozka neni -> vytvorime rovnou novou
        struct htab_item *newItem = malloc(sizeof(struct htab_item));
        if(newItem == NULL){
            return htab_end(t);
        }
        //alokace pameti pro jeji klic (string) a presun klice pomoci memcpy
        newItem->key = malloc((strlen(key) + 1) * sizeof(char));
        if(newItem->key == NULL){
            return htab_end(t);
        }
        memcpy(newItem->key, key, (strlen(key) + 1));
        newItem->next = NULL;
        newItem->data = 0;

        //pridani nove polozky do tabulky
        t->size++;
        t->arr[index] = newItem;

        //vytvoreni iteratoru 
        htab_iterator_t iterator;
        iterator.ptr = newItem;
        iterator.t = t;
        iterator.idx = index;
        return iterator;
    }

    //kdyz item neni null (neco uz zde je vlozene)
    while (item->next != NULL) {
        //existuje dalsi polozka
        //musim zjistit, zda aktualni polozka neni uplne stejna jako ta, kterou vkladam
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

    //jsem na posledni polozce listu
    //posledni kontrola shodne polozky
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

    //vytvorim novou polozku
    struct htab_item *newItem = malloc(sizeof(struct htab_item));
    if(newItem == NULL){
        return htab_end(t);
    }
    //alokace pameti pro jeji klic (string) a presun klice pomoci memcpy
    newItem->key = malloc((strlen(key) + 1) * sizeof(char));
    if(newItem->key == NULL){
        return htab_end(t);
    }
    memcpy(newItem->key, key, (strlen(key) + 1));
    newItem->next = NULL;
    newItem->data = 0;

    //navazu polozku na konec listu a aktualizuji tabulku
    item->next = newItem;
    t->size++;

    //vratim iterator na novou polozku
    htab_iterator_t iterator;
    iterator.ptr = newItem;
    iterator.t = t;
    iterator.idx = index;
    return iterator;
}