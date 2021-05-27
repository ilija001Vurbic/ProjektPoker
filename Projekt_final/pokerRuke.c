#include <stdio.h>
#include "karte.h"

void generiranjeRuke() {
    int i;
    for (i = 0; i < 5; i++) {
        ruka1.karte[i] = dijeliKartu();
        ruka2.karte[i] = dijeliKartu();
    }
}

struct Karta dijeliKartu() {
    int i;
    int duplikat;
    struct Karta kartaZaDijeliti;
    while (1) {
        kartaZaDijeliti.vrijednost = rand() % 13;
        kartaZaDijeliti.boja = rand() % 4;
        duplikat = 1;
        for (i = 0; i < spil.brojPodKarata; i++) {
            if (spil.sveKarte[i].vrijednost == kartaZaDijeliti.vrijednost && spil.sveKarte[i].boja == kartaZaDijeliti.boja)
                duplikat = 0;
        }
        if (duplikat) {
            spil.brojPodKarata++;
            spil.sveKarte[spil.brojPodKarata] = kartaZaDijeliti;
            return kartaZaDijeliti;
        }
    }
}

void ispisiRuke() {
    int i;
    printf("Igrac 1 ima:\n");
    for (i = 0; i < 5; i++)
        printf("%s %s\n", vrijednostString[ruka1.karte[i].vrijednost], bojaString[ruka1.karte[i].boja]);
    printf("\nIgrac 2 ima:\n");
    for (i = 0; i < 5; i++)
        printf("%s %s\n", vrijednostString[ruka2.karte[i].vrijednost], bojaString[ruka2.karte[i].boja]);
}

void usporediRuke() {
    
}