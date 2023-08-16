/*
Implementare una funzione di prototipo
 char *neg(char *s)

che riceve una stringa contenente caratteri '0' e '1', interpretata come un numero binario n (la cifra più
significativa è nella posizione 0), e restituisce una nuova stringa che contiene il numero -n (opposto),
espresso sullo stesso numero di bit.
*/

char *neg(char *s)
{
    int l = strlen(s);
    // Carry iniziale a 1
    int carry = 1;

    // Allocazione della stringa risultato,
    // con dimensione uguale a quella di s + 1 per il terminatore di stringa
    char *r = malloc(sizeof(char) * (l + 1));

    // Terminatore di stringa
    r[l] = '\0';

    // Inverti bit e aggiungi 1
    for (int i = l - 1; i >= 0; i--)
    {
        if (s[i] == '0')
        {
            if (!carry)
                r[i] = '1';
            else
                r[i] = '0';
        }
        else
        {
            if (!carry)
                r[i] = '0';
            else
            {
                r[i] = '1';
                carry = 0;
            }
        }
    }

    return r;
}

int main()
{
    char *s = "001011";
    char *r = neg(s);
    printf("%s\n", r);
    free(r);
    return 0;
}