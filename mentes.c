/*#include <stdio.h>
#include <stdlib.h>
#include "jatekallas.h"

void Ment(Palya palya, int oszlopokSzama, int sorokSzama)
{
    FILE *fp;

    fp = fopen("mentettallas.txt", "w");

    if(fp == NULL)
    {
        perror("A fájlba nem lehet menteni!");
        return;
    }

    fprintf(fp,"%d %d\n", oszlopokSzama, sorokSzama);
    for(int i = 0, i < sorokSzama, ++i)
    {
        for(int j = 0; j < oszlopokSzama; ++j)
        {
            if(palya.tabla[i][j].aknaE)
                fprintf(fp, "A ");
            else
                 fprintf(fp, "N ");

            if(palya.tabla[i][j].all == feloldatlan)
                fprintf(fp, "N");
            else if(palya.tabla[i][j].all == feloldva)
                fprintf(fp, "I");
            else
                fprintf(fp, "Z");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}
void Beolvas()
{
    FILE *fp;
    fp = fopen("mentettallas.txt", "w");

    if(fp == NULL)
    {
        perror("A mentett játék nem betölthető!");
    }

    if(fscanf(fp, "%d %d\n") == 2)
    {

    }
}
*/
