#include <stdio.h>
#include <stdlib.h>
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


int Sorsol(int sorokSzama, int oszlopokSzama)
{
    return rand()%(sorokSzama*oszlopokSzama);
}


void TablatFeltolt(Palya palya)
{
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        for(int j = 0 ; j < palya.oszlopokSzama; ++j)
        {
            Cella ujCella;
            ujCella.aknaE = false;
            ujCella.all = feloldatlan;
            palya.tabla[i][j] = ujCella;
        }
    }
}


void Kezdes(Palya palya, int aknakSzama)
{
    for(int i = 0; i < aknakSzama; ++i)
    {
        int sorsoltSzam = Sorsol(palya.sorokSzama, palya.oszlopokSzama);
        int sor = (sorsoltSzam / (palya.oszlopokSzama));
        int oszlop = sorsoltSzam - ((palya.oszlopokSzama) * (sor));
        if(palya.tabla[sor][oszlop].aknaE)
            i -= 1;
        else
            palya.tabla[sor][oszlop].aknaE = true;
    }
}


int SzomszedosAknaszam(Palya palya, int sor, int oszlop)
{
    int kornyezoAknaszam = 0;
    for(int i = sor - 1; i <= sor + 1; ++i)
    {
        for(int j = oszlop - 1; j <= oszlop + 1; ++j)
        {
            if(i <= palya.sorokSzama-1 & j <= palya.oszlopokSzama-1 & i >= 0 && j >= 0 && palya.tabla[i][j].aknaE && !(sor == i && oszlop == j))
            {
                kornyezoAknaszam++;
            }
        }
    }
    return kornyezoAknaszam;
}


void Kirajzol(Palya palya)
{
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        for(int j = 0; j < palya.oszlopokSzama; ++j)
        {
            if(palya.tabla[i][j].all == feloldatlan)
                printf("#");
            else if(palya.tabla[i][j].all == megjelolve)
                printf("Z");
            else
            {
                if(palya.tabla[i][j].all == feloldva && palya.tabla[i][j].aknaE)
                    printf("*");
                else
                {
                    int aknakKorulotte = SzomszedosAknaszam(palya, i, j);
                    printf("%d", aknakKorulotte);
                }

            }
        }
        printf("\n");
    }
}

void Tisztitas(int sor, int oszlop, Palya palya)
{
    for(int i = sor - 1; i <= sor + 1; ++i)
    {
        for(int j = oszlop - 1; j <= oszlop + 1; ++j)
        {
            if(i <= palya.sorokSzama-1 & j <= palya.oszlopokSzama-1 & i >= 0 && j >= 0 & palya.tabla[i][j].all == feloldatlan)
            {
                palya.tabla[i][j].all = feloldva;
                if(SzomszedosAknaszam(palya, i, j) == 0)
                    Tisztitas(i,j,palya);
            }

        }
    }
}

bool NyertE(Palya palya)
{
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        for(int j = 0; j < palya.oszlopokSzama; ++j)
        {
            if(palya.tabla[i][j].aknaE && palya.tabla[i][j].all == feloldatlan)
                return false;
        }
    }
    return true;
}

bool RobbanE(Palya palya, int sor, int oszlop)
{
    if(palya.tabla[sor][oszlop].aknaE)
    {
        return true;
    }

    return false;

}

bool Lepes(Palya palya)
{
    printf("Várom a következõ lépését típus:sor:oszlop formátumban!\n");
    char lepesSor, lepesOszlop, lepesTipus;
    int lepesSorSzam = 0;
    int lepesOszlopSzam = 0;
    scanf("\n%c:%c:%c", &lepesTipus, &lepesSor, &lepesOszlop);
    lepesSorSzam = lepesSor - 'A';
    lepesOszlopSzam = lepesOszlop - 'a';
    if(lepesTipus == 'M')
    {
        palya.tabla[lepesSorSzam][lepesOszlopSzam].all = megjelolve;
    }
    else if(lepesTipus == 'F')
    {
        palya.tabla[lepesSorSzam][lepesOszlopSzam].all = feloldva;
        if(SzomszedosAknaszam(palya, lepesSorSzam, lepesOszlopSzam) == 0)
        {
            Tisztitas(lepesSorSzam,lepesOszlopSzam,palya);
        }
        Kirajzol(palya);
        return RobbanE(palya, lepesSorSzam, lepesOszlopSzam);


    }
    else
    {
        printf("Nem helyes az oszlop/sor amit megadott!\n");
    }
    Kirajzol(palya);
    return false;
}


int main()
{
    srand(time(0));
    int aknakSzama;
    Palya palya;
    printf("Add meg a palya mereteit és a aknak szamat oszlop:sor:aknak formatumban!\n");
    while(scanf("%d:%d:%d", &palya.oszlopokSzama, &palya.sorokSzama, &aknakSzama) != 3)
    {
        printf("Probalja ujra, nem megfelelo a formatum!");
    }
    palya.tabla = (Cella**) malloc(palya.sorokSzama * sizeof(Cella*));
    for(int i = 0; i < palya.sorokSzama; ++i)
    {
        Cella* sor;
        sor = (Cella*) malloc(palya.oszlopokSzama * sizeof(Cella));
        palya.tabla[i] = sor;
    }
    //Lepes(palya);
    TablatFeltolt(palya);
    printf("Siker!");
    Kezdes(palya, aknakSzama);
    printf("Feltoltve!\n");
    Kirajzol(palya);
    bool nyertE = false;
    bool vesztettE = false;

    while(!nyertE && !vesztettE)
    {
        if(Lepes(palya))
        {
            printf("Sajnos aknára léptél és vesztettél!\n");
            vesztettE = true;
            Kirajzol(palya);
        }
        else if(NyertE(palya))
        {
            printf("Gratulálunk, nyertél!\n");
            nyertE = true;
            Kirajzol(palya);
        }


    }
}
