#ifndef JATEKALLAS_H_INCLUDED
#define JATEKALLAS_H_INCLUDED
#include <stdbool.h>
#include <time.h>

//Cellák állapotának a jellemzője
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
    // Két dimenziós tömb, aminek az első dimenziója a sorok, a második pedig az oszlopok
    Cella** tabla;
    int oszlopokSzama, sorokSzama, aknakSzama;
    // Ha volt már felrobbant akna, akkor ez annak az x pozíciója(-1, ha nem robbant még)
    int robbanoX;
    // Ha volt már felrobbant akna, akkor ez annak az y pozíciója(-1, ha nem robbant még)
    int robbanoY;
} Palya;

// A játék legvégén felszabadít minden dinamikusan lefoglalt memóriát
void PalyaFelszabadit(Palya* palya);
bool Lepes(Palya* palya);
bool NyertE(Palya* palya);

// A játékos által korábban beírt mennyiségű aknát véletlen pozíciókban elhelyezi a pályán (Sorsol függvény segítségével)
void AknaElhelyez(Palya* palya);

// Minden cellát alapállapotba állít (nincs akna, felfedetlen)
void TablatFeltolt(Palya* palya);

// Dinamikusan létrehozza a pályán lévő cellákat
// Olyan pályát vár, ahol már meg van adva a sorok és az oszlopok száma
void PalyaCellakatLetrehoz(Palya* palya);

// A játék végén mindent felold (azért, hogy lássa a játékos, mit hibázott)
void MindentFelold(Palya* palya);

#endif // JATEKALLAS_H_INCLUDED
