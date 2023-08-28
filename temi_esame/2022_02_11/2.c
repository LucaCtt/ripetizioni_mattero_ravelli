#include <stdio.h>
#include <string.h>

#define MAXLUNG (50)

float somiglianza(char prima[], char seconda[]);

int main()
{
    char p[MAXLUNG + 1] = {'\0'}, s[MAXLUNG + 1] = {'\0'};
    printf("\n Inserisci la 1ma stringa:");
    scanf("%f", p);
    printf("\n Inserisci la 2da stringa:");
    scanf("%f", s);
    printf("\n Somiglianza = %.2f", somiglianza(p, s));

    return 0;
}

float somiglianza(char prima[], char seconda[])
{
    float S = 0.0;
    // cont = contatore di triplette identiche
    int n1 = strlen(prima), n2 = strlen(seconda), cont = 0;

    // Controllo che le stringhe siano lunghe almeno 3 caratteri
    if (n1 < 3 || n2 < 3)
        return S;

    // Confronta le stringhe a blocchi di 3 caratteri
    for (int i = 2; i < n1; i++)
    {
        for (int j = 2; j < n2; j++)
        {
            if (prima[i] == seconda[j] && prima[i - 1] == seconda[j - 1] && prima[i - 2] == seconda[j - 2])
                cont += 1;
        }
    }

    // Calcola la somiglianza
    S = (2 * (float)cont) / (n1 + n2 - 4);
    return S;
}