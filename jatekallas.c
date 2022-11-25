#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jatekallas.h"
#include "megjelenites.h"

Palya PalyatLetrehoz (int sorokszama, int oszlopokszama)
{
    Palya palya;
    palya.sorokSzama = sorokszama;
    palya.oszlopokSzama = oszlopokszama;
    palya.tabla = (Cella**) malloc(palya.sorokSzama * sizeof(Cella*));
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        Cella* sor;
        sor = (Cella*) malloc(palya.oszlopokSzama * sizeof(Cella));
        palya.tabla[i] = sor;
    }
    return palya;
}
int Sorsol(int sorokSzama, int oszlopokSzama)
{
    return rand()%(sorokSzama*oszlopokSzama);
}


void TablatFeltolt(Palya palya)
{
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        for(int j = 0 ; j < palya.oszlopokSzama; ++j)
        {
            Cella ujCella;
            ujCella.aknaE = false;
            ujCella.all = feloldatlan;
            palya.tabla[i][j] = ujCella;
        }
    }
}


void AknaElhelyez(Palya palya, int aknakSzama)
{
    for(int i = 0; i < aknakSzama; ++i)
    {
        int sorsoltSzam = Sorsol(palya.sorokSzama, palya.oszlopokSzama);
        int sor = (sorsoltSzam / (palya.oszlopokSzama));
        int oszlop = sorsoltSzam - ((palya.oszlopokSzama) * (sor));
        if(palya.tabla[sor][oszlop].aknaE)
            i -= 1;
        else
            palya.tabla[sor][oszlop].aknaE = true;
    }
}


int SzomszedosAknaszam(Palya palya, int sor, int oszlop)
{
    int kornyezoAknaszam = 0;
    for(int i = sor - 1; i <= sor + 1; ++i)
    {
        for(int j = oszlop - 1; j <= oszlop + 1; ++j)
        {
            if(i <= palya.sorokSzama-1 && j <= palya.oszlopokSzama-1 && i >= 0 && j >= 0 && palya.tabla[i][j].aknaE && !(sor == i && oszlop == j))
            {
                kornyezoAknaszam++;
            }
        }
    }
    return kornyezoAknaszam;
}

void Tisztitas(int sor, int oszlop, Palya palya)
{
    for(int i = sor - 1; i <= sor + 1; ++i)
    {
        for(int j = oszlop - 1; j <= oszlop + 1; ++j)
        {
            if(i <= palya.sorokSzama-1 && j <= palya.oszlopokSzama-1 && i >= 0 && j >= 0 && palya.tabla[i][j].all == feloldatlan)
            {
                palya.tabla[i][j].all = feloldva;
                if(SzomszedosAknaszam(palya, i, j) == 0)
                    Tisztitas(i,j,palya);
            }

        }
    }
}

bool NyertE(Palya palya)
{
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        for(int j = 0; j < palya.oszlopokSzama; ++j)
        {
            if(palya.tabla[i][j].aknaE == false && (palya.tabla[i][j].all == feloldatlan || palya.tabla[i][j].all == megjelolve))
                return false;
        }
    }

    return true;
}

bool RobbanE(Palya palya, int sor, int oszlop)
{
    if(palya.tabla[sor][oszlop].aknaE)
    {
        return true;
    }

    return false;

}

bool Lepes(Palya palya)
{
    int lepesSorSzam, lepesOszlopSzam;
    char lepesTipus;
    LepestBeker(&lepesSorSzam, &lepesOszlopSzam, &lepesTipus, palya.sorokSzama, palya.oszlopokSzama);
    if(lepesTipus == 'M')
    {
        palya.tabla[lepesSorSzam][lepesOszlopSzam].all = megjelolve;
    }
    else if(lepesTipus == 'F')
    {
        palya.tabla[lepesSorSzam][lepesOszlopSzam].all = feloldva;
        if(SzomszedosAknaszam(palya, lepesSorSzam, lepesOszlopSzam) == 0)
        {
            Tisztitas(lepesSorSzam,lepesOszlopSzam,palya);
        }
        return RobbanE(palya, lepesSorSzam, lepesOszlopSzam);
    }
    else
    {
        printf("Nincs ilyen utasítás!");
        Lepes(palya);
    }
    return false;
}

void MindentFelold(Palya palya)
{
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        for(int j = 0 ; j < palya.oszlopokSzama; ++j)
        {
            palya.tabla[i][j].all = feloldva;
        }
    }
}
