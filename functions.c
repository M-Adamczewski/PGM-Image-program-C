#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "hed.h"


struct PIC *Gradient(int width, int height, int gray_scale) {

	struct PIC *pointer;
	int i, j;


	pointer = (struct PIC*)malloc(sizeof(struct PIC));

	pointer->x = width;
	pointer->y = height;
	pointer->scale = gray_scale;
	pointer->pixel = (int**)calloc(pointer->x, sizeof(int*));
	for (i = 0; i<pointer->x; i++) {
		pointer->pixel[i] = (int*)calloc(pointer->y, sizeof(int));
	}

	for (i = 0; i<pointer->x; i++) {

		for (j = 0; j<pointer->y; j++) {
			pointer->pixel[i][j] = j;
		}
	}
	return pointer;
}
//niepotrzebne ale ready
void Save(struct PIC *ready_pic) {
	int i, j;

	FILE *point;

	point = fopen("nowy_picture.pgm", "w");
	fprintf(point, "%s\n", "P2");
	fprintf(point, "%s\n", "# komentarz");
	fprintf(point, "%d %d\n", ready_pic->x, ready_pic->y);
	fprintf(point, "%d\n", ready_pic->scale);

	for (j = 0; j<ready_pic->y; j++) {
		for (i = 0; i<ready_pic->x; i++) {
			fprintf(point, "%d ", ready_pic->pixel[j][i]);
		}
		fprintf(point, "\n");
	}
	fclose(point);
}
//ready
struct PIC *slant(int width, int height, int gray_scale) {

	struct PIC *pointer;
	int i, j;


	pointer = (struct PIC*)malloc(sizeof(struct PIC));

	pointer->x = width;
	pointer->y = height;
	pointer->scale = gray_scale;
	pointer->pixel = (int**)calloc(pointer->x, sizeof(int*));
	for (i = 0; i<pointer->x; i++) {
		pointer->pixel[i] = (int*)calloc(pointer->y, sizeof(int));
	}

	for (i = 0; i<pointer->x; i++) {
		for (j = 0; j<pointer->y; j++) {

			pointer->pixel[j][i] = (i + j) / 2;
		}
	}
	return pointer;
}
//ready ale po co
struct PIC *read_file(char *file_name) {
	int i, j, s, w, sz;
	struct PIC *pointer;
	char bufor[100];
	FILE *point;

	point = fopen(file_name, "r");
	if (point == NULL)
	{
		struct PIC *picture;
		printf("Nie udalo sie otworzyc pliku, stworz wlasny, gradient\n podaj szerokosc\n");
		scanf("%d", &s);
		printf("podaj wysokosc\n");
		scanf("%d", &w);
		printf("podaj skale szarosci\n");
		scanf("%d", &sz);
		picture = Gradient(s, w, sz);
		Save(picture);
		/*	printf("program b�dzie pracowa� na pliku 001.pgm\n");
		nazwa = "001.pgm";
		point = fopen(nazwa, "r");
		fgets(bufor, 100, point);
		fgets(bufor, 100, point);

		pointer = (struct PIC*)malloc(sizeof(struct PIC));
		//skanowanie parametr�w z pocz�tku pliku
		fscanf(point, "%d%d%d", &pointer->x, &pointer->y, &pointer->scale);
		//alokacja
		pointer->pixel = (int**)calloc(pointer->y, sizeof(int*));
		for (i = 0; i < pointer->y; i++) {
		pointer->pixel[i] = (int*)calloc(pointer->x, sizeof(int));
		}

		//wczytanie
		for (j = 0; j < pointer->y; j++) {
		for (i = 0; i < pointer->x; i++) {
		fscanf(point, "%d", &pointer->pixel[j][i]);
		}
		}

		fclose(point);
		return pointer;
		*/
	}




