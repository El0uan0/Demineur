#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h>  // Pour pouvoir utiliser printf()
#include <math.h>   // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "GFXLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXLib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "tableau.h"
#include "images.h"
#include "grille.h"

void afficheGrille(int difficulte, structTab *t)
{
    effaceFenetre(211, 235, 248);
    int larg = largeurFenetre();
    int haut = hauteurFenetre();
    switch (difficulte)
    {
    case 1:
        if (larg != 400 || haut != 550)
        {
            redimensionneFenetre(700, 550);
        }
        break;
    case 2:
        if (larg != 550 || haut != 700)
        {
            redimensionneFenetre(850, 700);
        }
        break;
    case 3:
        if (larg != 700 || haut != 850)
        {
            redimensionneFenetre(1000, 850);
        }
        break;
    }
    // Dessine les carrés (cases)
    couleurCourante(200, 206, 172);
    int x1 = 50, y1 = 50, x2 = 80, y2 = 80;
    for (int i = 0; i < t->rows; ++i)
    {
        for (int j = 0; j < t->cols; ++j)
        {
            rectangle(x1, y1, x2, y2);
            x1 += 30, x2 += 30;
        }
        x1 = 50, x2 = 80;
        y1 += 30, y2 += 30;
    }

    couleurCourante(0, 0, 0); // Dessine les lignes pour démarquer les cases
    x1 = 50, y1 = 50;
    for (int i = 0; i < t->cols + 1; ++i)
    {
        ligne(x1, y1, x1, hauteurFenetre() - 50);
        x1 += 30;
    }
    x1 = 50, y1 = 50;
    for (int i = 0; i < t->rows + 1; ++i)
    {
        ligne(x1, y1, largeurFenetre() - 350, y1);
        y1 += 30;
    }
}

int getCol(int x)
{
    if (x < largeurFenetre() - 350 && x > 50)
    {

        // printf("Col : %d\n", (x - 50) / 30);
        return (x - 50) / 30;
    }
    else
    {
        return -1;
    }
}

int getRow(int y)
{

    if (y < hauteurFenetre() - 50 && y > 50)
    {
        // printf("Ligne : %d\n", (y - 50) / 30);
        return (y - 50) / 30;
    }
    else
    {
        return -1;
    }
}

int estDansTab(structTab t, int x, int y)
{
    if (x <= -1 || y <= -1 || x >= t.cols || y >= t.rows)
    {
        // printf("Pas sur une case\n");
        return 0;
    }
    else
    {
        // printf("%d\n", t.tableau[y - 1][x - 1]);
        return 1;
    }
}

void initCaseDevoile(structCaseDevoile *caseDevoile, int nbCases)
{
    caseDevoile->indice = 0;
    caseDevoile->tableau = (int(*)[5])malloc(nbCases * sizeof(int[5]));
}

void ajouteCaseDevoile(structCaseDevoile *caseDevoile, int x1, int y1, int x2, int y2, int type, structTab *tabMask, int row, int col)
{
    caseDevoile->tableau[caseDevoile->indice][0] = x1;
    caseDevoile->tableau[caseDevoile->indice][1] = y1;
    caseDevoile->tableau[caseDevoile->indice][2] = x2;
    caseDevoile->tableau[caseDevoile->indice][3] = y2;
    caseDevoile->tableau[caseDevoile->indice][4] = type;
    caseDevoile->indice += 1;
    tabMask->tableau[row][col] = 1;
}

