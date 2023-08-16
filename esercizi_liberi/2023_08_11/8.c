/*
Un numero intero positivo di lunghezza qualsiasi viene rappresentato tramite una stringa di
caratteri numerici (cioè caratteri compresi tra ‘0’ e ‘9’),
con la cifra più significativa nella posizione 0 della stringa.
Realizzare un programma C che legga due stringhe che rappresentano due interi
positivi nel modo suddetto e crei una nuova stringa che rappresenti
(nello stesso modo) la somma dei due numeri dati.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sommaCaratteri(char a, char b, char* riporto);

char* sommaStringhe(char* num1, char* num2);

int main() {
    char num1[100], num2[100];

    // Leggi numeri come stringhe
    printf("Inserisci il primo numero: ");
    scanf("%s", num1);

    printf("Inserisci il secondo numero: ");
    scanf("%s", num2);
    
    // Calcola somma
    char* sum = sommaStringhe(num1, num2);
    printf("La somma dei due numeri è: %s\n", sum);
    
    free(sum);
    return 0;
}

// Calcola la somma di due caratteri numerici
// Il riporto permette di tenere conto di eventuali riporti da una posizione precedente.
char sommaCaratteri(char a, char b, char* riporto) {
    // La sottrazione con il carattere '0' converte il carattere numerico in un intero,
    // sfruttando la codifica ASCII dei caratteri.
    // Per esempio, '0' - '0' diventa 0, '1' - '0' diventa 1, ecc.
    // Alla somma dei due caratteri aggiungi il riporto.
    int somma = (a - '0') + (b - '0') + (*riporto - '0');

    // Se la somma è maggiore di 9, allora c'è un riporto.
    // Aggiorna il riporto al carattere corrispondente.
    *riporto = (somma / 10) + '0';

    // Restituisci il carattere corrispondente alla cifra delle unità della somma.
    // Per esempio, se la somma è 12, restituisci '2'. Il numero '1' nelle decine è il riporto.
    return (somma % 10) + '0';
}

// Funzione per calcolare la somma di due stringhe numeriche
char* sommaStringhe(char* num1, char* num2) {
    // Lunghezza stringhe
    // NB: strlen non conta il terminatore di stringa. Se insericiamo "123", strlen restituisce 3.
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // Lunghezza massima tra le due stringhe
    int maxLen = len1 > len2 ? len1 : len2;
    
    // Allocazione memoria per il risultato.
    // La lunghezza massima è maxLen + 2, per il possibile riporto della somma e il terminatore di stringa.
    char* risultato = (char*)malloc((maxLen + 2) * sizeof(char));
    
    // Il riporto iniziale della somma è 0
    char riporto = '0';

    // Indici per scorrere le stringhe
    int i = len1 - 1; // Per scorrere num1
    int j = len2 - 1; // Per scorrere num2
    int k = maxLen; // Per scorrere il risultato

    // Scrivi subito il terminatore di stringa nella posizione finale
    risultato[k + 1] = '\0';
    
    // Somma caratteri finché non hai finito di scorrere entrambe le stringhe.
    // La somma viene scritta nella stringa risultato, partendo dalla fine.
    while (i >= 0 || j >= 0) {
        // Se hai finito di scorrere una delle due stringhe, usa '0' come carattere
        char cifra1 = i >= 0 ? num1[i] : '0';
        char cifra2 = j >= 0 ? num2[j] : '0';
        
        risultato[k] = sommaCaratteri(cifra1, cifra2, &riporto);
        
        i--;
        j--;
        k--;
    }
    
    if (riporto != '0') {
        // Se il riporto finale è diverso da 0, scrivilo nella prima posizione del risultato.
        risultato[0] = riporto;
        return risultato;
    } else {
        // Altrimenti crea una nuova stringa senza il riporto iniziale.
        char* risultatoAccorciato = (char*)malloc((maxLen + 1) * sizeof(char));
        strcpy(risultatoAccorciato, risultato + 1); // Ignora il carry iniziale

        // Libera la memoria occupata dal risultato precedente.
        free(risultato);

        return risultatoAccorciato;
    }
}