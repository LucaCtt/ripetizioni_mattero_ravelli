/*
Scrivere un programma che legga da terminale triple di numeri interi A, B, C, e stampi a video una linea
contenente il numero d'ordine della tripla letta (assumendo che la prima tripla sia numerata 1) se per tale
tripla la formula logica
not (A or C) or not B and C
è vera.
Nel caso in cui invece la formula risulti falsa, il programma non stampa nulla.
Il programma termina se A, B e C sono tutti e tre negativi.
*/

#include <stdio.h>

int main()
{
    // Il numero d'ordine di una tripla è il numero
    // di sequenza della tripla stessa.

    int a, b, c, i = 1;
    do
    {
        // Leggi i valori
        scanf("%d%d%d", &a, &b, &c);

        if (!(a || c) || !b && c)
            printf("%d\n", i);

        i++;

    } while (!(a < 0 && b < 0 && c < 0));

    return 0;
}