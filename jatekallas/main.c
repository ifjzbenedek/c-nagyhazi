#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jatekallas.h"
#include "megjelenites.h"

int main()
{
    srand(time(0));
    int aknakSzama;
    Palya palya;
    printf("Add meg a pálya méreteit és az aknák számát oszlop:sor:aknák formátumban!\n");
    while(scanf("%d:%d:%d", &palya.oszlopokSzama, &palya.sorokSzama, &aknakSzama) != 3)
    {
        printf("Próbálja újra, nem megfelelő a formátum!\n");
    }
    palya.tabla = (Cella**) malloc(palya.sorokSzama * sizeof(Cella*));
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        Cella* sor;
        sor = (Cella*) malloc(palya.oszlopokSzama * sizeof(Cella));
        palya.tabla[i] = sor;
    }
    TablatFeltolt(palya);
    Kezdes(palya, aknakSzama);
    Kirajzol(palya);
    bool nyertE = false;
    bool vesztettE = false;
    LepesTipusokatKiir();
    while(!nyertE && !vesztettE)
    {
        if(Lepes(palya))
        {
            printf("Sajnos aknára léptél és vesztettél!\n");
            vesztettE = true;
        }
        else if(NyertE(palya))
        {
            printf("Gratulálunk, nyertél!\n");
            nyertE = true;
        }
        Kirajzol(palya);

    }

}
