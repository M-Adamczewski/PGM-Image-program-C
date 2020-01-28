#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "hed.h"


struct OBRAZ *Gradient(int szer, int wys, int szar) {

	struct OBRAZ *wsk_na_str;
	int i, j;


	wsk_na_str = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	wsk_na_str->x = szer;
	wsk_na_str->y = wys;
	wsk_na_str->skala = szar;
	wsk_na_str->pixel = (int**)calloc(wsk_na_str->x, sizeof(int*));
	for (i = 0; i<wsk_na_str->x; i++) {
		wsk_na_str->pixel[i] = (int*)calloc(wsk_na_str->y, sizeof(int));
	}

	for (i = 0; i<wsk_na_str->x; i++) {

		for (j = 0; j<wsk_na_str->y; j++) {
			wsk_na_str->pixel[i][j] = j;
		}
	}
	return wsk_na_str;
}
//niepotrzebne ale ready
void Zapis(struct OBRAZ *do_zapisu) {
	int i, j;

	FILE *wsk;

	wsk = fopen("nowy_obraz.pgm", "w");
	fprintf(wsk, "%s\n", "P2");
	fprintf(wsk, "%s\n", "# komentarz");
	fprintf(wsk, "%d %d\n", do_zapisu->x, do_zapisu->y);
	fprintf(wsk, "%d\n", do_zapisu->skala);

	for (j = 0; j<do_zapisu->y; j++) {
		for (i = 0; i<do_zapisu->x; i++) {
			fprintf(wsk, "%d ", do_zapisu->pixel[j][i]);
		}
		fprintf(wsk, "\n");
	}
	fclose(wsk);
}
//ready
struct OBRAZ *Skos(int szer, int wys, int szar) {

	struct OBRAZ *wsk_na_str;
	int i, j;


	wsk_na_str = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	wsk_na_str->x = szer;
	wsk_na_str->y = wys;
	wsk_na_str->skala = szar;
	wsk_na_str->pixel = (int**)calloc(wsk_na_str->x, sizeof(int*));
	for (i = 0; i<wsk_na_str->x; i++) {
		wsk_na_str->pixel[i] = (int*)calloc(wsk_na_str->y, sizeof(int));
	}

	for (i = 0; i<wsk_na_str->x; i++) {
		for (j = 0; j<wsk_na_str->y; j++) {

			wsk_na_str->pixel[j][i] = (i + j) / 2;
		}
	}
	return wsk_na_str;
}
//ready ale po co
struct OBRAZ *Wczytaj(char *nazwa) {
	int i, j, s, w, sz;
	struct OBRAZ *wsk_na_str;
	char bufor[100];
	FILE *wsk;

	wsk = fopen(nazwa, "r");
	if (wsk == NULL)
	{
		struct OBRAZ *obraz;
		printf("Nie udalo sie otworzyc pliku, stworz wlasny, gradient\n podaj szerokosc\n");
		scanf("%d", &s);
		printf("podaj wysokosc\n");
		scanf("%d", &w);
		printf("podaj skale szarosci\n");
		scanf("%d", &sz);
		obraz = Gradient(s, w, sz);
		Zapis(obraz);
		/*	printf("program bêdzie pracowa³ na pliku 001.pgm\n");
		nazwa = "001.pgm";
		wsk = fopen(nazwa, "r");
		fgets(bufor, 100, wsk);
		fgets(bufor, 100, wsk);

		wsk_na_str = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));
		//skanowanie parametrów z pocz¹tku pliku
		fscanf(wsk, "%d%d%d", &wsk_na_str->x, &wsk_na_str->y, &wsk_na_str->skala);
		//alokacja
		wsk_na_str->pixel = (int**)calloc(wsk_na_str->y, sizeof(int*));
		for (i = 0; i < wsk_na_str->y; i++) {
		wsk_na_str->pixel[i] = (int*)calloc(wsk_na_str->x, sizeof(int));
		}

		//wczytanie
		for (j = 0; j < wsk_na_str->y; j++) {
		for (i = 0; i < wsk_na_str->x; i++) {
		fscanf(wsk, "%d", &wsk_na_str->pixel[j][i]);
		}
		}

		fclose(wsk);
		return wsk_na_str;
		*/
	}




