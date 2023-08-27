/*
Si considerino le seguenti definizioni di costanti e tipi di dato:

    #define MAX_RIGHE
    #define MAX_COLONNE
    30
    50
    typedef struct {
    int r;
    int c;
    } cella_t;

Esibire il prototipo e il codice di un sottoprogramma
    ...trova_ciclo(...)

che prenda come primo parametro un array bidimensionale in cui ogni cella sia di tipo cella_t, come
secondo parametro il numero di righe effettivo della matrice indicata dal primo argomento (dovrà essere un
valore <= MAX_RIGHE) e come terzo parametro il numero di colonne effettivo della matrice (dovrà essere
un valore <= MAX_COLONNE).
Il sottoprogramma deve acquisire da tastiera una coppia di coordinate della matrice (controllando che
siano valide) e restituire 1 se a partire dalla cella con le coordinate indicate è possibile seguire sulla matrice
un percorso ciclico, 0 altrimenti.
Nota: le coordinate nella prima cella individueranno una seconda cella, che a sua volta conterrà delle
coordinate. Le coordinate in quest’ultima individueranno una terza cella e così via.
Il sottoprogramma deve stabilire se procedendo in tal modo è possibile ritornare sulla cella di
partenza (restituendo 1) oppure no (restituendo 0).
*/

#define MAX_RIGHE 30
#define MAX_COLONNE 50

typedef struct {
    int r;
    int c;
} cella_t;

int trova_ciclo(cella_t mat[][MAX_COLONNE], int nr, int nc)
{
    // Controlla che i parametri siano validi
    if (nr <= 0 || nr > MAX_RIGHE || nc <= 0 || nc > MAX_COLONNE)
        return 0;

    int cond, x, y;
    do
    {
        printf("\n Inserisci coordinate x, y di una cella della matrice\n");
        printf("\n 0 <= x < %d, 0 <= y < %d", nr, nc);
        printf("\n x = ");
        scanf("%d", &x);
        printf("\n y = ");
        scanf("%d", &y);

        // Controlla che le coordinate siano valide
        cond = ((x >= 0 && x < nr) && (y >= 0 && y < nc));
    } while (cond == 0);

    // var. booleana per indicare se il ciclo è stato
    // individuato (== 1) o meno (== 0).
    int trovato = 0;

    // contatore del numero di celle
    // visitate sulla matrice (non può essere > nr*nc)
    int cont = 0;

    int currX = x, currY = y;

    while (cont < nr * nc && trovato == 0)
    {
        // Nuove coordinate
        nextX = mat[currX][currY].r;
        nextY = mat[currX][currY].c;

        // Controlla che le nuove coordinate siano valide
        if (!(nextX >= 0 && nextX < nr && nextY >= 0 && nextY < nc))
            return 0;

        cont += 1;
        trovato = (nextX == x && nextY == y);
        currX = nextX;
        curry = nextY;
    }

    if (trovato == 1)
        return 1;
    return 0;
}