typedef struct
{
    char codice[5 + 1];
    int quantita;
    float prezzo;
    char descrizione[300];
} pezzoMeccanico_t;

pezzoMeccanico_t *rimuoviDuplicati(pezzoMeccanico_t A[], int lungIN,
                                   int *lungOUT)
{
    // temp = array temporaneo di lunghezza lungIN che non contiene duplicati
    // res = come temp ma di lunghezza lungOUT
    pezzoMeccanico_t *temp, *res;

    temp = (pezzoMeccanico_t *)malloc(lungIN * sizeof(pezzoMeccanico_t));
    if (temp == NULL)
    {
        *lungOUT = 0;
        return NULL;
    }

    int k = 0, flag;
    for (int i = 0; i < lung; i++)
    {
        // Copia l'elemento i-esimo di A in temp alla posizione k
        temp[k] = A[i];
        flag = 0;
        
        // Controlla se l'elemento i-esimo di A è duplicato
        for (int j = i + 1; j < lung && flag == 0; j++)
        {
            // Se è duplicato, flag = 1
            if (strcmp(A[i].codice, A[j].codice) == 0)
                flag = 1;
        }

        // Se non è duplicato, incrementa k
        if (flag == 0)
        {
            k += 1; // se non ha duplicati che appaiono
            // successivamente in elenco non
            // sovrascriverò la cella k-esima
        }
    }

    // Adesso che ho la lunghezza di temp, alloco res con la dimensione giusta
    res = (pezzoMeccanico_t *)malloc(k * sizeof(pezzoMeccanico_t));
    if (res == NULL)
    {
        *lungOUT = 0;
        return NULL;
    }

    for (int i = 0; i < k; i++)
        res[i] = temp[i];

    *lungOUT = k;
    free(temp);
    return res;
}