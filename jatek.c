#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include "palya.h"
#include "megjelenites.h"
#include "mentes.h"
#include "debugmalloc.h"
#include "jatek.h"

void JatekFuttatasa()
{
    srand(time(0));

    Palya palya;
    time_t kezdIdo, aktIdo;
    bool kelleUjat = false;
    if (LetezikEMentes())
    {
        kelleUjat = !FelhasznalotKerdezEsMentestBetolt(&palya, &kezdIdo);
    }
    else
        kelleUjat = true;

    while (true)
    {
        if (kelleUjat)
        {
            UjJatekAllapotBeallitas(&palya, &kezdIdo);
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
                int perc, mp;
                IdotSzamolPercben(&perc, &mp, kezdIdo);
                Kirajzol(&palya);
                GyozelmetKiir(perc, mp);
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

void UjJatekAllapotBeallitas(Palya* palya, int* kezdIdo)
{
    PalyaParamaterketEsAknaSzamotBekerEsBeallit(palya);
    PalyaCellakatLetrehoz(palya);
    TablatFeltolt(palya);
    AknaElhelyez(palya);
    time(kezdIdo);
}

void IdotSzamolPercben(int* pperc, int* pmp, int kezdesIdo)
{
    time_t aktIdo;
    time(&aktIdo);
    *pperc = (aktIdo - kezdesIdo) / 60;
    *pmp = ((aktIdo - kezdesIdo) - (*pperc) * 60);
}

int IdoKorlatotSzamol(Palya* palya)
{
    return palya->oszlopokSzama * palya->sorokSzama / 5;
}

bool VanEMegIdo(int idoKorlat, int kezdesIdo)
{
    time_t aktIdo;
    return idoKorlat > (time(&aktIdo) - kezdesIdo) / 60;
}

//True, ha volt betöltés
bool FelhasznalotKerdezEsMentestBetolt(Palya* palya, time_t* kezdIdo)
{
    bool voltBetoltes = false;
    MenuKirajzol();
    bool ujE = JatekKivalasztas_UjE();
    if (!ujE)
    {
        int elteltIdo;
        Beolvas(palya, &elteltIdo);
        time_t aktIdo;
        *kezdIdo = time(&aktIdo) - elteltIdo;
        return true;
    }
    return false;
}
