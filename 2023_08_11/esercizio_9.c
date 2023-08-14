/*
Sia dato un array, di dimensione definibile dall’utente,
di stringhe contenenti tre o più caratteri (escluso il terminatore di stringa).
Realizzare un programma C che aggiunga ad ogni stringa s la prima di quelle seguenti
che abbia esattamente le prime due lettere iniziali in comune con le due finali di s,
evitando di ripetere le due lettere in comune.
Nel caso nessuna delle stringhe seguenti abbia due lettere in comune con s non bisogna modificare s.
Ad esempio, se l’array contiene le stringhe: casa postino sasso osteria salvia notare renna
Dovrà essere trasformato in: casasso postinotare sasso osteria salvia notarenna renna.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LUNG_STRINGA 50
#define MAX_NUM_STRINGHE 100
#define TRUE 1
#define FALSE 0

int aggiungiStringaCorrispondente(char *dest, const char *src);

int main() {
    char strings[MAX_NUM_STRINGHE][MAX_LUNG_STRINGA];
    int n;

    printf("Inserisci il numero di stringhe: ");
    scanf("%d", &n);

    // Leggi le stringhe dall'utente
    for (int i = 0; i < n; i++) {
        printf("Inserisci la stringa %d: ", i + 1);
        scanf("%s", strings[i]);
        printf("%s ", strings[i]);
    }

    // Scorri tutte le stringhe eccetto l'ultima
    for (int i = 0; i < n - 1; i++) {
        // Per ogni stringa, scorri tutte le stringhe successive
        for (int j = i+1; j < n; j++) {
            int match = aggiungiStringaCorrispondente(strings[i], strings[j]);

            // Se c'è stato un match, prosegui con la prossima stringa
            if (match == TRUE) {
                break;
            }
        }
    }

    // Stampa le stringhe modificate
    printf("Array modificato:\n");
    for (int i = 0; i < n; i++) {
        printf("%s ", strings[i]);
    }
    printf("\n");

    return 0;
}

int aggiungiStringaCorrispondente(char *dest, const char *src) {
    int dest_length = strlen(dest);

    // Controlla se le ultime due lettere di dest sono uguali alle prime due di src.
    if (dest[dest_length - 2] == src[0] && dest[dest_length - 1] == src[1]) {
        strcat(dest, src + 2);

        return TRUE;
    } else {
        return FALSE; 
    }
}