	else {
		fgets(bufor, 100, wsk);
		fgets(bufor, 100, wsk);

		wsk_na_str = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));
		//skanowanie parametrów z pocz¹tku pliku
		fscanf(wsk, "%d%d%d", &wsk_na_str->x, &wsk_na_str->y, &wsk_na_str->skala);
		//alokacja 
		wsk_na_str->pixel = (int**)calloc(wsk_na_str->y, sizeof(int*));
		for (i = 0; i < wsk_na_str->y; i++) {
			wsk_na_str->pixel[i] = (int*)calloc(wsk_na_str->x, sizeof(int));
		}

		//wczytanie
		for (j = 0; j < wsk_na_str->y; j++) {
			for (i = 0; i < wsk_na_str->x; i++) {
				fscanf(wsk, "%d", &wsk_na_str->pixel[j][i]);
			}
		}

		fclose(wsk);
		return wsk_na_str;
	}
}
//ready
struct OBRAZ *Negatyw(struct OBRAZ *we) {
	struct OBRAZ *wyj;
	int i, j;
	wyj = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));
	wyj->y = we->y;
	wyj->x = we->x;
	wyj->skala = we->skala;


	wyj->pixel = (int**)calloc(wyj->y, sizeof(int*));
	for (i = 0; i<wyj->y; i++) {
		wyj->pixel[i] = (int*)calloc(wyj->x, sizeof(int));
	}


	for (j = 0; j<wyj->y; j++) {
		for (i = 0; i<wyj->x; i++) {
			wyj->pixel[j][i] = wyj->skala - we->pixel[j][i];
		}
	}
	return wyj;
}
//ready
struct OBRAZ *Rozjasnianie(struct OBRAZ *wej, int poziom) {

	struct OBRAZ *wyjs;
	int i, j;
	wyjs = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));
	wyjs->y = wej->y;
	wyjs->x = wej->x;
	wyjs->skala = wej->skala;


	wyjs->pixel = (int**)calloc(wyjs->y, sizeof(int*));
	for (i = 0; i<wyjs->y; i++) {
		wyjs->pixel[i] = (int*)calloc(wyjs->x, sizeof(int));
	}


	for (j = 0; j<wyjs->y; j++) {
		for (i = 0; i<wyjs->x; i++) {
			wyjs->pixel[j][i] = wej->pixel[j][i] + poziom;
			if (wyjs->pixel[j][i] > wyjs->skala) //zabezpieczenie
				wyjs->pixel[j][i] = wyjs->skala;
			if (wyjs->pixel[j][i] < 0)
				wyjs->pixel[j][i] = 0;
		}
	}

	return wyjs;
}
//ready
struct OBRAZ *Szum(struct OBRAZ *sz) {
	struct OBRAZ *wyjs;
	int i, j;
	int r;
	wyjs = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));
	wyjs->y = sz->y;
	wyjs->x = sz->x;
	wyjs->skala = sz->skala;


	wyjs->pixel = (int**)calloc(wyjs->y, sizeof(int*));
	for (i = 0; i<wyjs->y; i++) {
		wyjs->pixel[i] = (int*)calloc(wyjs->x, sizeof(int));
	}


	for (j = 0; j<wyjs->y; j++) {
		for (i = 0; i<wyjs->x; i++) {
			wyjs->pixel[j][i] = sz->pixel[j][i];
			r = rand() % 4;
			if (r<2)	wyjs->pixel[j][i] = sz->pixel[j][i] + 255;
			else wyjs->pixel[j][i] = sz->pixel[j][i] - 255;
		}
	}

	return wyjs;
}
//ready
struct OBRAZ *Lustro(struct OBRAZ *lu) {
	struct OBRAZ *ul;
	int i, j, wybor;
	ul = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));
	ul->y = lu->y;
	ul->x = lu->x;
	ul->skala = lu->skala;

	//alokacja
	ul->pixel = (int**)calloc(ul->y, sizeof(int*));
	for (i = 0; i<ul->y; i++) {
		ul->pixel[i] = (int*)calloc(ul->x, sizeof(int));
	}
	do {
		printf("podaj wybor lustra\n");
		printf("1- X    2- Y\n");
		scanf("%d", &wybor);
		if (wybor != 1 && wybor != 2) printf("wybrano pozycje spoza MENU\n");
	} while (wybor != 1 && wybor != 2);
	switch (wybor) {
	case 1: {
		//lustro X
		for (j = 0; j < ul->y; j++) {
			for (i = 0; i < ul->x; i++) {
				ul->pixel[j][i] = lu->pixel[j][lu->x - i];
			}
		}
		break;
	}
	case 2: {
		//lustro Y
		for (j = 0; j < ul->y; j++) {
			for (i = 0; i < ul->x; i++) {
				ul->pixel[j][i] = lu->pixel[lu->y - j - 1][i];
			}
		}
		break;
	}
	}
	return ul;
}
//ready
struct OBRAZ *Zoom(struct OBRAZ *zo) {
	struct OBRAZ *oz;
	int i, j, k, g, zoom;
	oz = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	do {
		printf("podaj powiekszenie (potega liczby 2)\n");
		scanf("%d", &zoom);
		if (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16) printf("wybrano pozycje spoza MENU\n");
	} while (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16 && zoom != 32);