	else {
		fgets(bufor, 100, point);
		fgets(bufor, 100, point);

		pointer = (struct PIC*)malloc(sizeof(struct PIC));
		//skanowanie parametr�w z pocz�tku pliku
		fscanf(point, "%d%d%d", &pointer->x, &pointer->y, &pointer->scale);
		//alokacja 
		pointer->pixel = (int**)calloc(pointer->y, sizeof(int*));
		for (i = 0; i < pointer->y; i++) {
			pointer->pixel[i] = (int*)calloc(pointer->x, sizeof(int));
		}

		//wczytanie
		for (j = 0; j < pointer->y; j++) {
			for (i = 0; i < pointer->x; i++) {
				fscanf(point, "%d", &pointer->pixel[j][i]);
			}
		}

		fclose(point);
		return pointer;
	}
}
//ready
struct PIC *Negatyw(struct PIC *in) {
	struct PIC *out_put;
	int i, j;
	out_put = (struct PIC*)malloc(sizeof(struct PIC));
	out_put->y = in->y;
	out_put->x = in->x;
	out_put->scale = in->scale;


	out_put->pixel = (int**)calloc(out_put->y, sizeof(int*));
	for (i = 0; i<out_put->y; i++) {
		out_put->pixel[i] = (int*)calloc(out_put->x, sizeof(int));
	}


	for (j = 0; j<out_put->y; j++) {
		for (i = 0; i<out_put->x; i++) {
			out_put->pixel[j][i] = out_put->scale - in->pixel[j][i];
		}
	}
	return out_put;
}
//ready
struct PIC *bright(struct PIC *inp, int level) {

	struct PIC *outp;
	int i, j;
	outp = (struct PIC*)malloc(sizeof(struct PIC));
	outp->y = inp->y;
	outp->x = inp->x;
	outp->scale = inp->scale;


	outp->pixel = (int**)calloc(outp->y, sizeof(int*));
	for (i = 0; i<outp->y; i++) {
		outp->pixel[i] = (int*)calloc(outp->x, sizeof(int));
	}


	for (j = 0; j<outp->y; j++) {
		for (i = 0; i<outp->x; i++) {
			outp->pixel[j][i] = inp->pixel[j][i] + level;
			if (outp->pixel[j][i] > outp->scale) //zabezpieczenie
				outp->pixel[j][i] = outp->scale;
			if (outp->pixel[j][i] < 0)
				outp->pixel[j][i] = 0;
		}
	}

	return outp;
}
//ready
struct PIC *noise(struct PIC *sz) {
	struct PIC *outp;
	int i, j;
	int r;
	outp = (struct PIC*)malloc(sizeof(struct PIC));
	outp->y = sz->y;
	outp->x = sz->x;
	outp->scale = sz->scale;


	outp->pixel = (int**)calloc(outp->y, sizeof(int*));
	for (i = 0; i<outp->y; i++) {
		outp->pixel[i] = (int*)calloc(outp->x, sizeof(int));
	}


	for (j = 0; j<outp->y; j++) {
		for (i = 0; i<outp->x; i++) {
			outp->pixel[j][i] = sz->pixel[j][i];
			r = rand() % 4;
			if (r<2)	outp->pixel[j][i] = sz->pixel[j][i] + 255;
			else outp->pixel[j][i] = sz->pixel[j][i] - 255;
		}
	}

	return outp;
}
//ready
struct PIC *mirror(struct PIC *lu) {
	struct PIC *ul;
	int i, j, option;
	ul = (struct PIC*)malloc(sizeof(struct PIC));
	ul->y = lu->y;
	ul->x = lu->x;
	ul->scale = lu->scale;

