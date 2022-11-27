#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "c-econio/econio.h"
#include "palya.h"
#include "debugmalloc.h"

void KepernyoTorolEsKezdesbeMozog()
{
    econio_clrscr();
    econio_gotoxy(0, 0);
}

void Kirajzol(Palya* palya)
{
    KepernyoTorolEsKezdesbeMozog();
    for(int i = 0; i < palya->sorokSzama; ++i)
    {
        for(int j = 0; j < palya->oszlopokSzama; ++j)
        {
            if(palya->tabla[i][j].all == feloldatlan)
                printf("# ");
            else if (palya->tabla[i][j].all == megjelolve)
            {
                econio_textcolor(COL_RED);
                printf("Z ");
                econio_textcolor(COL_WHITE);
            }
            else
            {
                if(palya->tabla[i][j].all == feloldva && palya->tabla[i][j].aknaE)
                { 
                    if (palya->robbanoX == i && palya->robbanoY == j)
                    {
                        econio_textcolor(COL_RED);
                        printf("* ");
                        econio_textcolor(COL_WHITE);
                    }
                    else
                        printf("* ");
                }
                    
                else
                {
                    int aknakKorulotte = SzomszedosAknaszam(palya, i, j);
                    if (aknakKorulotte == 0)
                        printf("  ");
                    else
                        printf("%d ", aknakKorulotte);
                       
                }
            }
        }
        printf("%c ", 'A' + i);
        printf("\n");
    }
    for(int i = 0; i < palya->oszlopokSzama; i++)
    {
        printf("%c ", 'a'+i);
    }
    printf("\n\n");
}

void PalyaParamaterketEsAknaSzamotBekerEsBeallit(Palya* palya)
{
    int oszlopokSzama, sorokSzama, aknakSzama;
    printf("Add meg a pálya méreteit és az aknák számát oszlop:sor:aknák formátumban!\n");
    bool sikeres = false;
    while(!sikeres)
    {
        sikeres = true;
        if(scanf("%d:%d:%d", &oszlopokSzama, &sorokSzama, &aknakSzama) != 3)
        {
            printf("Próbálja újra, nem megfelelő a formátum!\n");
            sikeres = false;
            scanf("%*[^\n]");
        }
        else
        {
            if(oszlopokSzama < 3)
            {
                printf("Túl kevés oszlop! (min3)\n");
                sikeres = false;
            }
            else if(oszlopokSzama > 20)
            {
                printf("Túl sok oszlop! (max20)\n");
                sikeres = false;
            }

            if(sorokSzama < 3)
            {
                printf("Túl kevés sor! (min3)\n");
                sikeres = false;
            }
            else if(sorokSzama > 20)
            {
                printf("Túl sok sor! (max20)\n");
                sikeres = false;
            }

            if(aknakSzama > (sorokSzama * oszlopokSzama / 2))
            {
                printf("Túl sok akna! (max sorok*oszlopok/2 méretű lehet)\n");
                sikeres = false;
            }
            else if(aknakSzama < 3)
            {
                printf("Túl kevés akna! (min 3)\n");
                sikeres = false;
            }
        }
    }
    palya->sorokSzama = sorokSzama;
    palya->oszlopokSzama = oszlopokSzama;
    palya->aknakSzama = aknakSzama;

}

void LepestBeker(int* plepesSorSzam, int* plepesOszlopSzam, char* plepesTipus, Palya* palya)
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
            if (lepesSor - 'A' < 0 || lepesSor - 'A' >= palya->sorokSzama)
            {
                printf("Nem létezik ilyen sor! Próbálja újra!\n");
                sikeres = false;
            }
            else if (lepesOszlop - 'a' < 0 || lepesOszlop - 'a' >= palya->oszlopokSzama)
            {
                printf("Nem létezik ilyen oszlop! Próbálja újra!\n");
                sikeres = false;
            }
            else if (lepesTipus != 'F' && lepesTipus != 'M')
            {
                printf("Nem létezik ilyen funkció! Próbálja újra!\n");
                sikeres = false;
            }
            else if (lepesTipus == 'M' && palya->tabla[lepesSor - 'A'][lepesOszlop - 'a'].all == feloldva)
            {
                printf("Ez már fel van oldva! Csináljon mást!\n");
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

bool JatekKivalasztas_UjE()
{
    // TODO Ékezetet olvasson!
    char* regi = "regi";
    char valasztas[100];
    while(true)
    {
        if(scanf("%s", valasztas) != 1)
            printf("Próbálja újra, nem megfelelő a formátum!\n");
        else if(strcmp("uj", valasztas) == 0)
            return true;
        else if (strcmp("regi", valasztas) == 0)
            return false;

        scanf("%*[^\n]");
    }
}

void GyozelmetKiir(int kezdIdo)
{
    int perc, mp;
    IdotSzamolPercben(&perc, &mp, kezdIdo);
    printf("Gratulálunk, nyert! Az ideje: %d perc %d másodperc\n", perc, mp);
}

void VeresegetKiir()
{
    printf("Aknára léptett, sajnos vesztett.\n");
}

void UjrainditasKiir()
{
    printf("Nyomjon meg egy billentyűt az újraindításhoz!\n");
    getch();
    KepernyoTorolEsKezdesbeMozog();
}

void IdoLetelt()
{
    printf("Sajnos kifutott az időből és vesztett.\n");
}

void IdoKorlatotKiir(int idoKorlat)
{
    printf("A rendelkezésre álló idő a játék kezdetétől: %d perc\n", idoKorlat);
}

