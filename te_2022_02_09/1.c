/*
La funzione foo (vedere codice allegato) ha come obiettivo quello di modificare la stringa s rimuovendo
l'ultimo carattere se e solo se la differenza numerica tra il primo e l'ultimo carattere della stringa stessa è
pari in valore assoluto al valore del parametro num. Inoltre, la funzione stampa la differenza calcolata e il
parametro num.

Ad esempio, se foo viene invocata con i parametri "ASTRA" e 0, l'ultima lettera di ASTRA deve essere
sovrascritta con il carattere terminatore.
Fornendo "ASTRA" come stringa iniziale, il main fornito dovrebbe quindi restituire come output a terminale
il seguente testo:
ASTRA
0, 0
ASTR
1, 1
AST
AST

La funzione foo fornita presenta però due errori di sintassi che ne impediscono la corretta compilazione, e
due ulteriori errori logici che ne impediscono il corretto funzionamento.
Trovare e correggere i quattro errori.
*/

#include <stdio.h>
#include <string.h>

int foo(char *s, int num)
{
    int lung = strlen(s);
    if (lung <= 1)
        return 0; // Punto e virgola

    int temp = (int)s[0] - (int)s[lung-1]; // lung - 1 
    printf("%d, %d\n", temp, num); // Stringa non terminata

    if (temp == num || temp == -num)
    {
        // A ogni iterazione accorcia di un carattere dal fondo la stringa
        s[lung - 1] = '\0'; // \0
        return 1;
    }
    else
        return 0;
}

int main()
{
    char str[20];
    int i = 0, flag;
    scanf("%s", str);
    printf("%s\n", str);
    do
    {
        // A ogni iterazione accorcia di un carattere la stringa dall'inizio
        flag = foo(&str[i], i);
        i += 1;
        printf("%s\n", str);
    } while (flag == 1);
}