	//alokacja
	ul->pixel = (int**)calloc(ul->y, sizeof(int*));
	for (i = 0; i<ul->y; i++) {
		ul->pixel[i] = (int*)calloc(ul->x, sizeof(int));
	}
	do {
		printf("podaj wybor lustra\n");
		printf("1- X    2- Y\n");
		scanf("%d", &option);
		if (option != 1 && option != 2) printf("wybrano pozycje spoza MENU\n");
	} while (option != 1 && option != 2);
	switch (option) {
	case 1: {
		//mirror X
		for (j = 0; j < ul->y; j++) {
			for (i = 0; i < ul->x; i++) {
				ul->pixel[j][i] = lu->pixel[j][lu->x - i];
			}
		}
		break;
	}
	case 2: {
		//mirror Y
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
struct PIC *Zoom(struct PIC *zo) {
	struct PIC *oz;
	int i, j, k, g, zoom;
	oz = (struct PIC*)malloc(sizeof(struct PIC));

	do {
		printf("podaj powiekszenie (potega liczby 2)\n");
		scanf("%d", &zoom);
		if (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16) printf("wybrano pozycje spoza MENU\n");
	} while (zoom != 2 && zoom != 4 && zoom != 8 && zoom != 16 && zoom != 32);


	oz->y = (zoom * zo->y);
	oz->x = (zoom * zo->x);
	oz->scale = zo->scale;

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
struct PIC *Zoom1(struct PIC *zo) {
	struct PIC *oz;
	int i, j, z, zoom;
	int **frame;
	oz = (struct PIC*)malloc(sizeof(struct PIC));

	frame = (float**)calloc(3, sizeof(float*));
	for (i = 0; i < 3; i++) {
		frame[i] = (float*)calloc(3, sizeof(float));
	}
	//////////////////////////////////////////

	oz->y = (2 * (zo->y));
	oz->x = (2 * (zo->x));
	oz->scale = zo->scale;

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
	//frame1
	for (j = 0; j < oz->y - 2; j = j + 2) {
		for (i = 0; i < oz->x - 2; i = i + 2) {
			frame[0][0] = oz->pixel[j][i];
			frame[0][2] = oz->pixel[j][i + 2];
			frame[2][0] = oz->pixel[j + 2][i];
			frame[2][2] = oz->pixel[j + 2][i + 2];

			oz->pixel[j + 1][i + 1] = (frame[0][0] + frame[0][2] + frame[2][0] + frame[2][2]) / 4;
		}
	}
	//frame2
	for (j = 0; j < oz->y - 2; j = j + 1) {
		if (j % 2 == 0) {
			for (i = 1; i < oz->x - 2; i = i + 2) {
				frame[0][1] = oz->pixel[j][i + 1];
				frame[1][2] = oz->pixel[j + 1][i + 2];
				frame[1][0] = oz->pixel[j + 1][i];
				frame[2][1] = oz->pixel[j + 2][i + 1];

				oz->pixel[j + 1][i + 1] = (frame[0][1] + frame[1][2] + frame[1][0] + frame[2][1]) / 4;
			}
		}
		else {
			for (i = 0; i < oz->x - 2; i = i + 2) {
				frame[0][1] = oz->pixel[j][i + 1];
				frame[1][2] = oz->pixel[j + 1][i + 2];
				frame[1][0] = oz->pixel[j + 1][i];
				frame[2][1] = oz->pixel[j + 2][i + 1];

				oz->pixel[j + 1][i + 1] = (frame[0][1] + frame[1][2] + frame[1][0] + frame[2][1]) / 4;
			}
		}
	}

	//uzupe�nienie kraw�dzi
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
//ready ten bardziej zaawansowany U�REDNIAJ�CY
struct PIC *Zoom2(struct PIC *o) {
	struct PIC *z;

	int i, j, h, k, zoom;
	int **frame;
	z = (struct PIC*)malloc(sizeof(struct PIC));

	frame = (float**)calloc(3, sizeof(float*));
	for (i = 0; i < 3; i++) {
		frame[i] = (float*)calloc(3, sizeof(float));
	}
	//////////////////////////////////////////

	z->y = (2 * (o->y));
	z->x = (2 * (o->x));
	z->scale = o->scale;

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
	//frame1
	for (j = 0; j < z->y - 2; j = j + 2) {
		for (i = 0; i < z->x - 2; i = i + 2) {
			frame[0][0] = z->pixel[j][i];
			frame[0][2] = z->pixel[j][i + 2];
			frame[2][0] = z->pixel[j + 2][i];
			frame[2][2] = z->pixel[j + 2][i + 2];



			//// musi by� sortowanie
			for (j = 0; j < 3; j++) {
				if (frame[0][0] > frame[0][2])
				{
					k = frame[0][0];
					frame[0][0] = frame[0][2];
					frame[0][2] = k;
				}
				if (frame[0][2] > frame[2][0])
				{
					k = frame[0][2];
					frame[0][2] = frame[2][0];
					frame[2][0] = k;
				}
				if (frame[2][0] > frame[2][2])
				{
					k = frame[2][0];
					frame[2][0] = frame[2][2];
					frame[2][2] = k;
				}
			}


			///////////////////
			z->pixel[j + 1][i + 1] = (frame[0][2] + frame[2][0]) / 2;
		}
	}
	//frame2
	for (j = 0; j < z->y - 2; j = j + 1) {
		if (j % 2 == 0) {
			for (i = 1; i < z->x - 2; i = i + 2) {
				frame[0][1] = z->pixel[j][i + 1];
				frame[1][0] = z->pixel[j + 1][i + 2];
				frame[1][2] = z->pixel[j + 1][i];
				frame[2][1] = z->pixel[j + 2][i + 1];

				/////////////
				for (j = 0; j < 3; j++) {
					if (frame[0][1] > frame[1][0])
					{
						k = frame[0][1];
						frame[0][1] = frame[1][0];
						frame[1][0] = k;
					}
					if (frame[1][0] > frame[1][2])
					{
						k = frame[1][0];
						frame[1][0] = frame[1][2];
						frame[1][2] = k;
					}
					if (frame[1][2] > frame[2][1])
					{
						k = frame[1][2];
						frame[1][2] = frame[2][1];
						frame[2][1] = k;
					}
				}
				/////////////

				z->pixel[j + 1][i + 1] = (frame[1][2] + frame[1][0]) / 2;
			}
		}
		else {
			for (i = 0; i < z->x - 2; i = i + 2) {
				for (j = 0; j < 3; j++) {
					if (frame[0][1] > frame[1][0])
					{
						k = frame[0][1];
						frame[0][1] = frame[1][0];
						frame[1][0] = k;
					}
					if (frame[1][0] > frame[1][2])
					{
						k = frame[1][0];
						frame[1][0] = frame[1][2];
						frame[1][2] = k;
					}
					if (frame[1][2] > frame[2][0])
					{
						k = frame[1][2];
						frame[1][2] = frame[2][0];
						frame[2][0] = k;
					}
				}
				/////////////

				z->pixel[j + 1][i + 1] = (frame[1][2] + frame[1][0]) / 2;
			}
		}
	}

	//uzupe�nienie kraw�dzi
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
struct PIC *threshold(struct PIC *inputt) {
	struct PIC *output;
	int i, j, thr;
	output = (struct PIC*)malloc(sizeof(struct PIC));
	output->y = inputt->y;
	output->x = inputt->x;
	output->scale = inputt->scale;

	//alokacja
	output->pixel = (int**)calloc(output->y, sizeof(int*));
	for (i = 0; i<output->y; i++) {
		output->pixel[i] = (int*)calloc(output->x, sizeof(int));
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
		printf("podaj prog wedlug ktorego chcesz dokonac progowania( od 0 do %d)\n", output->scale);
		scanf("%d", &thr);
		if (thr > output->scale) printf("wartosc progu spoza przedzialu\n");
	} while (thr > output->scale);

	for (j = 0; j < output->y; j++) {
		for (i = 0; i < output->x; i++) {
			if (inputt->pixel[j][i]>thr) output->pixel[j][i] = 0;
			else output->pixel[j][i] = output->scale - 1;
		}
	}

	return output;
}
//ready
struct PIC *Histogram(struct PIC *his) {

	int i, j, k, yorn;
	int **tab;
	tab = (int**)calloc(2, sizeof(int*));
	for (i = 0; i < 2; i++) {
		tab[i] = (int*)calloc(his->scale + 1, sizeof(int));
	}
	for (i = 0; i <= his->scale + 1; i++) {
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

	DrawChart(tab, his->scale + 1, "histogram.html");
	printf("utworzono wykres dostepny w pliku o nazwie 'histogram.html'\n");
	return his;

}
//ready
struct PIC *rotation(struct PIC *ob) {
	struct PIC *spin;
	int i, j, option;
	spin = (struct PIC*)malloc(sizeof(struct PIC));

	do {
		printf("podaj jak chcesz obrocic obraz (w prawo)\n (1 - 90 2 - 180 3 - 270)\n");
		scanf("%d", &option);
		if (option != 1 && option != 2 && option != 3) printf("wybrano pozycje spoza MENU\n");
	} while (option != 1 && option != 2 && option != 3);

	switch (option) {
	case 1: {
		spin->x = ob->y;
		spin->y = ob->x;
		spin->scale = ob->scale;

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
		spin->scale = ob->scale;

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
		spin->scale = ob->scale;

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
struct PIC *Add(struct PIC *sk) {
	struct PIC *out;
	int i, j, k, h, ile, how_much_x, how_much_y, jak;
	out = (struct PIC*)malloc(sizeof(struct PIC));

	do {
		printf("podaj ile obrazow chcesz polaczyc w pionie\n");
		scanf("%d", &how_much_y);

		printf("podaj ile obrazow chcesz polaczyc w poziomie\n");
		scanf("%d", &how_much_x);
		if (how_much_y == 0 || how_much_x == 0) printf("podaj inna wartosc niz 0\n");
	} while (how_much_y == 0 || how_much_x == 0);

	out->y = how_much_y * sk->y;
	out->x = how_much_x * (sk->x);
	out->scale = sk->scale;

	out->pixel = (int**)calloc(out->y, sizeof(int*));
	for (i = 0; i<out->y; i++) {
		out->pixel[i] = (int*)calloc(out->x, sizeof(int));
	}

	for (i = 0; i<sk->x; i++) {
		for (h = 0; h < how_much_x; h++) {
			for (k = 0; k < how_much_y; k++) {
				for (j = 0; j < sk->y; j++) {
					out->pixel[j + k*sk->y][i + h*sk->x] = sk->pixel[j][i];
				}
			}
		}
	}

	return out;
}
//ready
struct PIC *filter(struct PIC *fil) {   //srednia
	struct PIC *lif;
	int i, j;
	lif = (struct PIC*)malloc(sizeof(struct PIC));
	lif->x = fil->x;
	lif->y = fil->y;
	lif->scale = fil->scale;

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
void DrawChart(int **data, int len, char *file_name) {
	FILE *pointer_to_file;
	int i;

	pointer_to_file = fopen(file_name, "w");

	fprintf(pointer_to_file, "<html>\n");
	fprintf(pointer_to_file, "<head>\n");
	fprintf(pointer_to_file, "<script type=\"text/javascript\" src=\"https://www.google.com/jsapi\"></script>\n");
	fprintf(pointer_to_file, "<script type=\"text/javascript\">\n");
	fprintf(pointer_to_file, "google.load(\"visualization\", \"1\", {packages:[\"corechart\"]});\n");
	fprintf(pointer_to_file, "google.setOnLoadCallback(drawChart);\n");
	fprintf(pointer_to_file, "function drawChart() {\n");
	fprintf(pointer_to_file, "var data = google.visualization.arrayToDataTable([\n");
	fprintf(pointer_to_file, "['scale', 'ilosc']");


	for (i = 0; i<len; i++) {
		fprintf(pointer_to_file, ",\n[%d, %d]", data[0][i], data[1][i]);   //przekazanie danych na wykres
	}

	fprintf(pointer_to_file, "\n]);\n");

	fprintf(pointer_to_file, "var options = {\n");
	fprintf(pointer_to_file, "title: 'Histogram'\n");
	fprintf(pointer_to_file, "};\n");
	fprintf(pointer_to_file, "var chart = new google.visualization.LineChart(document.getElementById('chart_div'));\n");
	fprintf(pointer_to_file, "chart.draw(data, {\n");
	fprintf(pointer_to_file, "colors: ['red']\n");
	fprintf(pointer_to_file, "}\n");
	fprintf(pointer_to_file, ");\n");
	fprintf(pointer_to_file, "}\n");
	fprintf(pointer_to_file, "</script>\n");
	fprintf(pointer_to_file, "</head>\n");
	fprintf(pointer_to_file, "<body>\n");
	fprintf(pointer_to_file, "<div id=\"chart_div\" style=\"width: 1280px; height: 720px;\"></div>\n");
	fprintf(pointer_to_file, "</body>\n");
	fprintf(pointer_to_file, "</html>\n");

	fclose(pointer_to_file);
}
//ready DO HISTOGRAMU