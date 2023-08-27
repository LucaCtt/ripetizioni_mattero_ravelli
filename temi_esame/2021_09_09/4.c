#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTRLENNOME (29 + 1)
#define MAXSTRLENEX (99 + 1)
#define MAXEXR 10

typedef struct
{
    char nomeEsercizio[MAXSTRLENEX];
    int peso;
    int ripetizioni;
} esercizio;

typedef struct
{
    char nomeAtleta[MAXSTRLENNOME];
    esercizio ex[MAXEXR];
    int numero_esercizi; // numero indicante il numero di celle
    // del vettore ex[...] riempite effettivamente.
} scheda;

scheda *lettura_dati(char *filename);

int soglia(scheda *s, float peso_soglia);

int scrittura_dati(char *filename, scheda *s);

int main()
{
    char *fname = "scheda.csv";
    scheda *s = lettura_dati(fname);
    int n2 = soglia(s, 64);
    int r = scrittura_dati("scheda2.csv", s);
    free(s);
    return r;
}

int soglia(scheda *s, float pesoSoglia)
{
    if (s == NULL)
        return 0;

    int rimodulatoAlmenoUnaVolta = 0;

    // Itera su tutti gli esercizi
    for (int i = 0; i < s->numero_esercizi; i++)
    {
        // Se peso * ripetizioni supera il peso soglia, rimodula il peso
        if (s->ex[i].peso * s->ex[i].ripetizioni > pesoSoglia)
        {
            s->ex[i].peso = pesoSoglia / s->ex[i].ripetizioni;
            rimodulatoAlmenoUnaVolta = 1;
        }
    }
    return rimodulatoAlmenoUnaVolta;
}

void scrittura_dati(char *nomefile, scheda *s)
{
    FILE *fp = fopen(nomefile, "w");
    if (fp == NULL || s == NULL)
    {
        fprintf(stderr, "\n Errore in creazione file o in var. scheda!\n");
        return;
    } 

    fprintf(fp, "%s\n", s->nomeAtleta);

    for (int i = 0; i < s->numero_esercizi; i++)
    {
        fprintf(fp, "%s %d %d\n", s->ex[i].nomeEsercizio,
                s->ex[i].peso,
                s->ex[i].ripetizioni);
    }

    fclose(fp);
}