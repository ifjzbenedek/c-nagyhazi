#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED

void UjJatekAllapotBeallitas(Palya* palya, int* kezdIdo);
void JatekFuttatasa();
bool VanEMegIdo(int idoKorlat, int kezdesIdo);
int IdoKorlatotSzamol(Palya* palya);
void IdotSzamolPercben(int* pperc, int* pmp, int kezdesIdo);
bool FelhasznalotKerdezEsMentestBetolt(Palya* palya, time_t* kezdIdo);

#endif // JATEK_H_INCLUDED