	oz->y = (zoom * zo->y);
	oz->x = (zoom * zo->x);
	oz->skala = zo->skala;

	//alokacja
	oz->pixel = (int**)calloc(oz->y, sizeof(int*));
	for (i = 0; i<oz->y; i++) {
		oz->pixel[i] = (int*)calloc(oz->x, sizeof(int));
	}


	for (j = 0; j < zo->y; j++) {
		for (i = 0; i < zo->x; i++) {
			for (k = 0; k < zoom; k++) {
				for (g = 0; g < zoom; g++) {
					oz->pixel[j*zoom + k][i*zoom + g] = zo->pixel[j][i];

				}
			}
		}
	}
	return oz;
}
//ready ale to ten najprostszy
struct OBRAZ *Zoom1(struct OBRAZ *zo) {
	struct OBRAZ *oz;
	int i, j, z, zoom;
	int **okno;
	oz = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	okno = (float**)calloc(3, sizeof(float*));
	for (i = 0; i < 3; i++) {
		okno[i] = (float*)calloc(3, sizeof(float));
	}
	//////////////////////////////////////////

	oz->y = (2 * (zo->y));
	oz->x = (2 * (zo->x));
	oz->skala = zo->skala;

	//alokacja
	oz->pixel = (float**)calloc((oz->y), sizeof(float*));
	for (i = 0; i < oz->y; i++) {
		oz->pixel[i] = (float*)calloc((oz->x), sizeof(float));
	}
	//baza (przepisanie danych pixeli)
	for (j = 0; j < zo->y; j++) {
		for (i = 0; i < zo->x; i++) {
			oz->pixel[j * 2][i * 2] = zo->pixel[j][i];
		}
	}
	//okno1
	for (j = 0; j < oz->y - 2; j = j + 2) {
		for (i = 0; i < oz->x - 2; i = i + 2) {
			okno[0][0] = oz->pixel[j][i];
			okno[0][2] = oz->pixel[j][i + 2];
			okno[2][0] = oz->pixel[j + 2][i];
			okno[2][2] = oz->pixel[j + 2][i + 2];

			oz->pixel[j + 1][i + 1] = (okno[0][0] + okno[0][2] + okno[2][0] + okno[2][2]) / 4;
		}
	}
	//okno2
	for (j = 0; j < oz->y - 2; j = j + 1) {
		if (j % 2 == 0) {
			for (i = 1; i < oz->x - 2; i = i + 2) {
				okno[0][1] = oz->pixel[j][i + 1];
				okno[1][2] = oz->pixel[j + 1][i + 2];
				okno[1][0] = oz->pixel[j + 1][i];
				okno[2][1] = oz->pixel[j + 2][i + 1];

				oz->pixel[j + 1][i + 1] = (okno[0][1] + okno[1][2] + okno[1][0] + okno[2][1]) / 4;
			}
		}
		else {
			for (i = 0; i < oz->x - 2; i = i + 2) {
				okno[0][1] = oz->pixel[j][i + 1];
				okno[1][2] = oz->pixel[j + 1][i + 2];
				okno[1][0] = oz->pixel[j + 1][i];
				okno[2][1] = oz->pixel[j + 2][i + 1];

				oz->pixel[j + 1][i + 1] = (okno[0][1] + okno[1][2] + okno[1][0] + okno[2][1]) / 4;
			}
		}
	}

