/*
Si desidera analizzare la statistica dei consumi di toner di un’azienda per ottimizzare gli acquisti futuri,
facendo uso delle costanti e del tipo di dato di seguito specificati.

    #define MAX_STR 30
    #define MAX_NUMERO 6

    typedef struct {
        char nomeDip[MAX_STR+1];
        int occorrenze[MAX_NUMERO];
    } stat;

La quantità di cartucce di toner prelevate dal magazzino è riportata all’interno di un file di testo.
Il file contiene una riga per ogni ordine fatto da ciascun dipartimento. Ogni riga contiene in sequenza:
    • il nome del dipartimento che ha prelevato il/i toner (una stringa lunga MAX_STR caratteri);
    • un numero intero (valore minimo 1 e massimo MAX_NUMERO) che indica la quantità di cartucce
      di toner prelevate da quel dipartimento.

Non è noto il numero di righe presenti nel file.

Esempio di formato del file:
ACQUISTI 1
VENDITE 2
ACQUISTI 1
ACQUISTI 5

(a) Si esibisca il codice del sottoprogramma

    void riempi_vett(char nomefile[], stat vett[], int lungVett)

che richiede come primo parametro il nome del file di testo contenete le informazioni sugli ordini
delle cartucce di toner, come secondo parametro un array le cui celle sono di tipo stat e come terzo
parametro la lunghezza dell’array stesso.
Il sottoprogramma assume che una stringa nell’attributo nomeDip in ciascuna cella dell’array
vett[] sia già presente e che sia diversa da quelle nelle altre celle, inoltre il valore di tutti gli interi
nell’attributo occorrenze di ogni cella è assunto essere inizializzato a 0.
Il sottoprogramma modifica l’attributo occorrenze di ciascuna cella, memorizzando in
occorrenze[0] quante righe del file contengono 1 come quantità di toner richiesta dal
dipartimento indicato nell’attributo nomeDip, in occorrenze[1] quante righe del file contengono
2 come quantità di toner richiesta dal dipartimento indicato nell’attributo nomeDip e cosı̀ via.

(b) Si esibisca il codice del sottoprogramma

    void toner_statistic(stat vett[], int lungVett)

Il sottoprogramma assume come primo parametro un vettore di statistiche creato dal
sottoprogramma al punto (a) . Esso crea un nuovo file chiamato "statistic.txt" con tante
righe quante sono le celle dell’array vett e, su ogni rigo, riporta: il nome del dipartimento, la
minima, la massima e la media quantità di toner che è stata richiesta negli ordini emessi dal
dipartimento, il valore della quantità di toner richiesta più spesso (la moda) dal dipartimento e il
numero di volte che tale valore si è ripetuto - in caso ci sia più di un valore moda, è sufficiente
riportarne solo uno.
Se un dipartimento non ha effettuato ordini di toner, il sottoprogramma riporterà sul rigo del file:
"Il Dip. non ha ordinato toner!"

Esempio: se l’array vett avesse lunghezza 2 e contenesse i seguenti dati
nella cella[0]: {"ACQUISTI", { 2, 1, 0, 0, 1, 0 } }
nella cella[1]: {"VENDITE", { 0, 1, 0, 0, 0, 0 } }
Il file "statistic.txt" creato dal sottoprogramma sarebbe:
ACQUISTI 1, 5, 2.25, (1, 2)
VENDITE 2, 2, 2.00, (2, 1)

*/

// Lunghezza max stringhe, senza contare il terminatore
#define MAX_STR 30
#define MAX_NUMERO 6

typedef struct
{
    char nomeDip[MAX_STR + 1];
    int occorrenze[MAX_NUMERO];
} stat;

void riempi_array(char nomefile[], stat vett[], int lungVett)
{
    FILE *fpr = fopen(nomefile, "r");
    if (fpr == NULL)
    {
        fprintf(stderr, "\n Errore in apertura del file %s", nomefile);
        exit(-1);
    }

    char nomeDip[MAX_STR + 1];
    int qta;

    // Controlla che non si sia raggiunta la fine del file
    while (feof(fpr) == 0)
    {
        // Legga una riga del file
        fscanf(fpr, "%s %d", nomeDip, &qta);

        // Trova il dipartimento nel vettore
        // e incremente l'occorrenza corrispondente
        for (int i = 0; i < lungVett; i++)
        {
            char *dipart = vett[i].nomeDip;

            // Se il dipartimento è presente nel vettore, incrementa l'occorrenza
            if (strcmp(nomeDip, dipart) == 0)
                vett[i].occorrenze[qta - 1] += 1;
        }
    }

    fclose(fpr);
}

void toner_statistic(stat vett[], int lungVett)
{
    // Apri file in scrittura
    FILE *fpw = fopen(nomefile, "w");
    if (fpw == NULL)
    {
        fprintf(stderr, "\n Errore in creazione del file %s", "statistics.txt");
        exit(-1);
    }

    // Itera ogni dipartimento,
    // creando quindi tante righe quante sono le celle dell'array vett
    for (int i = 0; i < lungVett; i++)
    {
        int min = 0, max, modaVal = -1, maxOccorrenze = 0, cont = 0;
        float media;

        // Trova qta min, max, media e moda
        for (int j = 0; j < MAX_NUMERO; j++)
        {
            if (min == 0 && vett[i].occorrenze[j] > 0)
                min = j + 1;

            if (vett[i].occorrenze[j] != 0)
                max = j + 1;

            media += vett[i].occorrenze[j] * (j + 1);
            cont + = vett[i].occorrenze[j];

            if (maxOccorrenze < vett[i].occorrenze[j])
            {
                maxOccorrenze = vett[i].occorrenze[j];
                modaVal = j + 1;
            }
        }

        if (cont != 0)
            fprintf(fpw, "%s %d %d %f (%d, %d)\n", vett[i].nomeDip,
                    min, max, media / cont, modaVal, MaxOccorrenze);
        else
            fprintf(fpw, "Il Dip. %s non ha ordinato toner!\n", vett[i].nomeDip);
    }

    fclose(fpw);
    return;
}