void devoileCase(int col, int row, structCaseDevoile *caseDevoile, structTab *t, structTab *tabMask, structTab *tabDrap, int firstClic)
{
    if (caseDevoile != NULL && t != NULL && tabMask != NULL && etatBoutonSouris() == GaucheAppuye && estDansTab(*t, col, row) && tabDrap->tableau[row][col] == 0 && firstClic == 1)
    {
        switch (t->tableau[row][col])
        {
        case 0:
            if (estDansTab(*t, col - 1, row - 1) && t->tableau[row - 1][col - 1] == 0 && tabMask->tableau[row - 1][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, (row - 1) * 30 + 50, (col - 1) * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col - 1], tabMask, row - 1, col - 1);
                devoileCase(col - 1, row - 1, caseDevoile, t, tabMask, tabDrap, firstClic);
            }

            if (estDansTab(*t, col, row - 1) && t->tableau[row - 1][col] == 0 && tabMask->tableau[row - 1][col] == 0)
            {
                ajouteCaseDevoile(caseDevoile, col * 30 + 50, (row - 1) * 30 + 50, col * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col], tabMask, row - 1, col);
                devoileCase(col, row - 1, caseDevoile, t, tabMask, tabDrap, firstClic);
            }

            if (estDansTab(*t, col + 1, row - 1) && t->tableau[row - 1][col + 1] == 0 && tabMask->tableau[row - 1][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, (row - 1) * 30 + 50, (col + 1) * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col + 1], tabMask, row - 1, col + 1);
                devoileCase(col + 1, row - 1, caseDevoile, t, tabMask, tabDrap, firstClic);
            }

            if (estDansTab(*t, col - 1, row) && t->tableau[row][col - 1] == 0 && tabMask->tableau[row][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, row * 30 + 50, (col - 1) * 30 + 80, row * 30 + 80, t->tableau[row][col - 1], tabMask, row, col - 1);
                devoileCase(col - 1, row, caseDevoile, t, tabMask, tabDrap, firstClic);
            }

            if (estDansTab(*t, col + 1, row) && t->tableau[row][col + 1] == 0 && tabMask->tableau[row][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, row * 30 + 50, (col + 1) * 30 + 80, row * 30 + 80, t->tableau[row][col + 1], tabMask, row, col + 1);
                devoileCase(col + 1, row, caseDevoile, t, tabMask, tabDrap, firstClic);
            }

            if (estDansTab(*t, col - 1, row + 1) && t->tableau[row + 1][col - 1] == 0 && tabMask->tableau[row + 1][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, (row + 1) * 30 + 50, (col - 1) * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col - 1], tabMask, row + 1, col - 1);
                devoileCase(col - 1, row + 1, caseDevoile, t, tabMask, tabDrap, firstClic);
            }

            if (estDansTab(*t, col, row + 1) && t->tableau[row + 1][col] == 0 && tabMask->tableau[row + 1][col] == 0)
            {
                ajouteCaseDevoile(caseDevoile, col * 30 + 50, (row + 1) * 30 + 50, col * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col], tabMask, row + 1, col);
                devoileCase(col, row + 1, caseDevoile, t, tabMask, tabDrap, firstClic);
            }

            if (estDansTab(*t, col + 1, row + 1) && t->tableau[row + 1][col + 1] == 0 && tabMask->tableau[row + 1][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, (row + 1) * 30 + 50, (col + 1) * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col + 1], tabMask, row + 1, col + 1);
                devoileCase(col + 1, row + 1, caseDevoile, t, tabMask, tabDrap, firstClic);
            }
            if (estDansTab(*t, col - 1, row - 1) && tabMask->tableau[row - 1][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, (row - 1) * 30 + 50, (col - 1) * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col - 1], tabMask, row - 1, col - 1);
            }

            if (estDansTab(*t, col, row - 1) && tabMask->tableau[row - 1][col] == 0)
            {
                ajouteCaseDevoile(caseDevoile, col * 30 + 50, (row - 1) * 30 + 50, col * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col], tabMask, row - 1, col);
            }

            if (estDansTab(*t, col + 1, row - 1) && tabMask->tableau[row - 1][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, (row - 1) * 30 + 50, (col + 1) * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col + 1], tabMask, row - 1, col + 1);
            }

            if (estDansTab(*t, col - 1, row) && tabMask->tableau[row][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, row * 30 + 50, (col - 1) * 30 + 80, row * 30 + 80, t->tableau[row][col - 1], tabMask, row, col - 1);
            }

            if (estDansTab(*t, col + 1, row) && tabMask->tableau[row][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, row * 30 + 50, (col + 1) * 30 + 80, row * 30 + 80, t->tableau[row][col + 1], tabMask, row, col + 1);
            }

            if (estDansTab(*t, col - 1, row + 1) && tabMask->tableau[row + 1][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, (row + 1) * 30 + 50, (col - 1) * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col - 1], tabMask, row + 1, col - 1);
            }

            if (estDansTab(*t, col, row + 1) && tabMask->tableau[row + 1][col] == 0)
            {
                ajouteCaseDevoile(caseDevoile, col * 30 + 50, (row + 1) * 30 + 50, col * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col], tabMask, row + 1, col);
            }

            if (estDansTab(*t, col + 1, row + 1) && tabMask->tableau[row + 1][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, (row + 1) * 30 + 50, (col + 1) * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col + 1], tabMask, row + 1, col + 1);
            }
            break;
        case 9:
            break;
        default:
            break;
        }
        ajouteCaseDevoile(caseDevoile, col * 30 + 50, row * 30 + 50, col * 30 + 80, row * 30 + 80, t->tableau[row][col], tabMask, row, col);
    }
}

