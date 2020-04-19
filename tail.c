/*
    Daniel Pátek (xpatek08)
    VUT FIT
    IJC - Projekt 2
    19.4.2020
    překladač: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_COUNT 10
#define MAX_SIZE 1023

#define MIN(a,b) ((a < b) ? a : b)

FILE *openFile(const char* file);
int checkNumber(const char* numArg, const char* number, bool * doSkip);
void tail(int n, FILE *f);
void tailSkip(int n, FILE *f);

int main(int argc, char const *argv[]) {

    FILE *f = stdin;
    int lines = DEFAULT_COUNT;
    bool doSkip = false;

    if (argc == 2) {
        //musi byt jako jediny argument zadan soubor
        f = openFile(argv[1]);
    }
    else if (argc == 3) {
        //bude zadan jen cislo radku (bez souboru)
        lines = checkNumber(argv[1], argv[2], &doSkip);
    }
    else if (argc == 4) {
        //bude zadano i cislo radku i soubor
        lines = checkNumber(argv[1], argv[2], &doSkip);
        f = openFile(argv[3]);
    }
    else if (argc != 1) {
        fprintf(stderr, "Zadan spatny pocet argumentu programu. Ocekavaji se 2-4 argumenty.\n");
        return EXIT_FAILURE;
    }

    (doSkip) ? tailSkip(lines, f) : tail(lines, f);

    fclose(f);
    return EXIT_SUCCESS;
}

FILE *openFile(const char* file) {
    FILE *fr;
    fr = fopen(file, "r");
    if (fr == NULL) {
        fprintf(stderr, "Soubor %s se nepodarilo otevrit.\n", file);
        exit(EXIT_FAILURE);
    }
    return fr;
}

int checkNumber(const char* numArg, const char* number, bool *doSkip) {
    //overit -n argument
    if (strcmp(numArg, "-n") != 0) {
        fprintf(stderr, "Ocekava se argument \"-n\" pro definovani poctu radku.\n");
        exit(EXIT_FAILURE);
    }

    if (number[0] == '+') {
        *doSkip = true;
    }

    //prevest cislo na integer
    char *endptr = NULL;
    int num = strtol(number, &endptr, 10);
    if (endptr[0] != '\0') {
        fprintf(stderr, "Cislo \"%s\" nemohlo byt spravne prevedeno na typ integer.\n", number);
        exit(EXIT_FAILURE);
    }

    //nesmi byt zaporne
    if (num < 0) {
        fprintf(stderr, "Zadany pocet radku nemuze byt zaporny.\n");
        exit(EXIT_FAILURE);
    }

    return num;
}

void tail(int n, FILE *f) {
    //netiskne se nic pri n 0
    if (n == 0) {
        return;
    }

    //kruhove pole o velikosti radku, ktere se maji vypsat
    char *arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(MAX_SIZE * sizeof(char));
    }

    //celkovy pocet radku bude v promenne size, pole naplnime hodnotami
    int size = 0;
    bool warningWasShown = false;
    char *dummy = malloc(MAX_SIZE * sizeof(char));
    while (fgets(arr[size % n], MAX_SIZE, f) != NULL) {
        if (arr[size % n][strlen(arr[size % n])-1] != '\n') {
            if (!warningWasShown) {
                fprintf(stderr, "Doslo ke zkraceni konce radku.\n");
                warningWasShown = true;
            }
            while (fgets(dummy, MAX_SIZE, f) != NULL) {
                if (dummy[strlen(dummy)-1] == '\n') {
                    break;
                }
            }
            arr[size % n][strlen(arr[size % n])-1] = '\n';
        }
        size++;
    }
    free(dummy);

    //zjistime kde zacit s vypisovanim z pole a kolik znaku vypsat
    int startArrIndex = size > n ? (size % n) : 0;
    int count = MIN(n, size);
    
    //vypiseme poslednich count radku z kruhoveho pole
    for(int i = 0; i < count ; i++){
        printf("%s", arr[(i + startArrIndex) % n]);
    }

    //uvolneni pameti
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
}

void tailSkip(int n, FILE *f) {
    //netiskne se nic pri n 0
    if (n == 0) {
        return;
    }

    char *arr = malloc(MAX_SIZE * sizeof(char));
    //skippnout prvnich n radku
    for (int i = 0; i < n; i++) {
        if (fgets(arr, MAX_SIZE, f) != NULL) {

        }
    }

    
    while (fgets(arr, MAX_SIZE, f) != NULL) {
        printf("%s", arr);
    }

    //uvolneni pameti
    free(arr);
}