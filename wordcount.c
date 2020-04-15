#include <stdio.h>
#include <stdlib.h>

#include "htab.h"

#define HTAB_SIZE 1024
#define WORD_LEN_LIM 256

int main(void) {
    FILE *f = stdin;

    char* word = malloc(WORD_LEN_LIM * sizeof(char));
    if (!word) {
        fprintf(stderr, "Chyba alokace paměti.\n");
        return EXIT_FAILURE;
    }

    htab_t *table = htab_init(HTAB_SIZE);
    if (!table) {
        fprintf(stderr, "Chyba alokace paměti.\n");
        return EXIT_FAILURE;
    }
}