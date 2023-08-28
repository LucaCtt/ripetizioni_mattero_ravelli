#define L 50

void stampaRotazione(char mat[][L], int n, int numRotazioni)
{
    if (n < 0 || n > L)
        return;

    // Ruotare 4 volte vuol dire non ruotare.
    // Allo stesso modo ruotare 5 volte (per esempio) equivale a
    // ruotare una volta.
    numRotazioni = numRotazioni % 4;

    // Ruotare -1 volte equivale a ruotare 3 volte
    if (numRotazioni < 0)
        numRotazioni += 4;
    // da questo punto in poi numRotazioni e' sicuramente in { 0, +1, +2, +3}

    switch (numRotazioni)
    {
    case 0:
    {
        // 0 => non ruoto
        for (int i = 0; i < n; i++)
        {
            // rig
            for (int j = 0; j < n; j++)
            { // col
                printf("%c ", mat[i][j]);
            }
            printf("\n");
        }
    }
    break;
    case 1:
    {
        for (int j = 0; j < n; j++)
        {
            // rig
            for (int i = n - 1; i >= 0; i--)
            { // col
                printf("%c ", mat[i][j]);
            }
            printf("\n");
        }
    }
    break;
    case 2:
    {
        for (int i = n - 1; i >= 0; i--)
        {
            // rig
            for (int j = n - 1; j >= 0; j--)
            { // col
                printf("%c ", mat[i][j]);
            }
            printf("\n");
        }
    }
    break;
    default:
    { // case 3
        for (int j = n - 1; j >= 0; j--)
        { // col
            for (int i = 0; i < n; i++)
            { // rig
                printf("%c ", mat[i][j]);
            }
            printf("\n");
        }
    }
    break;
    } // end switch
}