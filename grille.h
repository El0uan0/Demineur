// grille.h
#ifndef GRILLE_H
#define GRILLE_H

#include "tableau.h"
#include "images.h"

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
void devoileCase(int col, int row, structCaseDevoile *caseDevoile, structTab *t, structTab *tabMask, structTab *tabDrap, int firstclic, int *peutJouer, int *mort);
void ajouteCaseDevoile(structCaseDevoile *caseDevoile, int x1, int y1, int x2, int y2, int type, structTab *tabMask, int row, int col);
void dessineCaseDevoile(structCaseDevoile *caseDevoile, DonneesImageRGB **listeImages);
void initCaseDevoile(structCaseDevoile *caseDevoile, int nbCases);
void dessineDrap(structTab tabDrap, DonneesImageRGB **listeImages);
int reloadDifficulte(int difficulte, structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, bool *firstClic, int *drapeauxActuels, int *totalDrapeaux, int *debutPartie, int *mort);
int choisirDifficulte(int difficulte, structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, bool *firstClic, int *drapeauxActuels, int *totalDrapeaux, int *debutPartie, int *mort);
void afficheDrap(int drapeauxActuels, int totalDrapeaux, int firstClic, DonneesImageRGB **listeImages);
void afficheTemps(int debutPartie);
void rejouer(int difficulte, structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, bool *firstClic, int *drapeauxActuels, int *totalDrapeaux, int *debutPartie, int *mort);
void devoileBombes(structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, int firstClic);
void perdre(structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, int firstClic);
void afficheMort(int mort, int difficulte, DonneesImageRGB **listeAssets);
int gagne(int drapeauxActuels, int totalDrapeaux, structTab t, structTab tabMask);
void afficheGagne(int drapeauxActuels, int totalDrapeaux, structTab t, structTab tabDrap, int difficulte, DonneesImageRGB **listeAssets, int *peutJouer);
#endif