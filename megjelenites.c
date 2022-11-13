#include <stdio.h>
#include <stdlib.h>
#include "jatekallas.h"

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
