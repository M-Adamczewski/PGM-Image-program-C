#pragma once
#ifndef hed
#define hed


struct PIC {
	int x, y, scale;
	int **pixel;
};

struct PIC *Gradient(int, int, int);
struct PIC *slant(int, int, int);
struct PIC *read_file(char *);
struct PIC *Negatyw(struct PIC*);
struct PIC *bright(struct PIC*, int);
struct PIC *noise(struct PIC*);
struct PIC *mirror(struct PIC*);
struct PIC *Zoom(struct PIC*);
struct PIC *Zoom1(struct PIC*);
struct PIC *Zoom2(struct PIC*);
struct PIC *threshold(struct PIC*);
struct PIC *Histogram(struct PIC*);
struct PIC *rotation(struct PIC*);
struct PIC *Add(struct PIC*);
struct PIC *filter(struct PIC*);
void DrawChart(int **, int, char *);
void Save(struct PIC*);



#endif
