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
    bool kelleUjat = false;
    if(LetezikEMentes())
    {
        MenuKirajzol();
        char* mode = JatekKivalasztas();
        if(strcmp(mode, "regi") == 0)
            palya = Beolvas(&sorokSzama, &oszlopokSzama);
        else
            kelleUjat = true;
    }
    else
        kelleUjat = true;

    if(kelleUjat)
    {
        int aknakSzama;
        PalyaParamaterketEsAknaSzamotBeker(&sorokSzama, &oszlopokSzama, &aknakSzama);
        palya = PalyatLetrehoz(sorokSzama, oszlopokSzama);
        TablatFeltolt(palya);
        AknaElhelyez(palya, aknakSzama);
    }

    Kirajzol(palya);

    bool vege = false;
    LepesTipusokatKiir();
    while(!vege)
    {
        Ment(palya, oszlopokSzama, sorokSzama);
        if(Lepes(palya))
        {
            VeresegetKiir();
            vege = true;
            MindentFelold(palya);
            MentestTorol();
        }
        else if(NyertE(palya))
        {
            GyozelmetKiir();
            vege = true;
            MindentFelold(palya);
            MentestTorol();
        }
        
        Kirajzol(palya);
        
    }
}
