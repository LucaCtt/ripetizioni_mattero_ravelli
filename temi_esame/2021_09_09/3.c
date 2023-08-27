/*
Due parole p, q si definiscono allacciabili se un suffisso proprio s di p è anche prefisso proprio di q,
cioè hanno la forma p=w1s q=sw2 (dove s è proprio se è lungo almeno 2 lettere ma più corto di p e
di q).

(a) Ipotizzando di disporre di una funzione int misuraoverlap(char *p, char *q) che
restituisce la lunghezza del massimo suf-/pre-fisso proprio in comune tra p e q (cioè la lunghezza
di s, se p=w1s, q=sw2), si codifichi in C la funzione ...allaccia(...) che riceve due parole
come parametri e restituisce una nuova stringa (allocata dinamicamente) contenente la parola
ottenuta dall’allacciatura che fattorizza la massima sovrapposizione, oppure NULL se le parole non
sono allacciabili [5 punti]
N.B: è consentito/raccomandato far uso delle funzioni di libreria in <string.h> (strlen,
strcpy, strcat) e in <stdlib.h> (malloc), e/o definire dei proprii sottoprogrammi.

(b) Si codifichi in C la funzione int misuraoverlap(char *p, char *q)
Si complementi la soluzione spieghando in modo chiaro, sintetico e preciso come funziona
l’algoritmo scelto per misuraoverlap(), e in particolare come garantisce che la sottostringa
s sia “massima” (cioè non esista un s’ > s) [5 punti]
*/

char *allaccia(char *p, char *q)
{
    // Risultato allacciamento
    char *r = NULL;

    // Lunghezza overlap tra p e q
    int ov = misuraoverlap(p, q);

    int lp = strlen(p);
    int lq = strlen(q);

    // Se sono allacciabili crea la stringa risultato, che altrimenti rimane NULL
    if (ov >= 2)
    {
        r = (char *)malloc(lp + lq - ov + 1);
        // Copia p in r
        strcpy(r, p);

        // Copia q in r saltando ov
        strcat(r, q + ov);
    }

    return r;
}

int misuraoverlap(char *p, char *q)
{
    // Lunghezza massima overlap
    int max_ov = strlen(p) - 1;

    if (max_ov >= strlen(q))
        max_ov = strlen(q) - 1;

    // Parti con lunghezza max_ov = lunghezza di p, poi diminuisci
    // finché non trovi un overlap
    for (; max_ov >= 2; max_ov--)
        if (SovrapponibiliConNcaratteri(p, q, max_ov))
            return max_ov;

    return 0;
}

// Controlla se le ultime n lettere di p sono uguali alle prime n di q
int SovrapponibiliConNcaratteri(char *p, char *q, int n)
{
    for (int i = 0; i < n; i++)
        if (p[strlen(p) - n + i] != q[i])
            return 0;
    return 1;
}