	//uzupe³nienie krawêdzi
	for (j = 0; j < oz->y; j = j + 2) {
		for (i = 0; i < oz->x + 1; i = i + 2) {
			oz->pixel[j + 1][0] = oz->pixel[j][0];
			oz->pixel[0][i + 1] = oz->pixel[0][i];
		}
	}

	for (j = 0; j < oz->x; j++) {  //poziom ostatni
		oz->pixel[oz->y - 1][j] = oz->pixel[(oz->y - 2)][j];
	}
	for (j = 0; j < oz->y; j++) {   //pion ostatni
		oz->pixel[j][oz->x - 1] = oz->pixel[j][(oz->x - 2)];
	}
	return oz;

}
//ready ten bardziej zaawansowany UŒREDNIAJ¥CY
struct OBRAZ *Zoom2(struct OBRAZ *o) {
	struct OBRAZ *z;

	int i, j, h, k, zoom;
	int **okno;
	z = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	okno = (float**)calloc(3, sizeof(float*));
	for (i = 0; i < 3; i++) {
		okno[i] = (float*)calloc(3, sizeof(float));
	}
	//////////////////////////////////////////

	z->y = (2 * (o->y));
	z->x = (2 * (o->x));
	z->skala = o->skala;

	//alokacja
	z->pixel = (float**)calloc((z->y), sizeof(float*));
	for (i = 0; i < z->y; i++) {
		z->pixel[i] = (float*)calloc((z->x), sizeof(float));
	}
	//baza (przepisanie danych pixeli)
	for (j = 0; j < o->y; j++) {
		for (i = 0; i < o->x; i++) {
			z->pixel[j * 2][i * 2] = o->pixel[j][i];
		}
	}
	//okno1
	for (j = 0; j < z->y - 2; j = j + 2) {
		for (i = 0; i < z->x - 2; i = i + 2) {
			okno[0][0] = z->pixel[j][i];
			okno[0][2] = z->pixel[j][i + 2];
			okno[2][0] = z->pixel[j + 2][i];
			okno[2][2] = z->pixel[j + 2][i + 2];



			//// musi byæ sortowanie
			for (j = 0; j < 3; j++) {
				if (okno[0][0] > okno[0][2])
				{
					k = okno[0][0];
					okno[0][0] = okno[0][2];
					okno[0][2] = k;
				}
				if (okno[0][2] > okno[2][0])
				{
					k = okno[0][2];
					okno[0][2] = okno[2][0];
					okno[2][0] = k;
				}
				if (okno[2][0] > okno[2][2])
				{
					k = okno[2][0];
					okno[2][0] = okno[2][2];
					okno[2][2] = k;
				}
			}


			///////////////////
			z->pixel[j + 1][i + 1] = (okno[0][2] + okno[2][0]) / 2;
		}
	}
	//okno2
	for (j = 0; j < z->y - 2; j = j + 1) {
		if (j % 2 == 0) {
			for (i = 1; i < z->x - 2; i = i + 2) {
				okno[0][1] = z->pixel[j][i + 1];
				okno[1][0] = z->pixel[j + 1][i + 2];
				okno[1][2] = z->pixel[j + 1][i];
				okno[2][1] = z->pixel[j + 2][i + 1];

				/////////////
				for (j = 0; j < 3; j++) {
					if (okno[0][1] > okno[1][0])
					{
						k = okno[0][1];
						okno[0][1] = okno[1][0];
						okno[1][0] = k;
					}
					if (okno[1][0] > okno[1][2])
					{
						k = okno[1][0];
						okno[1][0] = okno[1][2];
						okno[1][2] = k;
					}
					if (okno[1][2] > okno[2][1])
					{
						k = okno[1][2];
						okno[1][2] = okno[2][1];
						okno[2][1] = k;
					}
				}
				/////////////

				z->pixel[j + 1][i + 1] = (okno[1][2] + okno[1][0]) / 2;
			}
		}
		else {
			for (i = 0; i < z->x - 2; i = i + 2) {
				for (j = 0; j < 3; j++) {
					if (okno[0][1] > okno[1][0])
					{
						k = okno[0][1];
						okno[0][1] = okno[1][0];
						okno[1][0] = k;
					}
					if (okno[1][0] > okno[1][2])
					{
						k = okno[1][0];
						okno[1][0] = okno[1][2];
						okno[1][2] = k;
					}
					if (okno[1][2] > okno[2][0])
					{
						k = okno[1][2];
						okno[1][2] = okno[2][0];
						okno[2][0] = k;
					}
				}
				/////////////

				z->pixel[j + 1][i + 1] = (okno[1][2] + okno[1][0]) / 2;
			}
		}
	}

