#ifndef JATEKALLAS_H_INCLUDED
#define JATEKALLAS_H_INCLUDED
#include <stdbool.h>

typedef enum Allapot
{   feloldva,
    megjelolve,
    feloldatlan
} Allapot ;


typedef struct Cella
{
    Allapot all;
    bool aknaE;
} Cella;


typedef struct Palya
{
    Cella** tabla;
    int oszlopokSzama, sorokSzama;
} Palya;

bool Lepes(Palya palya);
bool NyertE(Palya palya);
void AknaElhelyez(Palya palya, int aknakSzama);
void TablatFeltolt(Palya palya);
Palya PalyatLetrehoz(int sorokSzama, int oszlopokSzama);
void MindentFelold(Palya palya);

#endif // JATEKALLAS_H_INCLUDED
