// grille.h
#ifndef GRILLE_H
#define GRILLE_H

#define MAX_SIZE 100

typedef struct
{
    int indice;
    int (*tableau)[5];
} structCaseDevoile;

void afficheGrille(int difficulte, structTab *t);
int getCol(int x);
int getRow(int y);
int estDansTab(structTab t, int x, int y);
void devoileCase(int col, int row, structCaseDevoile *caseDevoile, structTab *t, structTab *tabMask);
void ajouteCaseDevoile(structCaseDevoile *caseDevoile, int x1, int y1, int x2, int y2, int type, structTab *tabMask, int row, int col);
void afficheCaseDevoile(structCaseDevoile *caseDevoile);
void dessineCaseDevoile(structCaseDevoile *caseDevoile, DonneesImageRGB **listeImages);
void initCaseDevoile(structCaseDevoile *caseDevoile, int nbCases);

#endif