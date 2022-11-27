#ifndef MEGJELENITES_H_INCLUDED
#define MEGJELENITES_H_INCLUDED

// A konzol kezdőpozíciójába újrarajzolja a pályát
void Kirajzol(Palya* palya);

void LepestBeker(int* plepesSorSzam, int* plepesOszlopSzam, char* lepesTipus, Palya* palya);

void LepesTipusokatKiir();

void PalyaParamaterketEsAknaSzamotBekerEsBeallit(Palya* palya);

bool JatekKivalasztas_UjE();

void GyozelmetKiir(int perc, int mp);

void VeresegetKiir();

void UjrainditasKiir();

void IdoLetelt();

void IdoKorlatotKiir(int idoKorlat);

void MenuKirajzol();

#endif // MEGJELENITES_H_INCLUDED
