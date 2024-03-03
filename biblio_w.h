#ifndef Biblio_w
#define Biblio_w

#define SZEROKOSC 7
#define WYSOKOSC 7
#define WIN 5

//zalozenia ze 0 = kolko, 1 = krzyzyk
//typedef enum {KOLKO = 0, KRZYZYK = 1} Znaczek;

typedef struct plansza
{
    union
    {
        char _2D[SZEROKOSC][WYSOKOSC];
        char _1D[SZEROKOSC*WYSOKOSC];
    } pole;
    int move ,stan;
}plansza;

typedef struct ruch
{
    int kolumna, wiersz;
}Ruch;

typedef struct 
{
    plansza *sz;
    uint8_t glebokosc;
}arggo;

extern void wypisz(plansza *tictactoe);
extern void zapisz_pustymi(plansza *sz);
extern plansza wykonaj_ruch(plansza *tictactoe, Ruch wsp);
extern int mozliwe_ruchy(plansza *tictactoe, Ruch *bufor);
extern int ocena(plansza *tictactoe);
extern int16_t negamax(plansza *sz, uint8_t glebokosc, int16_t alfa, int16_t beta);
extern void go_depth(arggo *arggs);

#endif