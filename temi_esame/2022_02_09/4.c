/*
Data una matrice di interi con R righe e C colonne, scrivere un sottoprogramma che riorganizzi

    • gli elementi lungo le righe di indice dispari, come sequenze di valori che scandite da sinistra a
    destra esibiscono in colonna [0] il massimo valore nelle colonne 0...C-1, in colonna [1]
    il minimo valore nelle colone 1...C-1, in colonna [2] il massimo valore nelle colonne
    2...C-1, in colonna [3] il minimo valore nelle colonne 3...C-1 e così via alternando
    massimi e minimi con lo stesso criterio fino a esaurimento dei valori sulla riga.
    • gli elementi lungo le righe di indice pari, come sequenze di valori che scandite da sinistra a

    destra esibiscono in colonna [0] il minimo valore nelle colone 0...C-1, in colonna [1] il
    massimo valore nelle colonne 1...C-1, in colonna [2] il minimo valore nelle colonne
    2...C-1, in colonna [3] il massimo valore nelle colonne 3...C-1 e così via alternando
    minimi e massimi con lo stesso criterio fino a esaurimento dei valori sulla riga.
*/

void riorganizza_crescente(int vett[], int n)
{
    int massimo, minimo;
    int posMassimo, posMinimo;

    // Itera prima 0..n-1, poi 1..n-1, poi 2..n-1, ecc.
    for (int i = 0; i < n; i++)
    {
        // Considero il sottovettore che va da i a n-1

        // Inizializza massimo e minimo con il primo elemento del 
        massimo = minimo = vett[i];
        posMassimo = posMinimo = i;

        // Cerca il massimo e il minimo nel sottovettore
        for (int k = i + 1; k < n; k++)
        {
            if (vett[k] > massimo)
            {
                posMassimo = k;
                massimo = vett[k];
            }
            if (vett[k] < minimo)
            {
                posMinimo = k;
                minimo = vett[k];
            }
        }

        // Se l'indice è pari, metto il massimo, altrimenti il minimo
        if (i % 2 == 0)
            vett[i] = vett[posMinimo];
        else
            vett[i] = vett[posMassimo];
    }
}

void riorganizza_decrescente(int vett[], int n)
{
    int massimo, minimo;
    int posMassimo, posMinimo;

    for (int i = 0; i < n; i++)
    {
        massimo = minimo = vett[i];
        posMassimo = posMinimo = i;

        for (int k = i + 1; k < n; k++)
        {
            if (vett[k] > massimo)
            {
                posMassimo = k;
                massimo = vett[k];
            }
            if (vett[k] < minimo)
            {
                posMinimo = k;
                minimo = vett[k];
            }
        }

        if (i % 2 == 0)
            vett[i] = vett[posMassimo];
        else
            vett[i] = vett[posMinimo];
    }
}

// Matrice rappresentata con un singolo vettore,
// avrà quindi lunghezza r * c
void riorganizzazione(int *mat, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        if (i % 2 == 0)
            // Riorganizza righe pari.
            // Passo l'indirizzo della riga i-esima:
            // mat = puntatore alla prima cella della matrice
            // i * c = indice della prima cella della riga i-esima
            riorganizza_crescente(mat + i * c, c);
        else
            // Riorganizza righe dispari
            riorganizza_decrescente(mat + i * c, c);
    }
}