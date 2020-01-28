#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "hed.h"


int main() {
	struct OBRAZ *obraz;
	char nazwa[20];
	int zoom, zoo, il, pozycja, r, i;

	printf("podaj nazwe pliku PGM: ");
	scanf("%s", nazwa);
	obraz = Wczytaj(nazwa);
	do {
		do {
			printf("\nMENU: \n");
			printf("1. Negatyw \n");
			printf("2. Rozjasnianie\n");
			printf("3. Szum\n");
			printf("4. Lustro\n");
			printf("5. Zoom (najprostszy)\n");
			printf("6. Zoom (usredniajacy)\n");
			printf("7. Zoom (medianowy)\n");
			printf("8. Progowanie\n");
			printf("9. Histogram\n");
			printf("10. Obracanie obrazu\n");
			printf("11. Laczenie obrazow\n");
			printf("12. Filtr (usredniajacy)\n");
			scanf("%d", &pozycja);
			if (pozycja > 12 || pozycja < 0) {
				printf("wybierz pozycje z menu (1-12) ");
			}
		} while (pozycja > 12 || pozycja < 0);

		switch (pozycja) {
		case 1: {
			obraz = Negatyw(obraz);
			Zapis(obraz);
			break;
		}
		case 2: {
			printf("podaj wartosc o jaka chcesz zmienic jasnosc obrazu\n");
			scanf("%d", &r);
			obraz = Rozjasnianie(obraz, r);
			Zapis(obraz);
			break;
		}
		case 3: {

			obraz = Szum(obraz);
			Zapis(obraz);
			break;
		}
		case 4: {
			obraz = Lustro(obraz);
			Zapis(obraz);
			break;
		}
		case 5: {
			obraz = Zoom(obraz);
			Zapis(obraz);
			break;
		}
		case 6: {
			do {
				printf("podaj powiekszenie (potega liczby 2 w zakresie <2, 64>)\n");
				scanf("%d", &zoom);
				if (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16 && zoom != 32 && zoom != 64) printf("wybrano pozycje spoza MENU\n");
			} while (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16 && zoom != 32 && zoom != 64);
			for (i = 1; i < zoom; i = i * 2) {
				obraz = Zoom1(obraz);
				Zapis(obraz);
			}

			break;
		}
		case 7: {
			do {
				printf("podaj powiekszenie (potega liczby 2 w zakresie <2, 64>)\n");
				scanf("%d", &zoom);
				if (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16 && zoom != 32 && zoom != 64) printf("wybrano pozycje spoza MENU\n");
			} while (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16 && zoom != 32 && zoom != 64);
			for (i = 1; i < zoom; i = i * 2) {
				obraz = Zoom2(obraz);
				Zapis(obraz);
			}
			break;
		}
		case 8: {
			obraz = Progowanie(obraz);
			Zapis(obraz);
			break;
		}
		case 9: {
			obraz = Histogram(obraz);
			Zapis(obraz);
			break;
		}
		case 10: {
			obraz = Obroty(obraz);
			Zapis(obraz);
			break;
		}
		case 11: {
			obraz = Polacz(obraz);
			Zapis(obraz);
			break;
		}

		}
	} while (1 == 1);

	return 0;

}


