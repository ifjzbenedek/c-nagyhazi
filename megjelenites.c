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

void PalyaParamaterketEsAknaSzamotBeker(int* poszlopokSzama, int* psorokSzama, int* paknakSzama)
{
    printf("Add meg a pálya méreteit és az aknák számát oszlop:sor:aknák formátumban!\n");
    bool sikeres = false;
    while(!sikeres)
    {
        sikeres = true;
        if(scanf("%d:%d:%d", poszlopokSzama, psorokSzama, paknakSzama) != 3)
        {
            printf("Próbálja újra, nem megfelelő a formátum!\n");
            sikeres = false;
            scanf("%*[^\n]");
        }
        else
        {
            if(*poszlopokSzama < 3)
            {
                printf("Túl kevés oszlop! (min3)\n");
                sikeres = false;
            }
            else if(*poszlopokSzama > 20)
            {
                printf("Túl sok oszlop! (max20)\n");
                sikeres = false;
            }

            if(*psorokSzama < 3)
            {
                printf("Túl kevés sor! (min3)\n");
                sikeres = false;
            }
            else if(*psorokSzama > 20)
            {
                printf("Túl sok sor! (max20)\n");
                sikeres = false;
            }

            if(*paknakSzama > (*psorokSzama * *poszlopokSzama / 2))
            {
                printf("Túl sok akna! (max sorok*oszlopok/2 méretű lehet)\n");
                sikeres = false;
            }
            else if(*paknakSzama < 4)
            {
                printf("Túl kevés akna! (min 3)\n");
                sikeres = false;
            }
        }


    }


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
