#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jatekallas.h"
#include <time.h>

#pragma warning( disable : 4996 )

bool LetezikEMentes()
{
    FILE *fp;
    if ((fp = fopen("mentettallas.txt", "r")))
    {
        fclose(fp);
        return true;
    }
    return false;
}
void Ment(Palya palya, int oszlopokSzama, int sorokSzama, time_t kezdesIdo)
{
    FILE *fp;
    time_t aktIdo;
    fp = fopen("mentettallas.txt", "w");

    if(fp == NULL)
    {
        perror("A fájlba nem lehet menteni!");
        return;
    }

    fprintf(fp,"%d %d %d\n", oszlopokSzama, sorokSzama, time(&aktIdo) - kezdesIdo);
    for(int i = 0; i < sorokSzama; ++i)
    {
        for(int j = 0; j < oszlopokSzama; ++j)
        {
            if(palya.tabla[i][j].aknaE)
                fprintf(fp, "A ");
            else
                 fprintf(fp, "N ");

            if(palya.tabla[i][j].all == feloldatlan)
                fprintf(fp, "N ");
            else if(palya.tabla[i][j].all == feloldva)
                fprintf(fp, "I ");
            else
                fprintf(fp, "Z ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

Cella Beallit(char aknaE, char allapot)
{
    Cella cella;
    if(aknaE == 'A')
        cella.aknaE = true;
    else
        cella.aknaE = false;

    if(allapot == 'Z')
        cella.all = megjelolve;
    else if(allapot == 'I')
        cella.all = feloldva;
    else
        cella.all = feloldatlan;

    return cella;
}

Palya Beolvas(int* psorokSzama, int* poszlopokSzama, int* pelteltIdo)
{
    FILE *fp;
    fp = fopen("mentettallas.txt", "r");

    if(fp == NULL)
    {
        perror("A mentett játék nem betölthető!");
    }
    Palya palya;
    if(fscanf(fp, "%d %d %d\n", poszlopokSzama, psorokSzama, pelteltIdo) == 3)
    {
        palya = PalyatLetrehoz(*psorokSzama, *poszlopokSzama);
    }
    char aknaE;
    char allapot;
    for(int i = 0; i < *psorokSzama; ++i)
    {
        for(int j = 0; j < *poszlopokSzama; ++j)
        {
            fscanf(fp, "%c %c ", &aknaE, &allapot);
            palya.tabla[i][j] = Beallit(aknaE, allapot);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
    return palya;
}

void MentestTorol()
{
    remove("mentettallas.txt");

}
