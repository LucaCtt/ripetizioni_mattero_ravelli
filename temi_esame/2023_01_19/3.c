/*
Si consideri un array di interi positivi senza duplicati nell’intervallo 1 ... MAXNUM.

Scrivere un sottoprogramma C
... replace(...);

che abbia come parametro un array di interi e la sua lunghezza che controlli che l’array usato come suo
argomento contenga solo numeri positivi senza duplicati. Nel caso in cui il controllo non dia esito positivo, il
sottoprogramma deve restituire zero, altrimenti prosegue sostituendo ogni elemento dell’array con
l’elemento più piccolo tra quelli aventi valore maggiore di lui che sono posizionati alla sua destra oppure con
-1 se non ci sono elementi maggiori di lui alla sua destra; il sottoprogramma termina restituendo 1 al
programma chiamante.
*/

#include <stdio.h>
#define MAXNUM 100

int checkPositiveNoDuplicates(int nums[], int n);

int replace(int nums[], int n);

int main(void)
{
    // n = lunghezza dell'array
    // i = contatore da 0 a n
    // r = risultato della funzione replace
    int i, r, n = 0;
    scanf("%d", &n);

    int *nums = malloc(sizeof(int) * n);
    if (nums == NULL)
    {
        printf("errore in allocazione\n");
        return 0;
    }

    for (i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    r = replace(nums, n);
    if (r == 0)
    {
        printf("Array non valido\n");
    }
    else if (r == 1)
    {
        // Stampa l'array risultante
        for (i = 0; i < n; i++)
            printf("%d ", nums[i]);
    }

    free(nums);

    return 0;
}

// Restituisce 1 se ci sono duplicati e/o numeri negativi, 0 altrimenti
int checkPositiveNoDuplicates(int nums[], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        if (nums[i] < 0)
            return 0;

        for (j = i + 1; j < n; j++)
            if (nums[j] == nums[i])
                return 0;
    }

    return 1;
}

// Sostituisci ogni elemento dell'array specificato con il
// elemento meno maggiore alla sua destra
int replace(int nums[], int n)
{
    int i, j;
    if (checkPositiveNoDuplicates(nums, n) == 0)
        return 0;

    // Attraversa l'array dall'inizio
    for (i = 0; i < n; i++)
    {
        int successor = -1;
        int diff = MAXNUM;

        // Controlla ogni elemento a destra per un successore
        for (j = i + 1; j < n; j++)
        {
            if (nums[j] > nums[i] && (nums[j] - nums[i] < diff))
            {
                successor = nums[j];
                diff = nums[j] - nums[i];
            }
        }

        nums[i] = successor;
    }
    return 1;
}