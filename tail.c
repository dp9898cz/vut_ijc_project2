#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_COUNT 10
#define MAX_SIZE 1024

#define MIN(a,b) ((a < b) ? a : b)

FILE *openFile(const char* file);
int checkNumber(const char* numArg, const char* number);
void tail(int n, FILE *f);

int main(int argc, char const *argv[]) {

    FILE *f = stdin;
    int lines = DEFAULT_COUNT;

    if (argc == 2) {
        //musi byt jako jediny argument zadan soubor
        f = openFile(argv[1]);
    }
    else if (argc == 3) {
        //bude zadan jen cislo radku (bez souboru)
        lines = checkNumber(argv[1], argv[2]);
    }
    else if (argc == 4) {
        //bude zadano i cislo radku i soubor
        lines = checkNumber(argv[1], argv[2]);
        f = openFile(argv[3]);
    }
    else if (argc != 1) {
        fprintf(stderr, "Zadan spatny pocet argumentu programu. Ocekavaji se 2-4 argumenty.\n");
        return EXIT_FAILURE;
    }

    tail(lines, f);

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

int checkNumber(const char* numArg, const char* number) {
    //overit -n argument
    if (strcmp(numArg, "-n") != 0) {
        fprintf(stderr, "Ocekava se argument \"-n\" pro definovani poctu radku.\n");
        exit(EXIT_FAILURE);
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
    while (fgets(arr[size % n], MAX_SIZE, f) != NULL) {
        size++;
    }

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