/*
Scrivere un programma C che:
    • Legga dal terminale un numero intero dispari n.
    • Legga dal terminale una sequenza s di numeri interi separati da spazi e terminata da un qualunque
      carattere non numerico.
    • Stampi a terminale, per ogni sottosequenza di lunghezza n nella sequenza s (partendo da sinistra) la
      media dei suoi elementi pesata con un peso pari a 1 per il primo e l'ultimo elemento, 4 per il secondo
      e il penultimo, 9 per il terzo e il terzultimo, etc. (ovvero pesi pari al quadrato della distanza
      dall'estremo più vicino, con l'elemento centrale pesato con peso pari al quadrato di n/2+1). Ad
      esempio, per sottosequenze di lunghezza 5, i pesi saranno, nell’ordine, 1, 4, 9, 4, 1.
    • Nel caso in cui non venga letto un numero intero n dispari, il programma stampa il messaggio di errore
      "n pari o non letto correttamente".
    • In entrambi i casi, il programma deve restituire il valore 0.
*/

#include <stdio.h>
#include <stdlib.h>
#define OK 0

char *errmsg = "n pari o non letto correttamente";

float filtro(int w[], int l);

void scorrimento(int w[], int l);

int main()
{
    // Leggi intero dispari n
    int n = 0;
    scanf("%d", &n);
    if (!(n % 2))
    {
        printf("%s", errmsg);
        return OK;
    }

    // Leggi sequenza di numeri interi
    int *f = malloc(sizeof(int) * n);
    int r = 1, l = 0;
    do
    {
        int x = 0;
        // r = numero di elementi letti da stdin
        // Dovrebbe essere uguale a 1 se è stato letto un intero
        r = scanf("%d", &x);

        // Il ciclo termina solo se NON leggo un intero
        if (!r)
            break;

        f[l] = x;

        // l = numero di sequenza, da 0 a n-1
        l++;

        // Se la sequenza è più corta di n, continua
        if (l < n)
            continue;

        // Se ho letto n elementi, stampa la media pesata
        printf("%f\n", filtro(f, n));
        // Scarta l'ultimo elemento della sequenza e sposta tutti gli altri a sinistra
        // in modo da poter leggere il prossimo elemento
        scorrimento(f, n);

        // Decrementa l per poter effettuare un nuovo ciclo di lettura
        l--;
    } while (1);

    free(f);
    return OK;
}

// Restituisce il valore assoluto di x
int abs(int x)
{
    return (x < 0 ? -x : x);
}

// Restituisce la media pesata degli elementi di w
float filtro(int w[], int l)
{
    // sum = somma pesata degli elementi di w
    // hl = indice dell'elemento centrale di w
    // tw = somma dei pesi degli elementi di w
    int sum = 0, hl = l / 2, tw = 0;

    for (int i = 0; i < l; i++)
    {
        int weight = hl + 1 - abs(i - hl);
        sum += w[i] * weight * weight;
        tw += weight * weight;
    }

    return sum / (float)tw;
}

void scorrimento(int w[], int l)
{
    for (int i = 1; i < l; i++)
        w[i - 1] = w[i];
}