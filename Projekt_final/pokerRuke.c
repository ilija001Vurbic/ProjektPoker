#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "karte.h"
#include <ctype.h>
#include <string.h>
#define strLen strlen(str)

void unosIgraca() {
	printf("Unesite ime za prvog igraca: ");
	scanf("%s", &sviIgraci[0].ime);
	printf("Unesite ime za drugog igraca: ");
	scanf("%s", &sviIgraci[1].ime);
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
	printf("Igrac %s ima:\n", sviIgraci[0].ime);
	for (i = 0; i < 5; i++)
		printf("%s %s\n", vrijednostString[ruka1.karte[i].vrijednost], bojaString[ruka1.karte[i].boja]);
	printf("\nIgrac %s ima:\n", sviIgraci[1].ime);
	for (i = 0; i < 5; i++)
		printf("%s %s\n", vrijednostString[ruka2.karte[i].vrijednost], bojaString[ruka2.karte[i].boja]);
}

void usporediRuke() {
    int i;
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

    int h1Rank = 0, h1Consec = 0, h1Straight = 0, h1Flush = 0, h1Four = 0, h1Three = 0, h1Pairs = 0;
    int h2Rank = 0, h2Consec = 0, h2Straight = 0, h2Flush = 0, h2Four = 0, h2Three = 0, h2Pairs = 0;

    for (i = 0; i < 5; i++) {
        if (ruka1BojaCnt[i] == 5)
            h1Flush = 1;
        if (ruka2BojaCnt[i] == 5)
            h2Flush = 1;
    }
    i = 0;
    while (ruka1VrijednostCnt[i] == 0)
        i++;
    for (; i < 3 && ruka1VrijednostCnt[i]; i++)
        h1Consec++;
    if (h1Consec == 5)
        h1Straight = 1;

    i = 0;
    while (ruka2VrijednostCnt[i] == 0)
        i++;
    for (; i < 3 && ruka2VrijednostCnt[i]; i++)
        h2Consec++;
    if (h2Consec == 5)
        h2Straight = 1;

    for (i = 0; i < 14; i++) {
        if (ruka1VrijednostCnt[i] == 4)
            h1Four = 1;
        if (ruka1VrijednostCnt[i] == 3)
            h1Three = 1;
        if (ruka1VrijednostCnt[i] == 2)
            h1Pairs++;
    }
    for (i = 0; i < 14; i++) {
        if (ruka2VrijednostCnt[i] == 4)
            h2Four = 1;
        if (ruka2VrijednostCnt[i] == 3)
            h2Three = 1;
        if (ruka2VrijednostCnt[i] == 2)
            h2Pairs++;
    }

    // ruka 1 ranking
    if (h1Straight && h1Flush)
        h1Rank = 8;
    else if (h1Four)
        h1Rank = 7;
    else if (h1Three && h1Pairs == 1)
        h1Rank = 6;
    else if (h1Flush)
        h1Rank = 5;
    else if (h1Straight)
        h1Rank = 4;
    else if (h1Three)
        h1Rank = 3;
    else if (h1Pairs == 2)
        h1Rank = 2;
    else if (h1Pairs == 1)
        h1Rank = 1;
    else
        h1Rank = 0;

    // ruka 2 ranking
    if (h2Straight && h2Flush)
        h2Rank = 8;
    else if (h2Four)
        h2Rank = 7;
    else if (h2Three && h2Pairs == 1)
        h2Rank = 6;
    else if (h2Flush)
        h2Rank = 5;
    else if (h2Straight)
        h2Rank = 4;
    else if (h2Three)
        h2Rank = 3;
    else if (h2Pairs == 2)
        h2Rank = 2;
    else if (h2Pairs == 1)
        h2Rank = 1;
    else
        h2Rank = 0;

    printf("\nIgrac %s ima %s.\n", sviIgraci[0].ime, rankString[h1Rank]);
    printf("Igrac %s ima %s.\n", sviIgraci[1].ime, rankString[h2Rank]);

    if (h1Rank > h2Rank) {
        printf("%s je pobjednik!!!\n", sviIgraci[0].ime);
        sviIgraci[0].bodovi += 100;
    }
    else if (h2Rank > h1Rank) {
        printf("%s je pobjednik!!!\n", sviIgraci[1].ime);
        sviIgraci[1].bodovi += 100;
    }
    else
    {
        printf("Nerjeseno!!!\n");
        sviIgraci[0].bodovi += 50;
        sviIgraci[1].bodovi += 50;
    }
}

FILE* otvoriFile() {
	FILE* fp = NULL;
    fp = fopen("ljestvica.txt", "a+");
	if (fp == NULL)
	{
		printf("Datoteka se ne moze otvoriti.");
		exit(EXIT_FAILURE);
	}
	else {
		return fp;
	}
}

void bubbleSort(char a[][20], int n) {
    char temp[100];

    for (int j = 0; j < n - 1; j++)
    {
        for (int i = j + 1; i < n; i++)
        {
            if (strcmp(a[j], a[i]) > 0)
            {
                strcpy(temp, a[j]);
                strcpy(a[j], a[i]);
                strcpy(a[i], temp);
            }
        }
    }
}


void upisiFile() {
    FILE* fp = otvoriFile();
    fprintf(fp, "%s %d\n", sviIgraci[0].ime, sviIgraci[0].bodovi);
    fprintf(fp, "%s %d\n", sviIgraci[1].ime, sviIgraci[1].bodovi);
}

void sortBodovi(char str[][20]) {
	char razmak = " ";
	char* bodovi = strchr(str, razmak);
	printf("%s\n", *(bodovi+1));
}

void ljestvica()
{
    FILE* fp = otvoriFile();
    char line[128][20];
    int i = 0, j=0;
    int tot = 0;
    while (fgets(line[i], 20, fp))
    {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    tot = i;
    for (i = 0; i < tot; ++i)
    {
        printf("%s \n", line[i]);
       
    } 
    bubbleSort(line,tot);
    printf("\nSortirano abecedno:\n");
    for (i = 0; i < tot; ++i)
    {
        printf("%s \n", line[i]);
    }
	printf("\nSortirano po bodovima:\n");
	for (i = 0; i < tot; ++i)
    {
		sortBodovi(line[i]);
    }
	/*for (i = 0; i < tot; ++i)
	{
		printf("%s \n", line[i]);
	}*/
}