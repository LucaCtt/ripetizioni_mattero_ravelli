/*
Si consideri la simulazione del movimento di un gatto su una mappa rappresentata come una matrice
quadrata con lato di lunghezza N celle. Ogni cella della matrice contiene un numero non negativo e
codificato in virgola mobile per indicare la quota (distanza dal suolo) del quadratino che le corrisponde
sulla mappa. Date le coordinate della posizione attuale del gatto sulla matrice, quest'ultimo si sposta
in una cella adiacente, solo se questa memorizza un valore di quota che è il massimo tra quella attuale
e quelle memorizzate in ciascuna delle posizioni adiacenti;
    • se tutti i quadratini adiacenti alla posizione attuale memorizzano una quota inferiore o uguale
      a quella attuale, il gatto si ferma;
    • se in più di una delle celle adiacenti alla posizione attuale è memorizzato il valore di quota
      massimo, il gatto può muoversi su una qualunque di esse.

(a) Si scriva un sottoprogramma C, ...massimoAdiacenti(...) che abbia come parametri
una matrice quadrata di lato N e le coordinate di una cella della matrice, e che restituisca le
coordinate della cella contenete il valore massimo tra quelli memorizzati nella cella passata
come parametro e nelle celle adiacenti. [4 punti]

(b) Si scriva un sottoprogramma C, ...Spostamento(...) che abbia come parametri una matrice
quadrata di lato N e le coordinate della posizione iniziale del gatto, e che restituisca le coordinate della
posizione sulla mappa dalla quale il gatto non riesce più a spostarsi, oppure le coordinate (-1,-1) per
indicare che la posizione iniziale non è valida. [4 punti]
*/

#define N 10
typedef struct coordinate
{
    int r;
    int c;
} coord;

int controllo(int r, int c)
{
    if (r < 0 || r > N || c < 0 || c > N)
        return 0; // coordinate non valide

    return 1; // coordinate valide
}

coord massimoAdiacenti(double mappa[][N], coord in)
{
    // Coordinate adiacente massimo, inizializzate a -1 per indicare errore
    coord ret = {-1, -1};

    if (controllo(in.r, in.c) == 0)
        return ret;

    // Valore massimo
    double massimo = mappa[in.r][in.c];
    int dx, dy, rmax, cmax;

    // Spostamento orizzontale relativo alla cella iniziale
    for (dx = -1; dx < 2; ++dx)
    {
        // Spostamento verticale relativo alla cella iniziale
        for (dy = -1; dy < 2; ++dy)
        {
            // Se controllo ok e valore superiore al massimo, aggiorno
            if (controllo(in.r + dx, in.c + dy) == 1 &&
                massimo < mappa[in.r + dx][in.c + dy])
            {
                massimo = mappa[in.r + dx][in.c + dy];
                rmax = in.r + dx;
                cmax = in.c + dy;
            }
        }
    }

    ret.r = rmax;
    ret.c = cmax;
    return ret;
}

coord Spostamento(double mappa[][N], coord in)
{
    coord ret = {-1, -1};

    if (controllo(in.r, in.c) == 0)
        return ret;

    // Coordinata attuale
    coord co = in;
    // Coordinata massimo
    coord coordMax;

    // Flag per indicare se ho trovato un massimo diverso dalla cella corrente
    int avanti = 1;
    do
    {
        // Trova la cella massima
        coordMax = massimoAdiacenti(mappa, co);
        // Se il massimo è ancora la cella corrente, non sono andato avanti. Mi fermo.
        if (coordMax.r == co.r && coordMax.c == co.c)
            avanti = 0;
        else
            co = coordMax;
    } while (avanti == 1);

    return co;
}