void dessineCaseDevoile(structCaseDevoile *caseDevoile, DonneesImageRGB **listeImages)
{
    static unsigned char *donnees = NULL;

    for (int i = 0; i < caseDevoile->indice; i++)
    {
        int x1 = caseDevoile->tableau[i][0];
        int y1 = caseDevoile->tableau[i][1];
        int y2 = caseDevoile->tableau[i][3];
        int val = caseDevoile->tableau[i][4];

        switch (val)
        {
        case 0:
            donnees = listeImages[0]->donneesRGB;
            break;
        case 1:
            donnees = listeImages[1]->donneesRGB;
            break;
        case 2:
            donnees = listeImages[2]->donneesRGB;
            break;
        case 3:
            donnees = listeImages[3]->donneesRGB;
            break;
        case 4:
            donnees = listeImages[4]->donneesRGB;
            break;
        case 5:
            donnees = listeImages[5]->donneesRGB;
            break;
        case 6:
            donnees = listeImages[6]->donneesRGB;
            break;
        case 7:
            donnees = listeImages[7]->donneesRGB;
            break;
        case 8:
            donnees = listeImages[8]->donneesRGB;
            break;
        case 9:
            donnees = listeImages[9]->donneesRGB;
            break;
        default:
            donnees = listeImages[0]->donneesRGB;
            break;
        }

        if (y2 != 0 && donnees != NULL)
        {
            ecrisImage(x1, y1, 30, 30, donnees);
        }
        else
        {
            break;
        }
    }
}

void dessineDrap(structTab tabDrap, DonneesImageRGB **listeImages)
{
    for (int i = 0; i < tabDrap.rows; i++)
    {
        for (int j = 0; j < tabDrap.cols; j++)
        {
            if (tabDrap.tableau[i][j] == 1)
            {
                ecrisImage(j * 30 + 50, i * 30 + 50, 30, 30, listeImages[10]->donneesRGB);
            }
        }
    }
}

int reloadDifficulte(int difficulte, structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, bool *firstClic, int *drapeauxActuels, int *totalDrapeaux)
{
    *firstClic = 0;
    *t = creeTab(difficulte);
    *tabMask = creeTabMask(*t);
    *tabDrap = creeTabMask(*t);
    initDrap(*t, drapeauxActuels, totalDrapeaux);
    for (int i = 0; i < t->cols * t->rows; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            caseDevoile->tableau[i][j] = 0;
        }
    }
    switch (difficulte)
    {
    case 1:
        redimensionneFenetre(700, 550);
        return 1;
        break;
    case 2:
        redimensionneFenetre(850, 700);
        return 2;
        break;
    case 3:
        redimensionneFenetre(1000, 850);
        return 3;
        break;
    default:
        break;
    }
    return 0;
}

int choisirDifficulte(int difficulte, structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, bool *firstClic, int *drapeauxActuels, int *totalDrapeaux)
{
    switch (difficulte)
    {
    case 1:
        if (firstClic && abscisseSouris() > 470 && abscisseSouris() < 545 && ordonneeSouris() > 270 && ordonneeSouris() < 330)
        {
            difficulte = reloadDifficulte(2, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux);
        }
        if (firstClic && abscisseSouris() > 550 && abscisseSouris() < 625 && ordonneeSouris() > 270 && ordonneeSouris() < 330)
        {
            difficulte = reloadDifficulte(3, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux);
        }
        break;
    case 2:
        if (firstClic && abscisseSouris() > 545 && abscisseSouris() < 635 && ordonneeSouris() > 390 && ordonneeSouris() < 450)
        {
            difficulte = reloadDifficulte(1, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux);
        }
        if (firstClic && abscisseSouris() > 735 && abscisseSouris() < 830 && ordonneeSouris() > 390 && ordonneeSouris() < 450)
        {
            difficulte = reloadDifficulte(3, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux);
        }
        break;
    case 3:
        if (abscisseSouris() > 695 && abscisseSouris() < 785 && ordonneeSouris() > 538 && ordonneeSouris() < 600)
        {
            difficulte = reloadDifficulte(1, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux);
        }
        if (abscisseSouris() > 790 && abscisseSouris() < 880 && ordonneeSouris() > 538 && ordonneeSouris() < 600)
        {
            difficulte = reloadDifficulte(2, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux);
        }
        break;

    default:
        break;
    }
    return difficulte;
}
