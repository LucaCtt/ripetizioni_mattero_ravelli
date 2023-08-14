/*
Il biscarto è un gioco enigmistico che pone in relazione tre stringhe, ottenendo la terza dalla concatenazione
delle prime due, da cui sia stata tolta una sottostringa comune.
Si progetti un programma di grado di determinare se tre stringhe lette da terminale costituiscono un biscarto.
In particolare, la funzione biscarto dovrà restituire -1 se la terna non costituisce un biscarto, e in caso
contrario un numero intero positivo che rappresenti la posizione nella terza stringa della prima lettera derivante
dalla seconda stringa.

Esempi:
Biscarto (semplice): pavoni / covo = panico (scarto: "vo")
Biscarto centrale: l'arco / l'ombra = la colomba (scarto: "r")
Biscarto iniziale: la claque / l'acrimonia = la querimonia (scarto: "lac")
Biscarto finale: minio / golfo = minigolf (scarto: "o")

Si noti che negli esempi vengono riportati anche gli apostrofi, accenti e spazi che nei casi di test si
considerano già rimossi.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scarto(char *s, char *t, int p, int l);

int biscarto(char *a, char *b, char *c);

int main()
{
    char a[128], b[128], c[128];
    scanf("%s%s%s", a, b, c);
    printf("%d\n", biscarto(a, b, c));
    return 0;
}

// Verifica se t è uno scarto valido da rimuovere dalla stringa s.
// p è la posizione iniziale dello scarto e l è la sua lunghezza.
// La funzione scorre attraverso le due stringhe, tenendo conto di p e l, e confronta i caratteri corrispondenti.
// Se c'è una differenza, restituisce 0, altrimenti restituisce 1.
int scarto(char *s, char *t, int p, int l)
{
    if (strlen(t) + l != strlen(s))
        return 0;

    for (int i = 0, j = 0; i < strlen(t); i++, j++)
    {
        // Ignora i caratteri dello scarto
        if (j == p)
            j += l;

        if (s[j] != t[i])
            return 0;
    }
    return 1;
}

int biscarto(char *a, char *b, char *c)
{
    // Lunghezza delle stringhe di input
    int la = strlen(a);
    int lb = strlen(b);
    int lc = strlen(c);

    int p1, p2;
    int i;

    // Calcola la differenza tra le lunghezze di a e b e la lunghezza di c.
    // Se il risultato è dispari, restituisce -1 poiché le lunghezze non possono soddisfare
    // le condizioni di un biscarto valido.
    if ((la + lb - lc) % 2)
    {
        // nessun biscarto perché i residui non hanno la lunghezza giusta
        return -1;
    }

    int lscarto = (la + lb - lc) / 2; // lunghezza dello scarto per ciascuna stringa

    //  Crea una copia di c che verrà utilizzata per sperimentare diverse posizioni di scarto.
    char *cdup = strdup(c);

    // Esegue per ogni possibile posizione di scarto in c, tranne il primo e l'ultimo carattere.
    for (i = 1; i < lc - 1; i++)
    {
        // Proviamo la posizione i come punto di sezione della stringa c
        cdup[i] = '\0';
        int r1 = 0, r2 = 0;

        // Scorre attraverso a cercando una posizione valida per lo scarto.
        for (p1 = 0; p1 <= la - lscarto; p1++)
        {
            // cerchiamo una posizione p1 per lo scarto in a
            // Chiama la funzione scarto per verificare se la sottostringa cdup è uno scarto valido da rimuovere da a in posizione p1.
            r1 = scarto(a, cdup, p1, lscarto);
            if (!r1)
            {
                continue;
            }

            // Scorre attraverso b cercando una posizione valida per lo scarto.
            for (p2 = 0; p2 <= lb - lscarto; p2++)
            {
                // cerchiamo una posizione p2 per lo scarto in b
                // Chiama la funzione scarto per verificare se la sottostringa di c inizia da i è uno scarto valido da rimuovere da b in posizione p2.
                r2 = scarto(b, &c[i], p2, lscarto);
                if (!r2)
                {
                    continue;
                }

                //  Verifica se le sottostringhe scartate da a e b sono uguali.
                if (strncmp(&a[p1], &b[p2], lscarto) == 0)
                {
                    free(cdup);
                    return i;
                }
            }
        }
        strcpy(cdup, c);
    }
    free(cdup);
    return -1;
}

int main()
{
    char a[128], b[128], c[128];
    scanf("%s %s %s", a, b, c);
    printf("%d\n", biscarto(a, b, c));
    return 0;
}