	//uzupe³nienie krawêdzi
	for (j = 0; j < z->y; j = j + 2) {
		for (i = 0; i < z->x + 1; i = i + 2) {
			z->pixel[j + 1][0] = z->pixel[j][0];
			z->pixel[0][i + 1] = z->pixel[0][i];
		}
	}

	for (j = 0; j < z->x; j++) {  //poziom ostatni
		z->pixel[z->y - 1][j] = z->pixel[(z->y - 2)][j];
	}
	for (j = 0; j < z->y; j++) {   //pion ostatni
		z->pixel[j][z->x - 1] = z->pixel[j][(z->x - 2)];
	}

	return z;
}
//ten bardziej zaawansowany MEDIANOWY
struct OBRAZ *Progowanie(struct OBRAZ *przed) {
	struct OBRAZ *po;
	int i, j, prog;
	po = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));
	po->y = przed->y;
	po->x = przed->x;
	po->skala = przed->skala;

	//alokacja
	po->pixel = (int**)calloc(po->y, sizeof(int*));
	for (i = 0; i<po->y; i++) {
		po->pixel[i] = (int*)calloc(po->x, sizeof(int));
	}
	/*
	do {
	printf("podaj wybor lustra\n");
	printf("1- X    2- Y\n");
	scanf("%d", &wybor);
	if (wybor != 1 && wybor != 2) printf("wybrano pozycje spoza MENU\n");
	} while (wybor != 1 && wybor != 2);
	*/
	do {
		printf("podaj prog wedlug ktorego chcesz dokonac progowania( od 0 do %d)\n", po->skala);
		scanf("%d", &prog);
		if (prog > po->skala) printf("wartosc progu spoza przedzialu\n");
	} while (prog > po->skala);

	for (j = 0; j < po->y; j++) {
		for (i = 0; i < po->x; i++) {
			if (przed->pixel[j][i]>prog) po->pixel[j][i] = 0;
			else po->pixel[j][i] = po->skala - 1;
		}
	}

	return po;
}
//ready
struct OBRAZ *Histogram(struct OBRAZ *his) {

