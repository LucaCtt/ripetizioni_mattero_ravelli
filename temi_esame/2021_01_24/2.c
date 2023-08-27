typedef struct
{
    char nomeRuota[10 + 1];
    int numeri[5];
} ruota_t;

int conteggioAssenti(ruota_t vett[11])
{
    int cont = 0;

    // Itera tutti i numeri da 1 a 90
    for (int num = 1; num <= 90; num++)
    {
        // Flag per indicare se è stato trovato il numero
        flag = 1;

        // Itera tutte le ruote
        for (r = 0; (r < 11) && (flag == 1); r++)
        {
            for (int j = 0; (j < 5) && (flag == 1); j++)
                // Se il numero è presente in una ruota, setta il flag a 0
                if (num == vett[r].numeri[j])
                    flag = 0;
        }

        // Se il flag è ancora 1, il numero non è stato trovato in nessuna ruota
        if (flag == 1)
            cont += 1;
    }

    return cont;
}