#include <stdio.h>
#include <stdlib.h>
#include "jatekallas.h"
#include <string.h>

#pragma warning( disable : 4996 )

void Kirajzol(Palya palya)
{
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        for(int j = 0; j < palya.oszlopokSzama; ++j)
        {
            if(palya.tabla[i][j].all == feloldatlan)
                printf("# ");
            else if(palya.tabla[i][j].all == megjelolve)
                printf("Z ");
            else
            {
                if(palya.tabla[i][j].all == feloldva && palya.tabla[i][j].aknaE)
                    printf("* ");
                else
                {
                    int aknakKorulotte = SzomszedosAknaszam(palya, i, j);
                    printf("%d ", aknakKorulotte);
                }
            }
        }
        printf("%c ", 'A' + i);
        printf("\n");
    }
    for(int i = 0; i < palya.oszlopokSzama; i++)
    {
        printf("%c ", 'a'+i);
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
            else if(*paknakSzama < 3)
            {
                printf("Túl kevés akna! (min 3)\n");
                sikeres = false;
            }
        }


    }


}

void LepestBeker(int* plepesSorSzam, int* plepesOszlopSzam, char* plepesTipus, int sorokSzama, int oszlopokSzama)
{
    printf("Várom a következõ lépését típus:sor:oszlop formátumban!\n");
    char lepesSor, lepesOszlop, lepesTipus;
    bool sikeres = false;
    while (!sikeres)
    {
        sikeres = true;
        if (scanf("\n%c:%c:%c", &lepesTipus, &lepesSor, &lepesOszlop) != 3)
        {
            printf("Nem megfelelő a formátum, próbálja újra!\n");
            scanf("%*[^\n]");
            sikeres = false;
        }
        else
        {
            if (lepesSor - 'A' < 0 || lepesSor - 'A' >= sorokSzama)
            {
                printf("Nem létezik ilyen sor! Próbálja újra!\n");
                sikeres = false;
            }
            else if (lepesOszlop - 'a' < 0 || lepesOszlop - 'a' >= oszlopokSzama)
            {
                printf("Nem létezik ilyen oszlop! Próbálja újra!\n");
                sikeres = false;
            }
            else if (lepesTipus != 'F' && lepesTipus != 'M')
            {
                printf("Nem létezik ilyen funkció! Próbálja újra!\n");
                sikeres = false;
            }
        }
    }
    
    *plepesTipus = lepesTipus;
    *plepesSorSzam = lepesSor - 'A';
    *plepesOszlopSzam = lepesOszlop - 'a';
}

void LepesTipusokatKiir()
{
    printf("Lehetséges lépések: \n   -F : felfed egy mezőt\n   -M : megjelöl egy mezőt zászlóval\n");
}

void MenuKirajzol()
{
    printf("Új játék vagy régi játék betöltése. Új játék esetén írd be, hogy “uj”, mentett játék esetén pedig, hogy “regi”:\n");
}

char* JatekKivalasztas()
{
    // TODO Ékezetet olvasson!
    char* regi = "regi";
    char valasztas[100];
    bool sikeres = false;
    while(!sikeres)
    {
        sikeres = true;
        if(scanf("%s", valasztas) != 1)
        {
            printf("Próbálja újra, nem megfelelő a formátum!\n");
            sikeres = false;
            scanf("%*[^\n]");
        }
        else if(strcmp("uj", valasztas) != 0 && strcmp("regi", valasztas) != 0)
        {
            printf("Kérem ˝regi˝ vagy ˝uj˝ közül válasszon!\n");
            sikeres = false;
            scanf("%*[^\n]");
        }

    }
    return valasztas;
}

void GyozelmetKiir()
{
    printf("Gratulálunk, győzött! Az ideje: \n");
    
}

void VeresegetKiir()
{
    printf("Aknára léptett, sajnos vesztett. Új játék kezdéséhez nyomjon meg egy billentyűt!\n");
}
