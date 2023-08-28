// Sottoprogramma che trova la cella di valore massimo tra le celle adiacenti
// alla cella corrente. Restituisce la differenza tra le coordinate della cella
// con il valore massimo e quelle della cella corrente.
// Il sottoprogramma restituisce i due valori anzidetti usando due parametri
// in uscita -- facenti uso del passaggio parametri per indirizzo.
void trovaMassimo(double M[][C], int rig, int col, int x, int y,
                  int *deltaX, int *deltaY)
{
    int massimo = M[x][y];
    *deltaX = 0;
    *deltaY = 0;

    // Itera celle adiacenti
    for (int i = -1; i <= +1; i++)
    {
        for (int j = -1; j <= +1; j++)
        {
            // Controlla validità cella adiacente
            if (!(x + i < 0 || x + i >= rig || y + j < 0 || y + j >= col))
            {
                if (massimo < M[x + i][y + j])
                {
                    // viene calcolato il percorso in
                    // salita piu' lungo che ad ogni
                    // passo e' anche il piu' ripido:
                    // Con due valori massimi viene scelto
                    // l'ultimo trovato
                    massimo = M[x + i][y + j];
                    *deltaX = i;
                    *deltaY = j;
                }
            }
        }
    }
}

int maximumPath(double M[][C], int rig, int col, int x, int y)
{
    if (rig <= 0 || rig > R || col <= 0 || col > C)
    {
        // sottomatrice rig × col non valida!
        return -1;
    }

    if (x < 0 || x >= rig || y < 0 || y >= col)
    {
        // coordinate cella iniziale non valide!
        return -1;
    }

    // il percorso ritornato e' inteso come num. di celle
    int dX, dY, numCelle = 1; 

    // Trova il percorso più lungo
    trovaMassimo(M, rig, col, x, y, &dX, &dY);
    while (!(dX == 0 && dY == 0))
    {
        x = x + dX;
        y = y + dY;
        numCelle += 1;
        trovaMassimo(M, rig, col, x, y, &dX, &dY);
    }

    return numCelle;
}