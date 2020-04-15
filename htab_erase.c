
#include "htab.h"
#include "htab_struct.h"

void htab_erase(htab_t * t, htab_iterator_t it) {
    if (it.ptr == NULL) {
        //nemam co smazat, vratim se
        return;
    }
    struct htab_item *item = t->arr[it.idx]; //ukazatel na prvni polozku ve stejnem seznamu tabulky

    if (item == it.ptr) {
        //odstranuji prvni polozku seznamu
        if (item->next != NULL) {
            //v seznamu jsou jeste dalsi polozky -> musim zmenit polozku na indexu tabulky
            t->arr[it.idx] = item->next;
            free(item->key);
            free(item);
        }
        //jediny prvek v seznamu -> odstranit polozku v tabulce
        t->arr[it.idx] = NULL;
        free(item->key);
        free(item);

        t->size--;
        return;
    }
    
    struct htab_item *toDelete = NULL;
    while (item->next != NULL) {
        //podivam se, zda je dalsi polozka ta, kterou mam odstranit
        if (item->next == it.ptr) {
            toDelete = item->next;
            //odstranuji polozku -> podivam se, zda je posledni
            if (toDelete->next == NULL) {
                //jedna se o posledni polozku -> u polozky pred odstranenou bude null u next
                item->next = NULL;
                free(toDelete->key);
                free(toDelete);
            }
            //polozka neni posledni -> musim prehodit ukazatel na dalsi
            item->next = toDelete->next;
            free(toDelete->key);
            free(toDelete);

            t->size--;
            return;
        }

        //neni to ta spravna, posunu se dale
        item = item->next;
    }
}