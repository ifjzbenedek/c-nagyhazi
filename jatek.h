#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED

// Az alkalmazás indulásától a kilépésig vezérli a játékok menetét
void JatekFuttatasa();

void UjJatekAllapotBeallitas(Palya* palya, int* kezdIdo);

bool VanEMegIdo(int idoKorlat, int kezdesIdo);

int IdoKorlatotSzamol(Palya* palya);

void IdotSzamolPercben(int* pperc, int* pmp, int kezdesIdo);

// Megkérdezi a felhasználót, hogy akarja-e a korábbi mentést használni. True-val tér vissza, ha volt betöltés
bool FelhasznalotKerdezEsMentestBetolt(Palya* palya, time_t* kezdIdo);

#endif // JATEK_H_INCLUDED