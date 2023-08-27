/*
Nello sport dei tuffi individuali, ogni tuffo viene valutato da cinque giudici diversi.
Ogni giudice esprime un punteggio individuale da 0 a 10, con la possibilità di esprimere anche mezzi punti.
Il punteggio 0 corrisponde a un tuffo completamente sbagliato; il punteggio 10 a un tuffo perfetto.
Per eliminare eventuali preferenze soggettive, il punteggio più alto e quello più basso vengono scartati in
automatico.
Ogni punteggio è espresso indipendentemente dal grado di difficoltà del tuffo (un valore numerico che va
da 1.3 a 3.6) e il punteggio finale attribuito all’atleta è calcolato come prodotto della somma dei tre
punteggi rimanenti per il grado di difficoltà del tuffo.

1. Date le seguenti definizioni di costanti e di tipo di dato
#define NUM_GIUDICI 5
#define MAX_STRING 30
typedef struct {
char nome[MAX_STRING+1];
char cognome[MAX_STRING+1];
char sesso;
char nazione[MAX_STRING+1];
float punteggi[NUM_GIUDICI];
float gradoDifficolta;
} atleta_t;
typedef struct {
} gara_t;
atleta_t* array;
int numAtleti;

scrivere in C la funzione
    gara_t acquisisciDaFile(char nomefile[])

che restituisce una variabile di tipo gara_t che memorizzi come valore del suo primo attributo
l’indirizzo iniziale di un array dinamico con tante celle quante sono le righe del file di testo il cui nome è
indicato come argomento del sottoprogramma, e come valore del suo secondo attributo la lunghezza
dell’array dinamico.

Il file di testo è assunto avere il seguente formato:

Tania Cagnotto F ITALIA 10 9.2 8.5 8.2 9.5 3.0
Kent Ferguson M USA 9.8 9.1 8.2 9.5 9.0 2.8
Dmitrij Sautin M RUSSIA 9.8 9.5 8.0 8.5 9.0 2.8
Patrick Hausding M GERMANIA 9.5 9.5 9.5 10 8.0 1.5
Shi Tingmao F CINA 8.5 8.2 8.0 9.0 9.5 2.5
…

dove su ogni rigo sono riportati nome, cognome, sesso (ꞌMꞌ per uomini e ꞌFꞌ per donne), nazione
di un atleta, il punteggio a lui assegnato da ciascuno dei NUM_GIUDICI giudici e il grado di difficoltà del
tuffo eseguito. Ogni cella dell’array dinamico deve contenere le informazioni prese da un rigo diverso del
file.

N.B. Si assuma che non ci siano nomi o cognomi composti da più di una parola. Le informazioni su ogni
rigo sono separate da un carattere ꞌ ꞌ (spazio). Il numero di righi del file non è noto a priori.

2. Scrivere in C la funzione
    void stampa_migliori(gara_t g)

che riporti a schermo il nome di uno dei migliori atleti della competizione (cioè uno di quelli che hanno
ottenuto il punteggio più alto).
*/

#include <stdlib.h>

#define NUM_GIUDICI 5

// Lunghezza max di una stringa, senza contare il carattere terminatore
#define MAX_STRING 30

typedef struct
{
    char nome[MAX_STRING + 1];
    char cognome[MAX_STRING + 1];
    char sesso;
    char nazione[MAX_STRING + 1];
    float punteggi[NUM_GIUDICI];
    float gradoDifficolta;
} atleta_t;

typedef struct
{
    atleta_t *array;
    int numAtleti;
} gara_t;

gara_t acquisisciDaFile(char nomefile[])
{
    // Apri file in lettura
    FILE *fp = fopen(nomefile, "r");
    if (fp == NULL)
    {
        printf("\n Errore nellꞌapertura del file %s. ", nomefile);
        printf("\n Programma terminato!\n");
        exit(-1);
    }

    // Numero di righe valide lette
    int numRighe = 0;

    // Variabile temporanea di lettura
    atleta_t a;

    // feof(fp) restituisce 0 se non si è raggiunta la fine del file
    // In alternativa si puo fare un ciclo do-while che controlla il numero
    // di valori restituiti da fscanf
    while (feof(fp) == 0)
    {
        // Leggi dati atleta
        fscanf(fp, "%s %s %c %s", a.nome, a.cognome, &a.genere, a.nazione);

        // Leggi voti giudici
        for (int i = 0; i < NUM_GIUDICI; i++)
            fscanf(fp, "%f", &a.punteggi[i]);

        // Leggi grado difficoltà
        fscanf(fp, "%f", &a.gradoDifficolta);

        numRighe += 1;
    }

    if (numRighe == 0)
    {
        printf("\n Il file eꞌ vuoto! ");
        printf("\n Programma terminato!\n");
        exit(-1);
    }

    // Ora che abbiamo il numero di righe possiamo leggere i dati
    // e scriverli nella gara

    gara_t g;
    g.array = (atleta_t *)malloc(sizeof(atleta_t) * numRighe);
    if (g.array == NULL)
    {
        printf("\n malloc(...) fallita! ");
        printf("\n Programma terminato!\n");
        exit(-1);
    }

    g.numAtleti = numRighe;

    // Riporta il puntatore all'inizio del file
    rewind(fp);

    // indice delle celle dell’array dinamico
    int k = 0;

    while (feof(fp) == 0)
    {
        fscanf(fp, "%s %s %c %s", a.nome, a.cognome, &a.genere, a.nazione);

        for (int i = 0; i < NUM_GIUDICI; i++)
            fscanf(fp, "%f", &a.punteggi[i]);

        fscanf(fp, "%f", &a.gradoDifficolta);

        g.array[k] = a;
        k += 1;
    }

    fclose(fp);
    return g;
}

void stampa_migliori(gara_t g)
{
    // Controlla che gara sia valida
    if (g.array == NULL || g.numAtleti <= 0)
        return;

    float maxPunteggio = 0;
    int maxPosizione;

    // Itera tutti gli atleti della gara,
    for (int i = 0; i < g.numAtleti; i++)
    {
        // Somma di tutti i punteggi dei giudici per atleta i
        // Contiene già il punteggio del primo giudice.
        float punteggio = g.array[i].punteggi[0];

        // Punteggio minimo e massimo dati dai giudici all'atleta i
        float punteggioINF = punteggio;
        float punteggioSUP = punteggio;

        // Itera a partire dal secondo giudice
        for (int j = 1; j < NUM_GIUDICI; j++)
        {
            if (g.array[i].punteggi[j] < punteggioINF)
                punteggioINF = g.array[i].punteggi[j];

            if (g.array[i].punteggi[j] > punteggioSUP)
                punteggioSUP = g.array[i].punteggi[j];

            punteggio += g.array[i].punteggi[j];
        }

        // Scarta punteggio più alto e più basso
        punteggio -= (punteggioINF + punteggioSUP);

        // Moltiplica per il grado di difficoltà dell'atleta i
        punteggio *= g.array[i].gradoDifficolta;

        if (maxPunteggio <= punteggio)
        {
            maxPunteggio = punteggio;
            maxPosizione = i;
        }
    }
    printf("\n Il nome di uno degli atleti con il punteggio ");
    printf("massimo e’: %s", g.array[i].nome);
}