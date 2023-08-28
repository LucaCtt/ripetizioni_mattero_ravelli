#include <stdio.h>
#include <stdlib.h>

#define MAXLUNG (50)

typedef struct
{
    char codice[5 + 1]; // codice univoco
    int quantita;
    float prezzo;
    char descrizione[300];
} pezzoMeccanico_t;

int main()
{
    char nome[MAXLUNG + 1] = {'\0'};

    printf("\n Inserisci nome file:");
    scanf("%s", nome);

    FILE *fp = fopen(nome, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "\n Errore Apertura File! \n");
        exit(-1);
    }

    pezzoMeccanico_t p;
    float accPrezzo = 0.0;
    int maxq = -1, u;

    // Itera finchè non arriva alla fine del file
    while (!feof(fp))
    {
        fscanf(fp, "%s %d %f %s\n", p.codice, p.quantita, p.prezzo,
               p.descrizione);

        // Se la quantità è maggiore di maxq, aggiorna maxq e accPrezzo
        if (p.quantita > maxq)
        {
            maxq = p.quantita;
            accPrezzo = p.prezzo;
            u = 1;
            continue;
        }

        // Se la quantità è uguale a maxq, aggiorna accPrezzo e u
        if (p.quantita == maxq)
        {
            accPrezzo += p.prezzo;
            u++;
        }
    }

    fprintf(stdout, "\n il prezzo medio dei pezzi meccanici disponibili nel maggior numero di pezzi e’: %.2f", accPrezzo / (u * maxq));
    return 0;
}

void fondiFile(char nomePrimo[], char nomeSecondo[])
{
    // NB i file sono ordinati, per Hp, in ordine crescente di codice
    FILE *fpOut = fopen("PezziSenzaDuplicati.txt", "w"),
         *fp1 = fopen(nomePrimo, "r"),
         *fp2 = fopen(nomeSecondo, "r");

    if (fp == NULL || fp1 == NULL || fp2 == NULL)
    {
        fprintf(stderr, "\n Errore Apertura File! \n");
        exit(-1);
    }

    pezzoMeccanico_t pPrimo, pSec;
    // Leggi dal primo file
    fscanf(fp1, "%s %d %f %s\n", pPrimo.codice, pPrimo.quantita,
           pPrimo.prezzo, pPrimo.descrizione);
    // Leggi dal secondo file
    fscanf(fp2, "%s %d %f %s\n", pSec.codice, pSec.quantita,
           pSec.prezzo, pSec.descrizione);

    // Itera finchè non raggiungo la fine di almeno uno dei due file
    while ((!feof(fp1)) && (!feof(fp2)))
    {
        // Copia i pezzi dai file di input nel file di output
        // Scrivi in ordine crescente di codice
        if (strcmp(pPrimo.codice, pSec.codice) < 0)
        {
            fprintf(fpOUT, "%s %d %f %s\n", pPrimo.codice, pPrimo.quantita,
                    pPrimo.prezzo, pPrimo.descrizione);
            fscanf(fp1, "%s %d %f %s\n", pPrimo.codice, pPrimo.quantita,
                   pPrimo.prezzo, pPrimo.descrizione);
        }
        else if (strcmp(pPrimo.codice, pSec.codice) > 0)
        {
            fprintf(fpOUT, "%s %d %f %s\n", pSec.codice, pSec.quantita,
                    pSec.prezzo, pSec.descrizione);
            fscanf(fp1, "%s %d %f %s\n", pSec.codice, pSec.quantita,
                   pSec.prezzo, pSec.descrizione);
        }
    }

    // A questo punto ho finito di leggere o fp1 o fp2.
    // Copio le righe residue dal file che non ho finito di leggere

    while (!feof(fp1))
    {
        fprintf(fpOUT, "%s %d %f %s\n", pPrimo.codice, pPrimo.quantita,
                pPrimo.prezzo, pPrimo.descrizione);
        fscanf(fp1, "%s %d %f %s\n", pPrimo.codice, pPrimo.quantita,
               pPrimo.prezzo, pPrimo.descrizione);
    }

    while (!feof(fp2))
    {
        fprintf(fpOUT, "%s %d %f %s\n", pPrimo.codice, pPrimo.quantita,
                pPrimo.prezzo, pPrimo.descrizione);
        fscanf(fp2, "%s %d %f %s\n", pPrimo.codice, pPrimo.quantita,
               pPrimo.prezzo, pPrimo.descrizione);
    }

    fclose(fpOUT);
    fclose(fp1);
    fclose(fp2);
}