	int i, j, k, yorn;
	int **tab;
	tab = (int**)calloc(2, sizeof(int*));
	for (i = 0; i < 2; i++) {
		tab[i] = (int*)calloc(his->skala + 1, sizeof(int));
	}
	for (i = 0; i <= his->skala + 1; i++) {
		tab[0][i] = i;
	}
	for (j = 0; j < his->y; j++) {
		for (i = 0; i < his->x; i++) {
			k = his->pixel[j][i];
			tab[1][k] = tab[1][k] + 1;
		}
	}
	printf("czy chcesz wypisac wynik histogramu?\n1.tak\n2.nie\n");
	scanf("%d", &yorn);
	if (yorn == 1) {
		for (i = 0; i <= 255; i++) {		//wypis
			printf("[%d, %d]\n", tab[0][i], tab[1][i]);
		}
	}
	else printf("zrezygnowano z wypisania\n");

	RysujWykres(tab, his->skala + 1, "histogram.html");
	printf("utworzono wykres dostepny w pliku o nazwie 'histogram.html'\n");
	return his;

}
//ready
struct OBRAZ *Obroty(struct OBRAZ *ob) {
	struct OBRAZ *spin;
	int i, j, wybor;
	spin = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	do {
		printf("podaj jak chcesz obrocic obraz (w prawo)\n (1 - 90 2 - 180 3 - 270)\n");
		scanf("%d", &wybor);
		if (wybor != 1 && wybor != 2 && wybor != 3) printf("wybrano pozycje spoza MENU\n");
	} while (wybor != 1 && wybor != 2 && wybor != 3);

	switch (wybor) {
	case 1: {
		spin->x = ob->y;
		spin->y = ob->x;
		spin->skala = ob->skala;

		spin->pixel = (int**)calloc(spin->y, sizeof(int*));
		for (i = 0; i<spin->y; i++) {
			spin->pixel[i] = (int*)calloc(spin->x, sizeof(int));
		}

		for (j = 0; j < spin->x; j++) {
			for (i = 0; i < spin->y; i++) {
				spin->pixel[i][j] = ob->pixel[ob->y - j - 1][i];
			}
		}
		break;
	}
	case 2: {
		spin->x = ob->x;
		spin->y = ob->y;
		spin->skala = ob->skala;

		spin->pixel = (int**)calloc(spin->y, sizeof(int*));
		for (i = 0; i<spin->y; i++) {
			spin->pixel[i] = (int*)calloc(spin->x, sizeof(int));
		}

		for (j = 0; j < spin->y; j++) {
			for (i = 0; i < spin->x; i++) {
				spin->pixel[j][i] = ob->pixel[ob->y - j - 1][ob->x - i - 1];
			}
		}
		break;
	}
	case 3: {
		spin->x = ob->y;
		spin->y = ob->x;
		spin->skala = ob->skala;

		spin->pixel = (int**)calloc(spin->y, sizeof(int*));
		for (i = 0; i<spin->y; i++) {
			spin->pixel[i] = (int*)calloc(spin->x, sizeof(int));
		}

		for (j = 0; j < spin->x; j++) {
			for (i = 0; i < spin->y; i++) {
				spin->pixel[i][j] = ob->pixel[j][ob->x - i];
			}
		}
		break;
	}
	}
	return spin;
}
//ready
struct OBRAZ *Polacz(struct OBRAZ *sk) {
	struct OBRAZ *wyjt;
	int i, j, k, h, ile, ilex, iley, jak;
	wyjt = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	do {
		printf("podaj ile obrazow chcesz polaczyc w pionie\n");
		scanf("%d", &iley);

		printf("podaj ile obrazow chcesz polaczyc w poziomie\n");
		scanf("%d", &ilex);
		if (iley == 0 || ilex == 0) printf("podaj inna wartosc niz 0\n");
	} while (iley == 0 || ilex == 0);

	wyjt->y = iley * sk->y;
	wyjt->x = ilex * (sk->x);
	wyjt->skala = sk->skala;

