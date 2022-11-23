#include <stdio.h>
#include <stdlib.h>
#include "jatekallas.h"

void Kirajzol(Palya palya)
{
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        for(int j = 0; j < palya.oszlopokSzama; ++j)
        {
            if(palya.tabla[i][j].all == feloldatlan)
                printf("#");
            else if(palya.tabla[i][j].all == megjelolve)
                printf("Z");
            else
            {
                if(palya.tabla[i][j].all == feloldva && palya.tabla[i][j].aknaE)
                    printf("*");
                else
                {
                    int aknakKorulotte = SzomszedosAknaszam(palya, i, j);
                    printf("%d", aknakKorulotte);
                }
            }
        }
        printf("%c", 'A' + i);
        printf("\n");
    }
    for(int i = 0; i < palya.oszlopokSzama; i++)
    {
        printf("%c", 'a'+i);
    }
    printf("\n");
}
void LepestBeker(int* plepesSorSzam, int* plepesOszlopSzam, char* plepesTipus)
{
    printf("Várom a következõ lépését típus:sor:oszlop formátumban!\n");
    char lepesSor, lepesOszlop, lepesTipus;
    scanf("\n%c:%c:%c", &lepesTipus, &lepesSor, &lepesOszlop);
    *plepesTipus = lepesTipus;
    *plepesSorSzam = lepesSor - 'A';
    *plepesOszlopSzam = lepesOszlop - 'a';
}
void LepesTipusokatKiir()
{
    printf("Lehetséges lépések: \n   -F : felfed egy mezőt\n   -M : megjelöl egy mezőt zászlóval\n");
}
