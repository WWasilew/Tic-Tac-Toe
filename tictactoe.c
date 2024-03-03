#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<inttypes.h>

#include "biblio_w.h"

int flaga_stopu = 0;

void silnik(void)
{

}

void zapisz_pustymi(plansza *sz)
{
    sz->move=0;
    sz->stan=0;
    for(int wiersz = WYSOKOSC; wiersz>=0; wiersz--)
    {
        for(int kolumna = SZEROKOSC; kolumna >=0; kolumna--)
        {
            sz->pole._2D[wiersz][kolumna] = '.';
            
        }
    }
}

void wypisz(plansza *sz)
{
    int i = 1;
    printf("  ");
    for(int kol = 0; kol<SZEROKOSC; kol++)
        printf("--%d",kol+1);
    printf("\n");
    for(int wiersz = 0; wiersz < WYSOKOSC; wiersz++)
    {
        printf("%2d ", i);
        ++i;
        for(int kolumna = 0; kolumna < SZEROKOSC; kolumna++)
        {
            printf("%2c ", sz->pole._2D[wiersz][kolumna]);
        }
        printf("\n");
    }
}

plansza wykonaj_ruch(plansza *tictactoe, Ruch wsp)
{
    char znak;
    if(tictactoe->move%2 == 0) 
        znak = 'O';
    else 
        znak = 'X';
    tictactoe->pole._2D[wsp.wiersz-1][wsp.kolumna-1] = znak;
    tictactoe->move++;
    if(znak == 'O')
        znak = 'X';
    else
        znak = 'O';
    return *tictactoe;
}

int mozliwe_ruchy(plansza *tictactoe, Ruch *bufor)
{
    for(int k = 0; k < WYSOKOSC*SZEROKOSC; ++k)
    {
        bufor[k].kolumna = 0;
        bufor[k].wiersz = 0;
    }
    int liczba_ruchow = 0;
    for(int j = 0; j < SZEROKOSC*WYSOKOSC; ++j)
    {
        if(tictactoe->pole._1D[j] == '.')
        {
            bufor[liczba_ruchow].kolumna = (j%SZEROKOSC)+1;
            bufor[liczba_ruchow].wiersz = (j/SZEROKOSC)+1;
            liczba_ruchow++;
        }
    }

    return liczba_ruchow;
}

int ocena(plansza *tictactoe) //O to dodajemy, X to odejmujemy!
{
    
    int ocenka = 0, maksymalnie = 0, znak = 1;
    char cznak = 'O', pcznak = 'X';
    if(tictactoe->move%2 == 1)
        cznak = 'X', pcznak = 'O';
    for(int i = 0; i < SZEROKOSC; i++)
    {
        for(int j = 0; j < WYSOKOSC; j++)
        {
            for(int k = 0; k<2;k++)
            {
                int pi = 1, po =-1;
                if(tictactoe->pole._2D[i][j] == cznak) 
                    {
                        for(int m = 0; m<4; m++)
                        {
                            maksymalnie=1;
                            int ocenap = ocenka;
                            for(int l = 1; l<WIN; l++)
                            {
                                if(tictactoe->pole._2D[i+po*l][j+pi*l] == cznak && (i+po*l)<SZEROKOSC && (i+po*l) >=0 && (j+pi*l) <WYSOKOSC)
                                {
                                    maksymalnie++;
                                    if(maksymalnie == WIN)//wygrana
                                    {
                                        tictactoe->stan= znak*1;
                                        return znak*1000;
                                        break;
                                    }
                                }
                                else if(tictactoe->pole._2D[i+po*l][j+pi*l] == pcznak || (i+po*l)>=SZEROKOSC || (i+po*l) <0 || (j+pi*l) >=WYSOKOSC)
                                { 
                                    maksymalnie = 0;
                                    break;;
                                }
                            }
                            ocenka = ocenka + znak*((maksymalnie-1) * maksymalnie*maksymalnie);
                            maksymalnie = 1;
                            if(m<2)
                                po = po +1;
                            else 
                                pi = pi -1;
                        }
                    }
                char swap = cznak;
                cznak = pcznak;
                pcznak = swap; 
                znak = -znak;
            }
        }
    }
    return ocenka;
}

int16_t negamax(plansza *kopia, uint8_t glebokosc, int16_t alfa, int16_t beta)
{
    if(!glebokosc)
        return ocena(kopia);
    Ruch legal[WYSOKOSC*SZEROKOSC];
    uint8_t liczba_ruchow = mozliwe_ruchy(kopia, legal);
    int16_t ocenai = -glebokosc*1000, ocena_robocza;
    for(uint8_t i = 0; i < liczba_ruchow; ++i)
    {
        if(flaga_stopu) 
            break;
        plansza kopia2 = *kopia;
        wykonaj_ruch(&kopia2, legal[i]);
        ocena_robocza = -negamax(&kopia2, glebokosc - 1, -beta, -alfa);
        if(kopia2.stan==1 || kopia2.stan == -1)
        {
            int ocenatest = ocena(kopia),znak = 1;
            if(kopia->stan != 0)
            {
                ocenai = glebokosc*ocenatest;
                break;
            }
        }
        if(ocena_robocza > ocenai && !flaga_stopu)
            ocenai = ocena_robocza;
        if(ocenai > alfa && !flaga_stopu)
            alfa = ocenai;
        if(alfa >= beta && !flaga_stopu)
            break;
    }
    return ocenai;
}

