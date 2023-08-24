/*
Scrivere un programma C che legga da terminale una stringa di lunghezza arbitraria, considerando soltanto i
caratteri alfabetici (cioè quelli che rappresentano lettere maiuscole o minuscole, escluse quelle dotate di accenti
o altri segni diacritici), e stampi a terminale:
1) sulla prima riga, la mediana del numero di occorrenze dei caratteri alfabetici nella stringa letta (considerando identici i caratteri maiuscoli e minuscoli), o 0 in caso di nessun carattere valido letto;
La mediana in una sequenza numerica è definita come il “valore centrale” della sequenza ordinata in
ordine ascendente. Se la sequenza è di lunghezza pari, la mediana è calcolata come la media aritmetica
dei due valori centrali.
Esempio: [1, 4, 5, 7], mediana = (4+5)/2= 4.5
Esempio: [6, 11, 16], mediana = 11
Attenzione: per ogni esecuzione del programma la mediana deve essere calcolata considerando le
lettere inserite (quindi quelle con num. di occorrenze >= 1) e non necessariamente tutto l’alfabeto.
2) sulle righe successive, i caratteri (minuscoli, uno per riga, e in ordine alfabetico) il cui numero di
occorrenze è diverso da zero, seguiti dal carattere ‘:’ e dal proprio numero di occorrenze;
3) sull’ultima riga, la sequenza di caratteri (minuscoli, in ordine alfabetico, e senza spaziature) il cui
numero di occorrenze è maggiore della mediana.
*/

#include <stdio.h>
#include <ctype.h>

#define N 26 // Numero di lettere dell'alfabeto

float mediana(int a[N]);

int main()
{
    int occorrenze[N] = {0};
    char c;
    int i;

    do
    {
        // Leggi un singolo carattere da stdin
        c = (char)getchar();

        // Se c è una lettera maiuscola, trasformala in minuscola
        if (c >= 'A' && c <= 'Z')
            c = (char)((int)c - (int)'A' + (int)'a');

        // Se c è una lettera minuscola, incrementa il contatore
        // NB: conta anche le lettere maiuscole convertite prima in minuscole
        if (c >= 'a' && c <= 'z')
            occorrenze[(int)c - (int)'a'] += 1;

        // Ripeti fino a che non viene inserito uno spazio, un terminatore di stringa o EOF
    } while (!isspace(c) && c != '\0' && c != EOF);

    float m = mediana(occorrenze);
    printf("%f\n", m);

    // Itera tutti gli indici delle lettere dell'alfabeto
    for (i = 0; i < N; i++)
    {
        // Stampa il numero di occorrenze per ogni carattere
        // con occorrenza > 0
        if (occorrenze[i] != 0)
            printf("%c:%d\n", (char)((int)'a' + i), occorrenze[i]);
    }

    for (i = 0; i < N; i++)
    {
        // Stampa il carattere solo se il numero di occorrenze
        // è maggiore della mediana
        if (occorrenze[i] > m)
            printf("%c", (char)((int)'a' + i));
    }

    printf("\n");
    return 0;
}

float mediana(int a[N])
{
    // array è una copia di a
    // cont è il numero di zeri in a
    int array[N], cont = 0;
    int i, j;


    // Copia a in array e conta il numero di zeri
    for (i = 0; i < N; i++)
    {
        if (a[i] == 0)
            cont++;
        array[i] = a[i];
    }

    // Se tutti gli elementi sono zeri, allora la mediana è 0
    if (cont == N)
    {
        return 0;
    }

    // Ordina array in ordine crescente
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (array[i] < array[j])
            {
                int t = array[i];
                array[i] = array[j];
                array[j] = t;
            }
        }
    }

    // Gli zeri a questo punto sono all'inizio dell'array,
    // quindi andranno saltati

    // Lunghezza dell'array pari
    if ((N - cont) % 2 == 0)
        return ((float)array[cont + (N - cont) / 2] +
                (float)array[cont + (N - cont) / 2 - 1]) /
               2;

    // Lunghezza dell'array dispari
    return (float)array[cont + (N - cont) / 2];
}