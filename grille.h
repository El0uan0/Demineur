// grille.h
#ifndef GRILLE_H
#define GRILLE_H

#define MAX_SIZE 100

typedef struct
{
    int indice;
    int tableau[1000][4];
} structCaseDevoile;

void afficheGrille(int difficulte, structTab *t);
int getCol(int x);
int getRow(int y);
int getValTab(structTab t, int x, int y);
void devoileCase(int col, int row, structCaseDevoile *caseDevoile);
void afficheCaseDevoile(structCaseDevoile *caseDevoile);
void dessineCaseDevoile(structCaseDevoile *caseDevoile);

#endif