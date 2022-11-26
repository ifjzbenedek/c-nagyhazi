#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "jatekallas.h"
#include "megjelenites.h"
#include "mentes.h"
#include <time.h>
#include <stdint.h>

int main()
{
    srand(time(0));
    
    int sorokSzama, oszlopokSzama;
    Palya palya;
    time_t kezdIdo, aktIdo;
    int elteltIdo;
    bool kelleUjat = false;
    if(LetezikEMentes())
    {
        MenuKirajzol();
        char* mode = JatekKivalasztas();
        if (strcmp(mode, "regi") == 0)
        {
            palya = Beolvas(&sorokSzama, &oszlopokSzama, &elteltIdo);
            kezdIdo = time(&aktIdo) - elteltIdo;
        }
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
        time(&kezdIdo);
    }
    
    bool vege = false;
    Kirajzol(palya);
    LepesTipusokatKiir();
    while(!vege)
    {
        Ment(palya, oszlopokSzama, sorokSzama, kezdIdo);
        if(Lepes(palya))
        {
            MindentFelold(palya);
            Kirajzol(palya);
            VeresegetKiir();
            vege = true;
        }
        else if(NyertE(palya))
        {
            MindentFelold(palya);
            Kirajzol(palya);
            GyozelmetKiir(time(&aktIdo)-kezdIdo);
            vege = true;
        }
        else
            Kirajzol(palya);
    }
    MentestTorol();
}
