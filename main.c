#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include "palya.h"
#include "megjelenites.h"
#include "mentes.h"
#include "debugmalloc.h"

void JatekInditas(Palya* palya, int* kezdIdo)
{
    PalyaParamaterketEsAknaSzamotBekerEsBeallit(palya);
    PalyaCellakatLetrehoz(palya);
    TablatFeltolt(palya);
    AknaElhelyez(palya);
    time(kezdIdo);
}
int main()
{
    srand(time(0));
    
    Palya palya;
    time_t kezdIdo, aktIdo;
    bool kelleUjat = false;
    if(LetezikEMentes())
    {
        MenuKirajzol();
        bool ujE = JatekKivalasztas_UjE();
        if (!ujE)
        {
            int elteltIdo;
            Beolvas(&palya, &elteltIdo);
            kezdIdo = time(&aktIdo) - elteltIdo;
        }
        else
            kelleUjat = true;
    }
    else
        kelleUjat = true;

    while (true)
    {
        if (kelleUjat)
        {
            JatekInditas(&palya, &kezdIdo);
        }
        kelleUjat = true;
        int idoKorlat = IdoKorlatotSzamol(&palya);
        bool vege = false;
        Kirajzol(&palya);
        IdoKorlatotKiir(idoKorlat);
        while (!vege)
        {
            LepesTipusokatKiir();
            Ment(&palya, kezdIdo);
            if (Lepes(&palya))
            {
                MindentFelold(&palya);
                Kirajzol(&palya);
                VeresegetKiir();
                vege = true;
            }
            else if (NyertE(&palya))
            {
                MindentFelold(&palya);
                Kirajzol(&palya);
                GyozelmetKiir(kezdIdo);
                vege = true;
            }
            else if (!VanEMegIdo(idoKorlat, kezdIdo))
            {
                MindentFelold(&palya);
                Kirajzol(&palya);
                IdoLetelt();
                vege = true;

            }
            else
                Kirajzol(&palya);
        }
        MentestTorol();
        PalyaFelszabadit(&palya);
        UjrainditasKiir();
    }
}
