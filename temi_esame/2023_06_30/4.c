/*
Si progetti una funzione
    ...aggiornaMatrice(...)

che riceve in ingresso una matrice NxN contenente valori interi nell'insieme {0, 1}, e che modifica la matrice
in modo tale che ogni cella della matrice contenga, dopo l'esecuzione della funzione, 1 se il conteggio dei
valori non nulli nelle celle adiacenti (inclusa la cella corrente) è maggiore o uguale al conteggio dei valori nulli,
0 altrimenti.
*/

// Copia la matrice m in r
void copiaMatrice(int r[N][N], int m[N][N])
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            r[i][j] = m[i][j];
        }
    }
}

void aggiornaMatrice(int m[N][N])
{
    int r[N][N];
    int i, j, k, h;

    // Copia la matrice m in r,
    // così da poter leggere i valori originali da r
    // e scrivere i valori aggiornati in m
    copiaMatrice(r, m);

    // i = indice riga
    for (i = 0; i < N; i++)
    {
        // j = indice colonna
        for (j = 0; j < N; j++)
        {
            // somma = somma valori adiacenti
            // contaAdiacenti = numero di valori adiacenti
            int somma = 0, contaAdiacenti = 1;

            // k = indice riga adiacente, relativamente a i
            for (k = -1; k <= 1; k++)
            {
                // h = indice colonna adiacente, relativamente a j
                for (h = -1; h <= 1; h++)
                {
                    // Controlla che i+k e j+h siano indici validi:
                    // questi sono infatti gli indici della cella adiacente
                    // considerata in questa iterazione
                    if (i + k >= 0 && i + k < N && j + h >= 0 && j + h < N)
                    {
                        somma += m[i + k][j + h];
                        contaAdiacenti += 1;
                    }
                }
            }

            // Se la somma dei valori adiacenti è maggiore o uguale
            // al numero di valori adiacenti diviso 2, allora scrivi 1
            if (somma >= contaAdiacenti / 2)
                r[i][j] = 1;
            else
                r[i][j] = 0;
        }
    }

    // Copia la matrice aggiornata in m
    // per riportare il risultato
    copiaMatrice(m, r);
}