void go_depth(arggo *arggs)
{
    Ruch legalne[WYSOKOSC*SZEROKOSC], debesciak;
    uint8_t liczba_ruchow = mozliwe_ruchy(arggs->sz, legalne), znak, gleb =arggs->glebokosc;
    if(liczba_ruchow< arggs->glebokosc)
    {
        gleb = liczba_ruchow-1;
        if(gleb == 0)
        {
            printf(" Koniec gry, remis\n");
            arggs->sz->stan=2;
            goto stop;
        }
    }
    int16_t ocena =-gleb*1000, ocena_robocza, alfa = (gleb-1)*-1000, beta = (gleb-1)*1000;
    for(uint8_t i = 0; i < liczba_ruchow; ++i)
    {
        if(flaga_stopu) 
            break;
        //printf("info currmove ");
        //printf("k:%d w:%d \n", legalne[i].kolumna, legalne[i].wiersz);
        plansza kopia = *arggs->sz;
        wykonaj_ruch(&kopia, legalne[i]);
        ocena_robocza = -negamax(&kopia, gleb - 1, -beta, -alfa);
        if(ocena_robocza > ocena && !flaga_stopu)
        {
            ocena = ocena_robocza;
            printf("info score cp %d depth %d pv ", ocena, gleb);
            printf("k:%d w:%d \n", legalne[i].kolumna, legalne[i].wiersz);
            debesciak = legalne[i];
        }
        if(ocena>alfa && !flaga_stopu)
            alfa = ocena;
        if(alfa >= beta && !flaga_stopu)
            break;
    }
    if(debesciak.kolumna*debesciak.wiersz == 0)
    printf("bestmove k:%d w:%d\n", debesciak.kolumna, debesciak.wiersz);
    flaga_stopu = 0;
    wykonaj_ruch(arggs->sz, debesciak);
    stop:;
}

void main()
{
    pthread_t watek_silnika;
    plansza tictactoe;
    Ruch mozliwe[WYSOKOSC*SZEROKOSC];
    //bufor na dane wejściowe, to co wpisujemy do konsoli
    char bufor[1024];

    int dlugosc_bufora;

    if(pthread_create(&watek_silnika, NULL, (void *)silnik, NULL))
    {
        printf("info string error: engine couldn't start it's thead\n");
        printf("Karny kutas");
        return;
    }

    for(printf("info string engine started\n");;scanf("\n"))
    {
        scanf("%[^\n]", bufor);
        dlugosc_bufora = strlen(bufor);

        if(strstr(bufor, "quit") == bufor && dlugosc_bufora == 4)
        {
            flaga_stopu = 1;
            break;
        }
        if(strstr(bufor, "uci") == bufor && dlugosc_bufora == 3)
            printf("id name Ticktacktoe 0.5\nid authors WW company and MP corporation\nuciok\n");
        else if (strstr(bufor, "isready") == bufor && dlugosc_bufora == 7)
            printf("readyok\n");
        else if (strstr(bufor,"!nowa") == bufor && dlugosc_bufora == 5)
        {
            zapisz_pustymi(&tictactoe);
            tictactoe.move = 0;
            tictactoe.stan = 0;
        }    
        else if (strstr(bufor,"!wypisz") == bufor && dlugosc_bufora ==7)
        {
            wypisz(&tictactoe);
        }
        else if (strstr(bufor, "!ruch") == bufor)
        {
            tictactoe = wykonaj_ruch(&tictactoe, (Ruch) {.kolumna = (bufor[6] - '0') * 10 + (bufor[7] - '0'), .wiersz = (bufor[9] - '0') * 10 + (bufor[10] - '0')});
        }
        else if (strstr(bufor, "!mozliwe") == bufor && dlugosc_bufora == 8)
        {
            int ile = mozliwe_ruchy(&tictactoe, mozliwe);
            printf("\nLiczba mozliwych ruchow: %d\n", ile);
            for(int i = 0; i < ile; ++i)
                printf("K:%2d W:%2d\n",mozliwe[i].kolumna, mozliwe[i].wiersz);
            printf("\n");
        }
        else if (strstr(bufor, "!ocena") == bufor && dlugosc_bufora == 6)
        {
            char znak;
            if(tictactoe.stan == 1)
                znak = 'O';
            else if (tictactoe.stan == -1)
                znak = 'X';

            int ocenka = ocena(&tictactoe);
            printf("Ocena sytuacji: %d\n", ocenka);
            if(ocenka == tictactoe.stan*10000)
                printf("Wygrywa %c\nStan: %d\n", znak, tictactoe.stan);
        }
        else if (strstr(bufor, "!analiza") == bufor)
        {
            uint8_t gleb = (bufor[9] - '0');
            arggo current = {.glebokosc = gleb, .sz = &tictactoe};
            go_depth(&current);
        }
        else if (strstr(bufor, "!walka") == bufor)
        {
            while (tictactoe.stan == 0)
            {
                uint8_t gleb1 = (bufor[7] - '0');
                uint8_t gleb2 = (bufor[9] - '0');
                arggo current1 = {.glebokosc = gleb1, .sz = &tictactoe};
                arggo current2 = {.glebokosc = gleb2, .sz = &tictactoe};
                go_depth(&current1);
                wypisz(&tictactoe);
                ocena(&tictactoe);
                if(tictactoe.stan !=0)
                    break;
                go_depth(&current2);
                wypisz(&tictactoe);
                ocena(&tictactoe);
            }
        }
        else if (strstr(bufor, "!help") == bufor)
        {
            printf("Lista komend:\n !nowa - zeruje gre, czysta plansza\n !wypisz - zobacz stan planszy\n !ruch [kolumna] [wiersz] - wykonaj ruch\n !mozliwe - poznaj mozliwe ruchy\n !ocena - zobacz ocene stanu gry\n !analiza [gleb] - algorytm oceniający kolejny ruch z daną glebokoscia\n !walka [O] [X] - komputer vs komputer z innymi gleb przeszukiwania, gra do wygranej, podaj glebokosci analizy\n");
        }
    }
    
    pthread_join(watek_silnika, NULL);
}
