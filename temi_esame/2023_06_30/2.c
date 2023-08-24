/*
Scrivere un programma C che acquisisca da terminale una stringa i cui caratteri sono da interpretare come
cifre di un numero intero espresso in base dodici (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'a' = 10dec,
'b' = 11dec).
La lunghezza della stringa può variare da 1 a 8 caratteri alfanumerici.
Il programma deve calcolare il valore decimale del numero in base 12 memorizzato come stringa e riportare a
video sia il numero minimo di bit necessari per rappresentarlo in binario naturale sia, sulla riga successiva, il
valore del numero in formato esadecimale.
Nel caso la stringa non rispetti la specifica, il programma riporterà a video il numero -1.
In entrambi i casi, il programma restituisce il valore 0
*/

#include <stdio.h>
#include <string.h>

int daBase12aDecimale(char c)
{
    if (c == 'a' || c == 'A')
        return 10;

    if (c == 'b' || c == 'B')
        return 11;

    // Se il carattere è un numero < 0 o > 9, allora non è valido
    if (c < '0' || c > '9')
        return -1;

    return (int)c - (int)'0';
}

int numBit(int v)
{
    int cont = 0;
    do
    {
        v = v / 2;
        cont += 1;
    } while (v != 0);
    return cont;
}

int main()
{
    // Max 8 caratteri + terminatore di stringa
    char s[9];
    int v, n = 0;
    scanf("%s", s);

    // Controlla innanzitutto la lunghezza della stringa inserita
    if (strlen(s) < 1 || strlen(s) > 8)
    {
        printf("-1\n");
        return 0;
    }

    // Itera tutti i caratteri della stringa,
    // che saranno i numeri in base 12
    for (int i = 0; s[i] != '\0'; i++)
    {
        v = daBase12aDecimale(s[i]);
        // Se la conversione restituisce -1,
        // allora stampa errore
        if (v < 0)
        {
            printf("-1\n");
            return 0;
        }
        // Aggiorna il numero in base 10
        n = n * 12 + v;
    }

    // Stampa numero di bit richiesti in binario e numero in esadecimale
    printf("%d\n%x\n", numBit(n), n);
    return 0;
}