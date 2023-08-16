/*
Scrivere un programma che legga da terminale due sequenze di caratteri (di lunghezza compresa tra 1 e 8)
da interpretare come cifre in base 7.
Ciascuna sequenza è conclusa da un carattere di spaziatura.
Il programma calcola la differenza fra i due valori, e stampa il valore come stringa in rappresentazione binaria
in complemento a due, usando il numero minimo di bit necessario a rappresentare tale risultato.
Nel caso le stringhe non rispettino la specifica, il programma stamperà la stringa "errore 1" o "errore 2"
sul terminale di errore a seconda che la prima stringa specificata in modo scorretto sia la prima o la seconda.
In entrambi i casi, il programma restituisce il valore 0 senza proseguire.
Tutte le stampe devono terminare con un carattere di “a capo”.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Converte un carattere che rappresenta una cifra in base 7
// nel suo equivalente in base 10.
// Restituisce -1 se il carattere non rappresenta una cifra in base 7.
int b7c(char c)
{
    if (c >= '0' && c <= '6')
    {
        return c - '0';
    }

    return -1;
}

// Converte una stringa di cifre in base 7 in un numero intero in base 10.
int b7toint(char *s, int *n)
{
    int c;
    *n = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        c = b7c(s[i]);
        if (c < 0)
        {
            return -1;
        }
        // Aggiorno il valore del numero moltiplicandolo per 7 e sommando la cifra corrente.
        *n = *n * 7 + c;
    }

    return 0;
}

// Stampa un intero m in rappresentazione binaria in complemento a due,
// utilizzando il numero minimo di bit necessario.
void print_bits(int m)
{
    // Calcola numero minimo di bit necessario per rappresentare m.

    // m può essere sia positivo che negativo.
    // n è un puntatore ad m, quindi avrà lo stesso valore di m, e le modifiche a n si rifletteranno su m.
    // Tuttavia essendo n unsigned, ignora il segno di m. Questo semplifica le istruzioni eseguite in seguito.
    unsigned int *n = &m;

    // Numero di bit necessario per rappresentare m.
    int l;
    if (m == 0)
    {
        l = 1
    }
    else if (m < 0)
    {
        // Servono 4 bit per -5 (1011)
        // Servono 4 bit per -8
        l = 1 + ceil(log2(-m));
    }
    else
    {
        // Servono 3 bit per 5 (101)
        // Servono 4 bit per 8 (1000)
        // Essendo l int, viene ignorata la parte decionale di log2.
        l = 1 + log2(m);
    }

    // Alloca memoria dinamica per una stringa s che conterrà la rappresentazione binaria.
    // La dimensione della stringa è l + 1 per contenere i bit binari e il terminatore di stringa ('\0').
    char *s = malloc(sizeof(char) * (l + 1));
    if (!s)
        return;

    //  Inizializza la stringa s con caratteri '0', che rappresentano i bit di valore 0.
    memset(s, '0', l + 1);

    // Scorre da 0 a l e calcola i bit binari per il valore m (rappresentato da n).
    for (int i = 0; *n && i <= l; i++)
    {
        // Assegna al bit corrispondente della stringa s il valore corrente del bit, convertito in carattere.
        s[l - i] = *n % 2 + '0';

        // Dividi il valore n per 2 per passare al prossimo bit.
        *n = *n / 2;
    }

    printf("%s\n", s);
    free(s);
}

int main()
{
    // Leggi due stringhe di lunghezza compresa tra 1 e 8.
    char s[9];
    int n1 = 0, n2 = 0;
    int l;

    // Controlla che la lunghezza della prima stringa sia compresa tra 1 e 8.
    scanf("%s", s);
    l = strlen(s);
    if (l < 1 || l > 8)
    {
        return 0;
    }

    // Converte la stringa in un numero intero e controlla che la conversione sia andata a buon fine.
    if (b7toint(s, &n1))
    {
        printf("errore 1\n");
        return 0;
    }

    // Controlla che la lunghezza della seconda stringa sia compresa tra 1 e 8.
    scanf("%s", s);
    l = strlen(s);
    if (l < 1 || l > 8)
    {
        return 0;
    }
    if (b7toint(s, &n2))
    {
        printf("errore 2\n");
        return 0;
    }

    // Stampa la differenza tra i due numeri in rappresentazione binaria in complemento a due.
    print_bits(n1 - n2);
    return 0;
}