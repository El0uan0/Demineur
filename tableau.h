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
void afficheTab(structTab t);
void remplirTabMines(structTab *t);
void remplirTabChiffres(structTab *t);

#endif