/*
(a) Scrivere una funzione di prototipo:

    int controlla_permutazione(int p[], int lung)

    che abbia come parametri un array di interi e la sua lunghezza e che restituisca 1 se l’array
    contiene i valori di una permutazione valida, 0 altrimenti.
    Un array di interi contiene una permutazione valida se i valori in ogni cella sono tutti e soli i numeri
    che possono rappresentare la posizione di una cella dell’array stesso.

    Esempio:
    indice:
    0
    1
    2
    3
    4
    5

    array p: [ 1, 3, 2, 4, 5, 0 ]
(b) Scrivere una funzione

    int applica_permutazione(char str[], int p[], int lung)

    che abbia come parametri una stringa, un array di interi e un intero indicante la lunghezza
    dell’array di interi. Se l’array di interi rappresenta una permutazione valida e ha la stessa lunghezza
    della stringa, la funzione applica la permutazione ai caratteri della stringa indicata come parametro
    e restituisce 1, altrimenti 0.

    Esempio:
    str: "AIRONE"
    array p: [ 1, 3, 2, 4, 5, 0 ]
    lung: 6
    dopo l’esecuzione della funzione str: "AIRONE" diventa
    str: "EARION"

    N.B: è consentito/raccomandato far uso delle funzioni di libreria in <string.h> e
    ...malloc(...)
*/

int controlla_permutazione(int p[], int lung)
{
    if (lung <= 0)
        return 0;

    // Itera tutti i numeri da o a lung
    for (int idx = 0; idx < lung; idx++)
    {
        // Se l'elemento idx-esimo di p è invalido, restituisci 0
        if (p[idx] < 0 || p[idx] > lung - 1)
            return 0;

        // Altrimenti controlla che non ci siano numeri duplicati in p
        for (int i = 0; i < lung; i++)
            if (i != idx && p[idx] == p[i])
                return 0;
    }

    return 1;
}

int applica_permutazione(char str[], int p[], int lung)
{
    if (lung != strlen(str) || controlla_permutazione(p, lung) == 0)
        return 0;

    // Copia str in una stringa temporanea
    char *temp = (char *)malloc(sizeof(char) * (lung + 1));
    if (temp == NULL)
        return 0;
    strcpy(temp, str);

    // Per ogni elemento di p, copia il carattere corrispondente
    for (int i = 0; i < lung; i++)
    {
        str[p[i]] = temp[i];
    }

    free(temp);
    return 1;
}