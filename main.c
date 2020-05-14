#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "hed.h"


int main() {
	struct PIC *pict;
	char file_name[20];
	int zoom, zoo, il, position, r, i;

	printf("podaj nazwe pliku PGM: ");
	scanf("%s", file_name);
	pict = read_file(file_name);
	do {
		do {
			printf("\nMENU: \n");
			printf("1. Negatyw \n");
			printf("2. bright\n");
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
			scanf("%d", &position);
			if (position > 12 || position < 0) {
				printf("wybierz pozycje z menu (1-12) ");
			}
		} while (position > 12 || position < 0);

		switch (position) {
		case 1: {
			pict = Negatyw(pict);
			Save(pict);
			break;
		}
		case 2: {
			printf("podaj wartosc o jaka chcesz zmienic jasnosc obrazu\n");
			scanf("%d", &r);
			pict = bright(pict, r);
			Save(pict);
			break;
		}
		case 3: {

			pict = noise(pict);
			Save(pict);
			break;
		}
		case 4: {
			pict = Lustro(pict);
			Save(pict);
			break;
		}
		case 5: {
			pict = Zoom(pict);
			Save(pict);
			break;
		}
		case 6: {
			do {
				printf("podaj powiekszenie (potega liczby 2 w zakresie <2, 64>)\n");
				scanf("%d", &zoom);
				if (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16 && zoom != 32 && zoom != 64) printf("wybrano pozycje spoza MENU\n");
			} while (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16 && zoom != 32 && zoom != 64);
			for (i = 1; i < zoom; i = i * 2) {
				pict = Zoom1(pict);
				Save(pict);
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
				pict = Zoom2(pict);
				Save(pict);
			}
			break;
		}
		case 8: {
			pict = threshold(pict);
			Save(pict);
			break;
		}
		case 9: {
			pict = Histogram(pict);
			Save(pict);
			break;
		}
		case 10: {
			pict = rotation(pict);
			Save(pict);
			break;
		}
		case 11: {
			pict = Add(pict);
			Save(pict);
			break;
		}

		}
	} while (1 == 1);

	return 0;

}


