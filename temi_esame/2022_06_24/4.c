#define MAX_CONTATTI 100
#define MAX_NOME 30
#define MAX_TEL 11

typedef struct
{
    char nome[MAX_NOME];
    char telefono[MAX_TEL];
} t_contatto;

char nome[MAX_NOME];

char telefono[MAX_TEL];

typedef struct
{
    t_contatto contatti[MAX_CONTATTI];
    int numero_contatti;
} t_rubrica;

// Restituisce 0 se tutto va a buon file, altrimenti restituisce -1.
int salvaSuFile(t_rubrica rub, char nomefile[])
{
    // Apri file in scrittura
    FILE *fp = fopen(nomefile, "w");
    if (fp == NULL)
        return -1;

    // Scrivi il numero di contatti
    fprintf(fp, "%d\n", rub.numero_contatti);

    // Scrivi tutti i contatti
    for (int i = 0; i < rub.numero_contatti; i++)
    {
        fprintf(fp, "%s %s\n", rub.contatti[i].nome, rub.contatti[i].telefono);
    }

    fclose(fp);
    return 0;
}

// Restituisce il numero di contatto con prefisso p, se tutto va a buon file;
// altrimenti restituisce -1.
int numPrefissi(char nomefile[], int p)
{
    if (!(p >= 100 && p <= 999))
        return -1;

    t_contatto contact;
    int totContatti = 0, num, count = 0;

    // Apri file in lettura
    FILE *fp = fopen(nomefile, "r");
    if (fp == NULL)
        return -1;

    // Leggi numero totale contatti
    fscanf(fp, "%d\n", &totContatti);

    // Leggi contatti
    for (int i = 0; i < totContatti; i++)
    {
        fscanf(fp, "%s %s\n", contact.nome, contact.telefono);

        // Controlla se il prefisso è uguale a p,
        // se sì, incrementa il contatore
        if (strlen(contact.telefono) >= 3)
        {
            num = (contact.telefono[2] - '0') + (contact.telefono[1] - '0') * 10 +
                  (contact.telefono[0] - '0') * 100;
            if (num == p)
                count += 1;
        }
    }

    fclose(fp);
    return count;
}