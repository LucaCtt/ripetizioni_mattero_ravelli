/*
I dati degli atleti di una società sportiva sono classificati in un file, che contiene per ogni riga la descrizione di
un atleta, costituita dal suo nome (una stringa di caratteri alfabetici di al più 31 elementi), e da quattro numeri
compresi tra 0 e 20, che rappresentano la valutazione, nell'ordine, della forza, agilità, velocità e resistenza
dell'atleta.

Ad esempio, un file di questo tipo potrebbe contenere i dati:
tizio
14 15 6 8
caio
10 12 10 12
sempronio 12 14 18 11

Per costituire una squadra, è necessario che gli atleti siano dotati di caratteristiche compatibili fra loro. A tale
scopo, si considera che gli atleti di una squadra siano compatibili se, per ciascuna delle loro caratteristiche,
non vi è una distanza fra due atleti pari o superiore a 5.

Impiegando il main ed i tipi di strutture dati forniti, realizzare un programma che:
a. Carica da file i dati in una apposita struttura dati di tipo "squadra" (funzione "carica_dati");
[5 punti]
b. Verifica che una squadra sia compatibile, restituendo 1 in tale caso e 0 in caso contrario (funzione
"verifica"); [4 punti]
c. Nel caso in cui vi siano più di sei atleti nella società, determina se sia possibile comporre una squa-
dra di 5 elementi compatibili (funzione "esiste_squadra"). [3 punti]
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum
{
    FORZA,
    AGILITA,
    VELOCITA,
    RESISTENZA
} caratteristiche_t;

typedef struct
{
    char nome[32];
    unsigned short caratteristiche[4]; /* Si possono usare gli elementi di caratteristiche_t per indicizzare questo array */
} persona_t;

typedef struct
{
    persona_t *elementi; /* Contiene i dati degli atleti */
    unsigned numero; /* Numero di atleti nel campo elementi */
} squadra_t;

squadra_t carica_dati(char *nome_file);

int verifica(squadra_t s);

int esiste_squadra(squadra_t s);

int main()
{
    // Leggi nome file
    char nomef[100];
    scanf("%s", nomef);

    squadra_t s = carica_dati(nomef);
    printf("%d\n", s.numero);

    if (s.numero > 1 && s.numero < 5)
        printf("%d\n", verifica(s));
    if (s.numero > 5)
        printf("%d\n", esiste_squadra(s));
}

squadra_t carica_dati(char *nome_file)
{
    squadra_t r = {0};
    FILE *fin = fopen(nome_file, "r");
    if (!fin)
    {
        fclose(fin);
        return r;
    }

    persona_t tmp;
    int i;

    // Conta il numero di righe
    while (fscanf(fin, "%s%hu%hu%hu%hu",
                  tmp.nome,
                  &tmp.caratteristiche[FORZA],
                  &tmp.caratteristiche[AGILITA],
                  &tmp.caratteristiche[VELOCITA],
                  &tmp.caratteristiche[RESISTENZA]) == 5)
    {
        r.numero++;
    }

    // Torna all'inizio del file
    rewind(fin);

    // Alloca l'array di elementi
    r.elementi = malloc(sizeof(persona_t) * r.numero);

    // Se non è stato possibile allocare l'array, restituisci una struttura vuota
    if (!r.elementi)
    {
        r.elementi = 0;
        fclose(fin);
        return r;
    }

    // Leggi gli elementi
    i = 0;
    while (fscanf(fin, "%s%hu%hu%hu%hu", r.elementi[i].nome,
                  &r.elementi[i].caratteristiche[FORZA],
                  &r.elementi[i].caratteristiche[AGILITA],
                  &r.elementi[i].caratteristiche[VELOCITA],
                  &r.elementi[i].caratteristiche[RESISTENZA]) == 5)
    {
        i++;
    }

    fclose(fin);
    return r;
}

int verifica(squadra_t s)
{
    // Valore massimi e minimi per ogni caratteristica
    unsigned short max[4] = {0};
    unsigned short min[4] = {20, 20, 20, 20};

    int c, p, r = 1;
    // Itera le caratteristiche
    for (c = FORZA; c <= RESISTENZA; c++)
    {
        // Itera gli atleti
        for (p = 0; p < s.numero; p++)
        {
            // Se la caratteristica è maggiore del massimo, aggiorna il massimo
            if (s.elementi[p].caratteristiche[c] > max[c])
                max[c] = s.elementi[p].caratteristiche[c];

            // Se la caratteristica è minore del minimo, aggiorna il minimo
            if (s.elementi[p].caratteristiche[c] < min[c])
                min[c] = s.elementi[p].caratteristiche[c];
        }
    }
    
    // Controlla che la differenza tra massimo e minimo sia minore di 5 per ogni caratteristica.
    // Se non lo è, la squadra non è compatibile.
    for (c = FORZA; c <= RESISTENZA; c++)
    {
        if (max[c] - min[c] >= 5)
            r = 0;
    }

    return r;
}

int esiste_squadra(squadra_t s)
{
    // Crea una squadra vuota di 5 elementi
    squadra_t r;
    r.numero = 5;
    r.elementi = malloc(sizeof(persona_t) * 5);

    int i, j, k, l, m;

    // Prova tutte le combinazioni di 5 elementi
    for (i = 0; i < s.numero; i++)
    {
        r.elementi[0] = s.elementi[i];
        for (j = i + 1; j < s.numero; j++)
        {
            r.elementi[1] = s.elementi[j];
            for (k = j + 1; k < s.numero; k++)
            {
                r.elementi[2] = s.elementi[k];
                for (l = k + 1; l < s.numero; l++)
                {
                    r.elementi[3] = s.elementi[l];
                    for (m = l + 1; m < s.numero; m++)
                    {
                        r.elementi[4] = s.elementi[m];
                        if (verifica(r))
                        {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}