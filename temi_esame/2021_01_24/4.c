#include <stdio.h>
#include <stdlib.h>

unsigned int calcola_vittoria(char mappa[3][3]);

int main()
{
    FILE *fp = fopen("partita.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "\nErrore nellꞌapertura del file ");
        fprintf(stderr, "- terminazione del programma! \n");
        exit(-1);
    }

    char mappa[3][3];
    int i;

    for (i = 0; i < 3; i++)
    {
        fscanf(fp, "%c", &mappa[i][0]);
        fscanf(fp, "%c", &mappa[i][1]);
        fscanf(fp, "%c", &mappa[i][2]);
        fscanf(fp, "\n");
    }

    printf("\nValutazione mappa del Tris:%u\n", calcola_vittoria(mappa));
    fclose(fp);
    return 0;
}

// per scelta implementativa non si considera il caso
// di partite impossibili con 2 vincitori
unsigned int calcola_vittoria(char mappa[3][3])
{
    int i, k;
    int num_x_in_diagonale1 = 0, num_x_in_diagonale2 = 0;
    int num_o_in_diagonale1 = 0, num_o_in_diagonale2 = 0;

    for (k = 0; k < 3; k++)
    {
        // Diagonale principale
        if (mappa[k][k] == 'x')
            num_x_in_diagonale1++;
        else if (mappa[k][k] == 'o')
            num_o_in_diagonale1++;

        // Diagonale opposta
        if (mappa[k][2 - k] == 'x')
            num_x_in_diagonale2++;
        else if (mappa[k][2 - k] == 'o')
            num_o_in_diagonale2++;

        // Controllo della k-esima riga e della k-esima colonna
        int num_x_in_riga = 0, num_o_in_riga = 0;
        int num_x_in_colonna = 0, num_o_in_colonna = 0;

        for (i = 0; i < 3; i++)
        {
            if (mappa[k][i] == 'x')
                num_x_in_riga++;
            else if (mappa[k][i] == 'o')
                num_o_in_riga++;

            if (mappa[i][k] == 'x')
                num_x_in_colonna++;
            else if (mappa[i][k] == 'o')
                num_o_in_colonna++;
        }

        // Controllo se c'è un vincitore basandomi sulle righe e sulle colonne
        if (num_x_in_riga == 3 || num_x_in_colonna == 3)
            return 1;
        if (num_o_in_riga == 3 || num_o_in_colonna == 3)
            return 2;
    }

    // Controllo se c'è un vincitore basandomi sulle diagonali
    if (num_x_in_diagonale1 == 3 || num_x_in_diagonale2 == 3)
        return 1;
    if (num_o_in_diagonale1 == 3 || num_o_in_diagonale2 == 3)
        return 2;
    return 0;
}