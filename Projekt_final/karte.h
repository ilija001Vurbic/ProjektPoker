#pragma once
#ifndef KARTE_H
struct Karta {
    int vrijednost;
    int boja;
};

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

static const char* rankString[] = {"Najvisa karta","Jedan par","Dva para","Tris","Straight","Boja","Full House","Poker","Skala u boji" };

void generiranjeRuke();

struct Karta dijeliKartu();

void ispisiRuke();

void usporediRuke();
#endif // !KARTE_H
