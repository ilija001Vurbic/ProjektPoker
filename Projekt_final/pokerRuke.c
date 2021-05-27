#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "karte.h"
#include <ctype.h>

void unosIgraca() {
	printf("Unesite ime za prvog igraca: ");
	scanf("%s", &igrac1.ime);
	printf("Unesite ime za drugog igraca: ");
	scanf("%s", &igrac2.ime);
}

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
	printf("Igrac %s ima:\n", igrac1.ime);
	for (i = 0; i < 5; i++)
		printf("%s %s\n", vrijednostString[ruka1.karte[i].vrijednost], bojaString[ruka1.karte[i].boja]);
	printf("\nIgrac %s ima:\n", igrac2.ime);
	for (i = 0; i < 5; i++)
		printf("%s %s\n", vrijednostString[ruka2.karte[i].vrijednost], bojaString[ruka2.karte[i].boja]);
}

void usporediRuke() {
	int i, j;
	int ruka1VrijednostCnt[13];
	int ruka1BojaCnt[4];
	int ruka2VrijednostCnt[13];
	int ruka2BojaCnt[4];
	memset(ruka1VrijednostCnt, 0, sizeof(ruka1VrijednostCnt));
	memset(ruka1BojaCnt, 0, sizeof(ruka1BojaCnt));
	memset(ruka2VrijednostCnt, 0, sizeof(ruka2VrijednostCnt));
	memset(ruka2BojaCnt, 0, sizeof(ruka2BojaCnt));
	for (i = 0; i < 5; i++) {
		ruka1VrijednostCnt[ruka1.karte[i].vrijednost]++;
		ruka1BojaCnt[ruka1.karte[i].boja]++;
		ruka2VrijednostCnt[ruka2.karte[i].vrijednost]++;
		ruka2BojaCnt[ruka2.karte[i].boja]++;
	}
	int r1Rank = 0, r1Consec = 0, r1Straight = 0, r1Flush = 0, r1Four = 0, r1Three = 0, r1Pairs = 0, r1Nula=0;
	int r2Rank = 0, r2Consec = 0, r2Straight = 0, r2Flush = 0, r2Four = 0, r2Three = 0, r2Pairs = 0, r2Nula=0;
	for (i = 0; i < 5; i++) {
		if (ruka1BojaCnt[i] == 5)
			r1Flush = 1;
		if (ruka2BojaCnt[i] == 5)
			r2Flush = 1;
	}
	i = 0;
	while (ruka1VrijednostCnt[i] == 0)
		i++;
	for (; i < 3 && ruka1VrijednostCnt[i]; i++)
		r1Consec++;
	if (r1Consec == 5)
		r1Straight = 1;
	i = 0;
	while (ruka2VrijednostCnt[i] == 0)
		i++;
	for (; i < 3 && ruka2VrijednostCnt[i]; i++)
		r2Consec++;
	if (r2Consec == 5)
		r2Straight = 1;
	for (i = 0; i < 14; i++) {
		if (ruka1VrijednostCnt[i] == 4)
			r1Four = 1;
		if (ruka1VrijednostCnt[i] == 3)
			r1Three = 1;
		if (ruka1VrijednostCnt[i] == 2)
			r1Pairs++;
	}
	for (i = 0; i < 14; i++) {
		if (ruka2VrijednostCnt[i] == 4)
			r2Four = 1;
		if (ruka1VrijednostCnt[i] == 3)
			r2Three = 1;
		if (ruka1VrijednostCnt[i] == 2)
			r2Pairs++;
	}
	if (r1Straight && r1Flush)
		r1Rank = 8;
	else if (r1Four)
		r1Rank = 7;
	else if (r1Three && r1Pairs == 1)
		r1Rank = 6;
	else if (r1Flush)
		r1Rank = 5;
	else if (r1Straight)
		r1Rank = 4;
	else if (r1Three)
		r1Rank = 3;
	else if (r1Pairs == 2)
		r1Rank = 2;
	else if (r1Pairs == 1)
		r1Rank = 1;
	else
		r1Rank = r1Nula;
	if (r2Straight && r2Flush)
		r2Rank = 8;
	else if (r2Four)
		r2Rank = 7;
	else if (r2Three && r2Pairs == 1)
		r2Rank = 6;
	else if (r2Flush)
		r2Rank = 5;
	else if (r2Straight)
		r2Rank = 4;
	else if (r2Three)
		r2Rank = 3;
	else if (r2Pairs == 2)
		r2Rank = 2;
	else if (r2Pairs == 1)
		r2Rank = 1;
	else
		r2Rank = r2Nula;

	printf("\nIgrac %s ima %s.\n", igrac1.ime, rankString[r1Rank]);
	printf("Igrac %s ima %s.\n", igrac2.ime, rankString[r2Rank]);

	igrac1.bodovi = 0;
	igrac2.bodovi = 0;
	if (r1Rank > r2Rank)
	{
		printf("Igrac %s je pobjedio!!!\n", igrac1.ime);
		igrac1.bodovi += 100;
	}

	else if (r2Rank > r1Rank) {
		printf("Igrac %s je pobjedio!!!\n", igrac2.ime);
		igrac2.bodovi += 100;
	}
	else
	{
		printf("Nerjeseno!!!\n");
		igrac1.bodovi += 50;
		igrac2.bodovi += 50;
	}
}

FILE* otvoriFile() {
	FILE* fp = NULL;
	fp = fopen("C:\\Users\\student\\ljestvica.txt", "a");
	if (fp == NULL)
	{
		printf("Datoteka se ne moze otvoriti.");
		exit(EXIT_FAILURE);
	}
	else {
		return fp;
	}
}

void ljestvica()
{
	printf("%s %d", igrac1.ime, igrac1.bodovi);
	printf("\n%s %d\n", igrac2.ime, igrac2.bodovi);
	FILE* fp = otvoriFile();
	if (igrac1.bodovi < igrac2.bodovi) {
		fprintf(fp, "\n%s %d\n", igrac2.ime, igrac2.bodovi);
		fprintf(fp, "\n%s %d\n", igrac1.ime, igrac1.bodovi);
	}
	else {
		fprintf(fp, "\n%s %d\n", igrac1.ime, igrac1.bodovi);
		fprintf(fp, "\n%s %d\n", igrac2.ime, igrac2.bodovi);
	}
}

