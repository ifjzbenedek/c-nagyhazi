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
    printf("Add meg a palya mereteit és a aknak szamat oszlop:sor:aknak formatumban!\n");
    while(scanf("%d:%d:%d", &palya.oszlopokSzama, &palya.sorokSzama, &aknakSzama) != 3)
    {
        printf("Probalja ujra, nem megfelelo a formatum!");
    }
    palya.tabla = (Cella**) malloc(palya.sorokSzama * sizeof(Cella*));
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        Cella* sor;
        sor = (Cella*) malloc(palya.oszlopokSzama * sizeof(Cella));
        palya.tabla[i] = sor;
    }
    //Lepes(palya);
    TablatFeltolt(palya);
    printf("Siker!");
    Kezdes(palya, aknakSzama);
    printf("Feltoltve!\n");
    Kirajzol(palya);
    bool nyertE = false;
    bool vesztettE = false;

    while(!nyertE && !vesztettE)
    {
        if(Lepes(palya))
        {
            printf("Sajnos aknára léptél és vesztettél!\n");
            vesztettE = true;
            Kirajzol(palya);
        }
        else if(NyertE(palya))
        {
            printf("Gratulálunk, nyertél!\n");
            nyertE = true;
            Kirajzol(palya);
        }


    }
}
