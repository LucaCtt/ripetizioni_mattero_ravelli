/*
(a) Progettare e implementare una funzione di prototipo
        exercise *read_exercises();

    che legga da terminale una sequenza di linee di testo di lunghezza arbitraria, e interpreti ciascuna riga
    come la specifica di un esercizio, costituita da:

        •nome: una stringa di testo non più lunga di 127 caratteri.
        •lista di muscoli esercitati: una sequenza non vuota di numeri interi nell'intervallo da 1 a 14
         (corrispondenti ai valori del tipo enumerativo muscle_groups), senza ripetizioni ma
         possibilmente non ordinati, separati da un singolo spazio o carattere di tabulazione.

    La sequenza è terminata da una linea vuota.
    La funzione deve restituire un array di elementi di tipo exercise.
    Tale array sarà terminato da un elemento terminatore con campo name pari alla stringa vuota, e
    campo exercised_muscles interamente posto a 0.
    Tutti gli altri elementi conterranno gli esercizi letti da terminale, con campo name pari al nome
    dell'esercizio e campo exercised_muscles[i] pari a 1 (vero) se il gruppo muscolare i è
    compreso nella lista di muscoli esercitati, e 0 (falso) altrimenti.

(b) Progettare e implementare una funzione di prototipo:
        print_non_exercised_by_max(exercise *l);

    che riceva la struttura dati prodotta dalla funzione read_exercises e stampi la sequenza di
    gruppi muscolari non esercitata dall'esercizio che esercita il maggior numero di gruppi muscolari
    (assumendo che sia unico), con gli elementi ordinati in senso crescente, separati da spazi. La
    sequenza deve essere terminata dal carattere di fine linea '\n'.
*/

typedef enum
{
    NONE /*empty element*/,
    CALF,
    QUAD,
    FEM_BICEPS,
    HIP_FLEXORS,
    ABS,
    PECT,
    LAT,
    BACK,
    ERECTOR,
    TRAPS,
    BICEPS,
    TRICEPS,
    FOREARM,
    DELTS,
    STOP /* index of last element */
} muscle_groups;

typedef struct _exercise
{
    char name[128];
    int exercised_muscles[STOP];
} exercise;

int count_exercised(exercise *e)
{
    int count = 0;
    int i;
    for (i = 1; i < STOP; i++)
        count += e->exercised_muscles[i];
    return count;
}

int read_exercise(exercise *e)
{
    char s[168]; /*va bene qualunque numero abbastanza grande*/
    char *r = NULL;
    char *p = NULL;

    int read = 0;

    // Leggi una riga da stdin e salvala in s
    r = fgets(s, 168, stdin);

    memset(e, 0, sizeof(exercise)); /* azzera e */

    if (!r || r[0] == '\n')
        return 0; /* nessun elemento letto */

    // Leggi il nome dalla stringa
    sscanf(s, "%s", e->name);

    // Leggi i muscoli esercitati
    p = s + strlen(e->name);
    do
    {
        int x = NONE;
        read = sscanf(p, "%d", &x);

        do
        {
            p++;
        } while (*p >= '0' && *p <= '9');

        e->exercised_muscles[x] = 1;
    } while (read && *p != '\0');

    return 1; /* un elemento letto */
}

// Estende l'array e di count elementi aggiungendo toadd elementi
exercise *extend(exercise *e, int count, int toadd)
{
    int i;

    // Alloca un nuovo array di count + toadd elementi
    exercise *r = malloc(sizeof(exercise) * (count + toadd));

    memset(r, 0, sizeof(exercise) * (count + toadd)); /* inizializza a 0 */

    // Copia gli elementi di e in r
    for (i = 0; i < count; i++)
        r[i] = e[i];

    // Libera l'array e
    free(e);

    return r;
}

exercise *read_exercises()
{
    // Risultati
    exercise *r = malloc(sizeof(exercise) * 8);

    // inizializza tutto a 0
    memset(r, 0, sizeof(exercise) * 8);

    // Variabile temporanea per leggere l'esercizio
    exercise e;

    int count = 0;
    int read = 0;
    do
    {
        read = read_exercise(&e);
        // Se ho letto un esercizio, aggiungilo al risultato
        if (read)
        {
            r[count] = e;
            count++;
        }

        // Se ho letto 8 elementi, estendi l'array di altre 8 posizioni
        if (count != 0 && count % 8 == 0)
            r = extend(r, count, 8);

    } while (read);

    return r;
}

// Trova l'esercizio che esercita il maggior numero di muscoli
exercise *max_exercised(exercise *l)
{
    exercise *max = NULL;
    int nmax = -1;
    int i;

    for (i = 0; l[i].name[0] != '\0'; i++)
    {
        int x = count_exercised(l + i);
        if (x > nmax)
        {
            max = l + i;
            nmax = x;
        }
    }

    return max;
}

    // Stampa i muscoli non esercitati dall'esercizio che esercita il maggior numero di muscoli
void print_non_exercised_by_max(exercise *l)
{
    int i;

    exercise *max = max_exercised(l);

    for (i = 1; i < STOP; i++)
        if (!max->exercised_muscles[i])
            printf("%d ", i);

    printf("\n");
}