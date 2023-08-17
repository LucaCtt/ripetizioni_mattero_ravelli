/*
Scrivere una funzione di prototipo
    int sum(int a[N], int b[N], int c[N]);

che riceve in ingresso 2 array a e b contenenti numeri interi nell'intervallo [0,1], da interpretare come bit,
e memorizzi nell'array c di pari lunghezza i valori dei bit risultanti dalla somma in complemento a 2 dei
numeri rappresentati dagli array a e b.
La funzione restituisce 1 se si è verificato un errore e 0 altrimenti.
*/

int sum(int a[N], int b[N], int c[N])
{
    int carry = 0;
    int i;

    for (i = N - 1; i >= 0; i--)
    {
        int sum = a[i] + b[i] + carry;

        // se la somma è 2 3, c'è un riporto
        carry = sum / 2;

        // se la somma è 1 o 3, il risultato è 1.
        // Altrimenti è 0.
        c[i] = sum % 2;
    }

    if ((a[0] && b[0] && !c[0]) || (!a[0] && !b[0] && c[0]))
        return 1;

    return 0;
}