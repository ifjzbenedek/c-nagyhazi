#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jatekallas.h"
#include "megjelenites.h"

int Sorsol(int sorokSzama, int oszlopokSzama)/**/
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


void Kezdes(Palya palya, int aknakSzama)
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


int SzomszedosAknaszam(Palya palya, int sor, int oszlop) /**/
{
    int kornyezoAknaszam = 0;
    for(int i = sor - 1; i <= sor + 1; ++i)
    {
        for(int j = oszlop - 1; j <= oszlop + 1; ++j)
        {
            if(i <= palya.sorokSzama-1 & j <= palya.oszlopokSzama-1 & i >= 0 && j >= 0 && palya.tabla[i][j].aknaE && !(sor == i && oszlop == j))
            {
                kornyezoAknaszam++;
            }
        }
    }
    return kornyezoAknaszam;
}

void Tisztitas(int sor, int oszlop, Palya palya) /**/
{
    for(int i = sor - 1; i <= sor + 1; ++i)
    {
        for(int j = oszlop - 1; j <= oszlop + 1; ++j)
        {
            if(i <= palya.sorokSzama-1 & j <= palya.oszlopokSzama-1 & i >= 0 && j >= 0 & palya.tabla[i][j].all == feloldatlan)
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
            if(palya.tabla[i][j].aknaE && palya.tabla[i][j].all == feloldatlan)
                return false;
        }
    }
    return true;
}

bool RobbanE(Palya palya, int sor, int oszlop) /**/
{
    if(palya.tabla[sor][oszlop].aknaE)
    {
        return true;
    }

    return false;

}

bool Lepes(Palya palya)
{
    printf("Várom a következõ lépését típus:sor:oszlop formátumban!\n");
    char lepesSor, lepesOszlop, lepesTipus;
    int lepesSorSzam = 0;
    int lepesOszlopSzam = 0;
    scanf("\n%c:%c:%c", &lepesTipus, &lepesSor, &lepesOszlop);
    lepesSorSzam = lepesSor - 'A';
    lepesOszlopSzam = lepesOszlop - 'a';
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
        Kirajzol(palya);
        return RobbanE(palya, lepesSorSzam, lepesOszlopSzam);


    }
    else
    {
        printf("Nem helyes az oszlop/sor amit megadott!\n");
    }
    Kirajzol(palya);
    return false;
}
