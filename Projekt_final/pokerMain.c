#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "karte.h"

int main() {
	spil.brojPodKarata = 0;
	int end = 1, endPoker = 1;
	int odabir, pokerOdabir;
	srand(time(NULL));
	while (end)
	{
		printf("------------------------POKER---------------------------");
		printf("\nOdaberite:\n");
		/*unosMain:*/printf("\n1 - Unesite imena igraca\n2 - Zapocnite igru\n3 - Prikazi ljestvicu\n4 - Izadi iz igre\n");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1:
			unosIgraca();
			//goto unosMain;
			break;
		case 2:

			while (endPoker)
			{
				printf("----------------PODIZBORNIK-------------------");
			/*unosPoker:*/ printf("\n1 - Podijeli karte\n2 - Pokazi karte\n3 - Natrag na izbornik\n");
				scanf("%d", &pokerOdabir);
				switch (pokerOdabir)
				{
				case 1:
					generiranjeRuke();
					printf("\nKarte su podijeljene!\n");
					//goto unosPoker;
					continue;
				case 2:
					generiranjeRuke();
					ispisiRuke();
					usporediRuke();
					//goto unosPoker;
					continue;
				case 3:
					printf("\nVracanje na glavni izbornik.\n");
					endPoker = 0;
					//goto unosMain;
					break;
				default:
					printf("\nNeispravan unos. Unesite ponovno!\n");
					//goto unosPoker;
					break;
				}
				break;
		case 3:
			upisiFile();
			ljestvica();
			//goto unosMain;
			break;
		case 4:
			printf("\nZavrsetak programa.\n");
			end = 0;
			break;
		default:
			printf("\nNeispravan unos. Unesite ponovno!\n");
			//goto unosMain;
			break;
			}
		}
	}
	return 0;
}