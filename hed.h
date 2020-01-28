#pragma once
#ifndef hed
#define hed


struct OBRAZ {
	int x, y, skala;
	int **pixel;
};

struct OBRAZ *Gradient(int, int, int);
struct OBRAZ *Skos(int, int, int);
struct OBRAZ *Wczytaj(char *);
struct OBRAZ *Negatyw(struct OBRAZ*);
struct OBRAZ *Rozjasnianie(struct OBRAZ*, int);
struct OBRAZ *Szum(struct OBRAZ*);
struct OBRAZ *Lustro(struct OBRAZ*);
struct OBRAZ *Zoom(struct OBRAZ*);
struct OBRAZ *Zoom1(struct OBRAZ*);
struct OBRAZ *Zoom2(struct OBRAZ*);
struct OBRAZ *Progowanie(struct OBRAZ*);
struct OBRAZ *Histogram(struct OBRAZ*);
struct OBRAZ *Obroty(struct OBRAZ*);
struct OBRAZ *Polacz(struct OBRAZ*);
struct OBRAZ *Filtr(struct OBRAZ*);
void RysujWykres(int **, int, char *);
void Zapis(struct OBRAZ*);



#endif
