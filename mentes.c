#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "palya.h"
#include "debugmalloc.h"


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
void Ment(Palya* palya, time_t kezdesIdo)
{
    FILE *fp;
    time_t aktIdo;
    fp = fopen("mentettallas.txt", "w");

    if(fp == NULL)
    {
        perror("A fájlba nem lehet menteni!");
        return;
    }

    fprintf(fp,"%d %d %d\n", palya->oszlopokSzama, palya->sorokSzama, (int)(time(&aktIdo) - kezdesIdo));
    for(int i = 0; i < palya->sorokSzama; ++i)
    {
        for(int j = 0; j < palya->oszlopokSzama; ++j)
        {
            if(palya->tabla[i][j].aknaE)
                fprintf(fp, "A ");
            else
                 fprintf(fp, "N ");

            if(palya->tabla[i][j].all == feloldatlan)
                fprintf(fp, "N ");
            else if(palya->tabla[i][j].all == feloldva)
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

void Beolvas(Palya* palya, int* pelteltIdo)
{
    FILE *fp;
    fp = fopen("mentettallas.txt", "r");

    if(fp == NULL)
    {
        perror("A mentett játék nem betölthető!");
    }

    if(fscanf(fp, "%d %d %d\n", palya->oszlopokSzama, palya->sorokSzama, pelteltIdo) == 3)
    {
        PalyaCellakatLetrehoz(palya);
    }
    char aknaE;
    char allapot;
    for(int i = 0; i < palya->sorokSzama; ++i)
    {
        for(int j = 0; j < palya->oszlopokSzama; ++j)
        {
            fscanf(fp, "%c %c ", &aknaE, &allapot);
            palya->tabla[i][j] = Beallit(aknaE, allapot);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
}

void MentestTorol()
{
    remove("mentettallas.txt");

}
