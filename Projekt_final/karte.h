#pragma once
#ifndef KARTE_H
#define KARTE_H
#include <stdio.h>
#define MAXSZ 100

struct Karta {
    int vrijednost;
    int boja;
};

typedef struct Igrac {
	char ime[20];
	int bodovi;
}igrac;

//igrac igrac1,igrac2;
igrac sviIgraci[100];

struct Ruka {
    struct Karta karte[5];
};

struct Spil {
    struct Karta sveKarte[52];
    int brojPodKarata;
};

struct Ruka ruka1, ruka2;

struct Spil spil;

static const char* vrijednostString[] = {"Dva","Tri","Cetiri","Pet","Sest","Sedam","Osam","Devet","Deset","Decko","Dama","Kralj","As" };

static const char* bojaString[] = {"Srce","Tref","Karo","Pik" };

static const char* rankString[] = {"Najvisa karta","Jedan par","Dva para","Tris","Straight","Boja","Full House","Poker","Skala u boji","Nula"};

void unosIgraca();

void generiranjeRuke();

struct Karta dijeliKartu();

void ispisiRuke();

void usporediRuke();

FILE* otvoriFile();

void upisiFile();

void ljestvica();
#endif // !KARTE_H