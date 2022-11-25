#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jatekallas.h"
#include "megjelenites.h"
#include "mentes.h"

int main()
{
    srand(time(0));
    int sorokSzama, oszlopokSzama;
    Palya palya;

    if(LetezikEMentes())
    {
        MenuKirajzol();
        char* mode = JatekKivalasztas();
        if(strcmp(mode, "régi") == 0)
            palya = Beolvas(&sorokSzama, &oszlopokSzama);
        else
        {
            int aknakSzama;
            PalyaParamaterketEsAknaSzamotBeker(&sorokSzama, &oszlopokSzama, &aknakSzama);
            Palya palya = PalyatLetrehoz(sorokSzama, oszlopokSzama);
            TablatFeltolt(palya);
            AknaElhelyez(palya, aknakSzama);
        }
    }
    int aknakSzama;
    PalyaParamaterketEsAknaSzamotBeker(&sorokSzama, &oszlopokSzama, &aknakSzama);
    palya = PalyatLetrehoz(sorokSzama, oszlopokSzama);
    TablatFeltolt(palya);
    AknaElhelyez(palya, aknakSzama);
    Kirajzol(palya);

    bool nyertE = false;
    bool vesztettE = false;
    LepesTipusokatKiir();
    while(!nyertE && !vesztettE)
    {
        Ment(palya, oszlopokSzama, sorokSzama);
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