	wyjt->pixel = (int**)calloc(wyjt->y, sizeof(int*));
	for (i = 0; i<wyjt->y; i++) {
		wyjt->pixel[i] = (int*)calloc(wyjt->x, sizeof(int));
	}

	for (i = 0; i<sk->x; i++) {
		for (h = 0; h < ilex; h++) {
			for (k = 0; k < iley; k++) {
				for (j = 0; j < sk->y; j++) {
					wyjt->pixel[j + k*sk->y][i + h*sk->x] = sk->pixel[j][i];
				}
			}
		}
	}

	return wyjt;
}
//ready
struct OBRAZ *Filtr(struct OBRAZ *fil) {   //srednia
	struct OBRAZ *lif;
	int i, j;
	lif = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));
	lif->x = fil->x;
	lif->y = fil->y;
	lif->skala = fil->skala;

	lif->pixel = (float**)calloc(lif->y, sizeof(float*));
	for (i = 0; i < lif->y; i++) {
		lif->pixel[i] = (float*)calloc(lif->x, sizeof(float));
	}
	for (j = 0; j < lif->y; j++) {
		for (i = 0; i < lif->x; i++) {
			if (i == 0 || i == (lif->x) - 1 || j == 0 || j == (lif->y) - 1)
			{
				lif->pixel[j][i] = fil->pixel[j][i];
			}
			else
			{
				lif->pixel[j][i] = (fil->pixel[j - 1][i + 1] + fil->pixel[j][i + 1] + fil->pixel[j + 1][i + 1] + fil->pixel[j - 1][i] + fil->pixel[j + 1][i] + fil->pixel[j - 1][i - 1] + fil->pixel[j][i - 1] + fil->pixel[j + 1][i - 1]) / 8;
			}
		}
	}
	return lif;
}
//ready SREDNIA
void RysujWykres(int **dane, int l_linii, char *nazwa) {
	FILE *Wsk_do_pliku;
	int i;

	Wsk_do_pliku = fopen(nazwa, "w");

	fprintf(Wsk_do_pliku, "<html>\n");
	fprintf(Wsk_do_pliku, "<head>\n");
	fprintf(Wsk_do_pliku, "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
	fprintf(Wsk_do_pliku, "<script type=\"text/javascript\">\n");
	fprintf(Wsk_do_pliku, "google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
	fprintf(Wsk_do_pliku, "google.setOnLoadCallback(drawChart);\n");
	fprintf(Wsk_do_pliku, "function drawChart() {\n");
	fprintf(Wsk_do_pliku, "var data = google.visualization.arrayToDataTable([\n");
	fprintf(Wsk_do_pliku, "['skala', 'ilosc']");


	for (i = 0; i<l_linii; i++) {
		fprintf(Wsk_do_pliku, ",\n[%d, %d]", dane[0][i], dane[1][i]);   //przekazanie danych na wykres
	}

	fprintf(Wsk_do_pliku, "\n]);\n");

	fprintf(Wsk_do_pliku, "var options = {\n");
	fprintf(Wsk_do_pliku, "title: 'Histogram'\n");
	fprintf(Wsk_do_pliku, "};\n");
	fprintf(Wsk_do_pliku, "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
	fprintf(Wsk_do_pliku, "chart.draw(data, {\n");
	fprintf(Wsk_do_pliku, "colors: ['red']\n");
	fprintf(Wsk_do_pliku, "}\n");
	fprintf(Wsk_do_pliku, ");\n");
	fprintf(Wsk_do_pliku, "}\n");
	fprintf(Wsk_do_pliku, "</script>\n");
	fprintf(Wsk_do_pliku, "</head>\n");
	fprintf(Wsk_do_pliku, "<body>\n");
	fprintf(Wsk_do_pliku, "<div id=\"chart_div\" style=\"width: 1280px; height: 720px;\"></div>\n");
	fprintf(Wsk_do_pliku, "</body>\n");
	fprintf(Wsk_do_pliku, "</html>\n");

	fclose(Wsk_do_pliku);
}
//ready DO HISTOGRAMU