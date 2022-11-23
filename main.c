#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jatekallas.h"
#include "megjelenites.h"

int main()
{
    srand(time(0));
    int sorokSzama, oszlopokSzama, aknakSzama;
    PalyaParamaterketEsAknaSzamotBeker(&sorokSzama, &oszlopokSzama, &aknakSzama);
    Palya palya = PalyatLetrehoz(sorokSzama, oszlopokSzama);
    TablatFeltolt(palya);
    AknaElhelyez(palya, aknakSzama);
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
