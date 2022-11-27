#ifndef JATEKALLAS_H_INCLUDED
#define JATEKALLAS_H_INCLUDED
#include <stdbool.h>
#include <time.h>

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
    int oszlopokSzama, sorokSzama, aknakSzama;
    // -1, ha nem robbant még
    int robbanoX;
    // -1, ha nem robbant még
    int robbanoY;
} Palya;

void PalyaFelszabadit(Palya* palya);
bool Lepes(Palya* palya);
bool NyertE(Palya* palya);
void AknaElhelyez(Palya* palya);
void TablatFeltolt(Palya* palya);
void PalyaCellakatLetrehoz(Palya* palya);
void MindentFelold(Palya* palya);

#endif // JATEKALLAS_H_INCLUDED
