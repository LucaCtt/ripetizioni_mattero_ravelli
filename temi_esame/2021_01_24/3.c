ruota_t *ruotePesanti(int soglia, ruota_t vett[11], int *lung)
{
    int supera[11] = {0}, cont = 0;
    /*
    l’array supera[…] viene usato di seguito come array di valori 0 o 1:
    se una sua cella conterra’ 0 allora si sara’ verificato che la cella
    di vett[….] con lo stesso indice ha somma degli estratti che NON
    supera la soglia.
    Se una sua cella conterra’ 1 allora si sara’ verificato che la cella
    di vett[….] con lo stesso indice ha somma degli estratti che supera
    la soglia.
    La variabile cont, conteggia il num. di celle non nulle in supera[…]
    */

    // Itera tutte le ruote
    for (int i = 0; i < 11; i++)
    {
        int sum = 0;

        // Somma i numeri di ogni ruota
        for (int j = 0; j < 5; j++)
        {
            sum += vett[i].numeri[j];
        }

        if (sum > soglia)
        {
            supera[i] = 1;
            cont++;
        }
    }

    *lung = cont; // valore di ritorno passato per indirizzo

    // Se non ci sono ruote pesanti, ritorna NULL
    if (cont == 0)
        return NULL;

    // Altrimenti crea un array di t_ruota di dimensione cont
    t_ruota *ret = (t_ruota *)malloc(cont * sizeof(t_ruota));

    if (ret == NULL)
        return NULL;

    int k = 0;
    for (int i = 0; i < 11; i++)
    {
        if (supera[i] == 1)
        {
            ret[k] = vett[i];
            k++;
        }
    }

    return ret;
}