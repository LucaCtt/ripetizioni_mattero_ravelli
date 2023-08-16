/*
Parte A (5 punti)
    Realizzare una funzione di prototipo
        tPersona *lettura_persone(int *n);

    che legga n righe, ciascuna costituita da un nome, un cognome (ciascuno rappresentato da una
    sequenza di caratteri priva di spazi) e una data di nascita nel formato DD/MM/YYYY, scartando le
    righe per le quali la data di nascita è malformata (ovvero il giorno o il mese non sono compresi negli
    intervalli corretti, o la data è nel futuro; si assuma inoltre che gli anni di nascita siano positivi). Al fine
    di tali controlli, non è necessario verificare che il 29 Febbraio cada effettivamente in un anno
    bisestile. In caso di errore, la funzione lettura_persone deve chiamare la funzione
    stampa_errore data, passando ad essa l'opportuno codice d'errore (vedere il tipo enumerativo
    tControlloData).
    La funzione deve restituire una struttura dati dinamicamente allocata contenente i dati letti.
    Il parametro n contiene all'atto della chiamata il numero di righe da leggere, ma all'atto della
    chiusura della funzione deve contenere il numero di righe valide lette.
• Parte B (5 punti)
    Realizzare inoltre una funzione di prototipo
        int distanza(tPersona *data, int n);

    che riceva una struttura di tipo tPersona contenente i dati di n persone, e calcoli la distanza
    (espressa in anni) fra l'anno di nascita della persona più vecchia e l'anno di nascita della persona più
    giovane.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define NMAX 128

// Risultati del controllo data
typedef enum
{
    OK,
    GIORNOERRATO,
    MESEERRATO,
    ANNOERRATO,
    DATAFUTURA,
} tControlloData;

typedef enum
{
    NONE,
    GEN,
    FEB,
    MAR,
    APR,
    MAG,
    GIU,
    LUG,
    AGO,
    SET,
    OTT,
    NOV,
    DIC
} tMese;

typedef struct _data
{
    int giorno;
    tMese mese;
    int anno;
} tData;

const tData oggi = {9, 2, 2023};

typedef struct _tPersona
{
    char nome[NMAX];
    char cognome[NMAX];
    tData data_nascita;
} tPersona;

void stampaerrore(tControlloData c)
{
    printf("errore: %d\n", c);
}

tPersona *lettura_persone(int *n);

int distanza(tPersona *data, int n);

int main()
{
    int n;
    tPersona *dati = NULL;
    scanf("%d", &n);

    dati = lettura_persone(&n);

    printf("n: %d\n", n);
    printf("distanza: %d\n", distanza(dati, n));

    return 0;
}

// Controlla la validità di una data
tControlloData controlla_data(tData d)
{
    if (d.giorno < 1 || d.giorno > 31)
        return GIORNOERRATO;

    if (d.mese < GEN || d.mese > DIC)
        return MESEERRATO;

    if (d.anno > oggi.anno ||
        (d.anno == oggi.anno && d.mese > oggi.mese) ||
        (d.anno == oggi.anno && d.mese == oggi.mese && d.giorno > oggi.giorno))
        return DATAFUTURA;

    if (d.anno <= 0)
        return ANNOERRATO;

    switch (d.mese)
    {
    case APR:
    case GIU:
    case SET:
    case NOV:
        if (d.giorno > 30)
            return GIORNOERRATO;
    case FEB:
        if (d.giorno > 29)
            return GIORNOERRATO;
    }
    return OK;
}

// Leggi n persone da stdin
// n è un puntatore perchè il suo valore verrà aggiornato
// con il numero di righe effetivamente letto!
tPersona *lettura_persone(int *n)
{
    // Crea un array di n persone
    tPersona *res = malloc(sizeof(tPersona) * *n);

    // Variabile temporanea per la lettura
    tPersona r;

    // Numero di righe valide lette
    int j = 0;

    for (int i = 0; i < *n; i++)
    {
        tControlloData c;

        // Leggi persona nella variabile temporanea
        scanf("%s %s %d/%u/%d", r.nome, r.cognome, &r.data_nascita.giorno,
              &r.data_nascita.mese, &r.data_nascita.anno);

        c = controlla_data(r.data_nascita);
        if (c == OK)
        {
            // Se la data è valida, copia la persona nell'array risultato
            res[j] = r;
            j++;
        }
        else
        {
            stampaerrore(c);
        }
    }

    // Aggiorna il numero di righe valide lette
    *n = j;
    return res;
}

// Trova l'anno di nascita massimo fra n persone
int massimo(tPersona *persona, int n)
{
    int amax = 0;

    for (int i = 0; i < n; i++)
        if (persona[i].data_nascita.anno > amax)
            amax = persona[i].data_nascita.anno;

    return amax;
}

// Trova l'anno di nascita minimo fra n persone
int minimo(tPersona *persona, int n)
{
    int amin = oggi.anno;

    for (int i = 0; i < n; i++)
        if (persona[i].data_nascita.anno < amin)
            amin = persona[i].data_nascita.anno;

    return amin;
}

// Calcola la distanza fra l'anno di nascita massimo e minimo
int distanza(tPersona *persona, int n)
{
    return massimo(persona, n) - minimo(persona, n);
}