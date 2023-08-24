/*
Si completi il programma seguente esibendo il codice dei sottoprogrammi
    ...leggi_aerei(...); e ...capacita_max(...);

Il programma legge da un file che contiene nomi, velocità e numero di passeggeri di vari modelli di aerei di
linea e stampa a terminale:

    (a) il conteggio di quanti aerei sono descritti nel file;
    (b) i modelli di aereo con la massima capacità effettiva (ovvero la capacità di trasportare il massimo
        numero di passeggeri per unità di tempo).

Il file letto ha il seguente formato (il numero di righe del file è arbitrario):

Modello Velocità Passeggeri
Concorde 2179 100
Tu-144 2300 110
Boeing-747 1061 660
Boeing-707 987 194
Il-62 850 186
A380 1049 868
…

La prima riga contiene l'intestazione e deve essere scartata.
Ogni riga successiva alla prima contiene tre campi: modello, velocità e passeggeri.
I modelli sono stringhe prive di spazi composte da caratteri alfanumerici, con al più la presenza del carattere
trattino (-). Le velocità e i passeggeri sono numeri interi.
*/

#include <stdio.h>
#include <stdlib.h>

struct aereo
{
    char modello[128];
    int velocita;
    int passeggeri;
};

typedef struct aereo aereo_t;

aereo_t *leggi_aerei(char *nome_file, int *numero_aerei);

void capacita_max(aereo_t *aerei, int numero_aerei);

int main()
{
    int numero_aerei = 0;

    // Leggi il nome del file da stdin
    char file[200];
    scanf("%s", file);

    aereo_t *aerei = leggi_aerei(file, &numero_aerei);

    printf("%d\n", numero_aerei);
    if (!aerei)
    {
        return 0;
    }

    capacita_max(aerei, numero_aerei);

    free(aerei);
    return 0;
}

int conta_aerei(FILE *file)
{
    // i = numero di aerei
    int i = 0;

    // a, b, c = stringhe temporanee per leggere i campi
    char a[128], b[128], c[128];
    int n, m;

    // Se non leggo tre stringhe da file, allora il file è vuoto
    if (fscanf(file, "%s%s%s", a, b, c) != 3)
    {
        return 0;
    }

    // A questo punto ho letto la prima riga correttamente
    // Procedo a contare le righe successive, che sono
    // quelle che contengono i dati degli aerei
    while (fscanf(file, "%s%d%d", a, &n, &m) == 3)
    {
        i++;
    }

    // Riavvolgo il file per poterlo leggere nuovamente
    rewind(file);

    // Scarto la prima riga
    fscanf(file, "%s%s%s", a, b, c);

    return i;
}

aereo_t *leggi_aerei(char *nome_file, int *numero_aerei)
{
    int i;

    // Variabile temporanea
    aereo_t *res = NULL;

    FILE *fin = fopen(nome_file, "r");
    if (!fin)
    {
        return NULL;
    }

    // Non sappiamo a priori il numero di aerei nel file,
    // quindi lo calcoliamo con la funzione conta_aerei
    *numero_aerei = conta_aerei(fin);
    res = (aereo_t *)malloc(sizeof(aereo_t) * (*numero_aerei));
    if (!res)
    {
        fclose(fin);
        return NULL;
    }

    // Adesso posso leggere gli aerei veri e propri
    for (i = 0; i < *numero_aerei; i++)
    {
        // Se non leggo tre stringhe da file, allora ho trovato una riga non valida
        if (fscanf(fin, "%s%d%d", res[i].modello, &res[i].velocita, &res[i].passeggeri) != 3)
        {
            return res;
        }
    }

    fclose(fin);
    return res;
}

void capacita_max(aereo_t *aerei, int numero_aerei)
{
    int max = 0;
    int i;

    // Trova la capacità massima
    // capacità = velocità * passeggeri
    for (i = 0; i < numero_aerei; i++)
    {
        if (max < aerei[i].velocita * aerei[i].passeggeri)
        {
            max = aerei[i].velocita * aerei[i].passeggeri;
        }
    }

    // Stampa info dell'aereo con capacità massima
    for (i = 0; i < numero_aerei; i++)
    {
        if (max == aerei[i].velocita * aerei[i].passeggeri)
        {
            printf("%s\n", aerei[i].modello);
        }
    }
}