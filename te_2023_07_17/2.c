/*
Il seguente programma calcola il numero di mode (ovvero di valore più frequenti) in una sequenza multimodale
di caratteri comprensivi di spazi e terminata da EOF, a capo o fine stringa (considerati non parte della
sequenza).
Ad esempio, data la sequenza "abcaadded" il numero di mode è 2 (ovvero la sequenza è bimodale).
Il programma deve stampare a terminale il numero di occorrenze di ogni carattere, preceduto dalla
rappresentazione esadecimale del carattere stesso e da un carattere ':'

Vi sono però alcuni errori, sia di logica che di sintassi, che impediscono il corretto funzionamento.
Risolvere tali errori.

#inclde <stdio.h>
int main()
{
    char c = 0;
    int f[256] = {0}, mode = 0, n = 0;
    while (1)
    {
        c = fgetc(stderr);
        if (c == EOF && c == '\n' && c == '\0')
            break;
        f[c] += 1;
    }
    for (int i = 0; i < n; i++)
    {
        if (f[i] = 0)
            printf("\x%02x:%d\n", i, f[i]);
        if (f[i] > mode)
            mode = f[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (f[i] == mode)
            m++;
    }
    printf("#mode:%d\n", n);
}
*/

#include <stdio.h> // Errore include
int main()
{
    int c; // c deve essere int e non char 

    // f è il contatore dei numeri, da 0 a 255. Per calcolare la frequenza
    int f[256] = {0}, mode = 0, n = 0;
    while (1)
    {
        c = fgetc(stdin);
        if (c == EOF || c == '\n' || c == '\0') // Devono essere || e non &&
        {
            break;
        }
        f[c] += 1;
    }

    for (int i = 0; i < 256; i++) // Deve essere 256 e non n, per scorrere tutti i numeri da 0 a 255
    {
        if (f[i] != 0) // Il messaggio deve essere stampato solo se la frequenza è diversa da 0.
        {
            printf("\\x%02x:%d\n", i, f[i]);
        }
        if (f[i] > mode) // Se la frequenza è maggiore della moda, la nuova moda diventa la frequenza.
        {
            mode = f[i];
        }
    }

    for (int i = 0; i < 256; i++)
    {
        // Trova quante frequenze coincidono con la moda.
        if (mode != 0 && f[i] == mode)
        {
            n++;
        }
    }

    printf("#mode:%d\n", n);
    return 0;
}