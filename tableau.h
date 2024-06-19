// tableau.h
#ifndef TABLEAU_H
#define TABLEAU_H

#define MAX_SIZE 100

typedef struct
{
    int rows;
    int cols;
    int tableau[MAX_SIZE][MAX_SIZE];
} structTab;

structTab creeTab(int difficulty);
structTab creeTabMask(structTab t);
void initDrap(structTab t, int *drapeauxActuels, int *totalDrapeaux);
void afficheTab(structTab t);
void remplirTabMines(structTab *t);
void remplirTabChiffres(structTab *t);
void meursPasAuDebut(int col, int row, structTab *t);

#endif