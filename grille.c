#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h>  // Pour pouvoir utiliser printf()
#include <math.h>   // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include <string.h>
#include <unistd.h>
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
        if (larg != 700 || haut != 550)
        {
            redimensionneFenetre(700, 550);
        }
        break;
    case 2:
        if (larg != 850 || haut != 700)
        {
            redimensionneFenetre(850, 700);
        }
        break;
    case 3:
        if (larg != 1000 || haut != 850)
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
        return 0;
    }
    else
    {
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

void devoileCase(int col, int row, structCaseDevoile *caseDevoile, structTab *t, structTab *tabMask, structTab *tabDrap, int firstClic, int *peutJouer, int *mort)
{
    if (caseDevoile != NULL && t != NULL && tabMask != NULL && estDansTab(*t, col, row) && tabDrap->tableau[row][col] == 0 && firstClic == 1 && *peutJouer)
    {
        switch (t->tableau[row][col])
        {
        case 0:
            if (estDansTab(*t, col - 1, row - 1) && t->tableau[row - 1][col - 1] == 0 && tabMask->tableau[row - 1][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, (row - 1) * 30 + 50, (col - 1) * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col - 1], tabMask, row - 1, col - 1);
                devoileCase(col - 1, row - 1, caseDevoile, t, tabMask, tabDrap, firstClic, peutJouer, mort);
            }

            if (estDansTab(*t, col, row - 1) && t->tableau[row - 1][col] == 0 && tabMask->tableau[row - 1][col] == 0)
            {
                ajouteCaseDevoile(caseDevoile, col * 30 + 50, (row - 1) * 30 + 50, col * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col], tabMask, row - 1, col);
                devoileCase(col, row - 1, caseDevoile, t, tabMask, tabDrap, firstClic, peutJouer, mort);
            }

            if (estDansTab(*t, col + 1, row - 1) && t->tableau[row - 1][col + 1] == 0 && tabMask->tableau[row - 1][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, (row - 1) * 30 + 50, (col + 1) * 30 + 80, (row - 1) * 30 + 80, t->tableau[row - 1][col + 1], tabMask, row - 1, col + 1);
                devoileCase(col + 1, row - 1, caseDevoile, t, tabMask, tabDrap, firstClic, peutJouer, mort);
            }

            if (estDansTab(*t, col - 1, row) && t->tableau[row][col - 1] == 0 && tabMask->tableau[row][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, row * 30 + 50, (col - 1) * 30 + 80, row * 30 + 80, t->tableau[row][col - 1], tabMask, row, col - 1);
                devoileCase(col - 1, row, caseDevoile, t, tabMask, tabDrap, firstClic, peutJouer, mort);
            }

            if (estDansTab(*t, col + 1, row) && t->tableau[row][col + 1] == 0 && tabMask->tableau[row][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, row * 30 + 50, (col + 1) * 30 + 80, row * 30 + 80, t->tableau[row][col + 1], tabMask, row, col + 1);
                devoileCase(col + 1, row, caseDevoile, t, tabMask, tabDrap, firstClic, peutJouer, mort);
            }

            if (estDansTab(*t, col - 1, row + 1) && t->tableau[row + 1][col - 1] == 0 && tabMask->tableau[row + 1][col - 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, (row + 1) * 30 + 50, (col - 1) * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col - 1], tabMask, row + 1, col - 1);
                devoileCase(col - 1, row + 1, caseDevoile, t, tabMask, tabDrap, firstClic, peutJouer, mort);
            }

            if (estDansTab(*t, col, row + 1) && t->tableau[row + 1][col] == 0 && tabMask->tableau[row + 1][col] == 0)
            {
                ajouteCaseDevoile(caseDevoile, col * 30 + 50, (row + 1) * 30 + 50, col * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col], tabMask, row + 1, col);
                devoileCase(col, row + 1, caseDevoile, t, tabMask, tabDrap, firstClic, peutJouer, mort);
            }

            if (estDansTab(*t, col + 1, row + 1) && t->tableau[row + 1][col + 1] == 0 && tabMask->tableau[row + 1][col + 1] == 0)
            {
                ajouteCaseDevoile(caseDevoile, (col + 1) * 30 + 50, (row + 1) * 30 + 50, (col + 1) * 30 + 80, (row + 1) * 30 + 80, t->tableau[row + 1][col + 1], tabMask, row + 1, col + 1);
                devoileCase(col + 1, row + 1, caseDevoile, t, tabMask, tabDrap, firstClic, peutJouer, mort);
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
            perdre(t, tabMask, tabDrap, caseDevoile, firstClic);
            *peutJouer = 0;
            *mort = 1;
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

int reloadDifficulte(int difficulte, structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, bool *firstClic, int *drapeauxActuels, int *totalDrapeaux, int *debutPartie, int *mort)
{
    *firstClic = 0;
    *t = creeTab(difficulte);
    *tabMask = creeTabMask(*t);
    *tabDrap = creeTabMask(*t);
    initDrap(*t, drapeauxActuels, totalDrapeaux);
    *debutPartie = time(NULL);
    *mort = 0;
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

int choisirDifficulte(int difficulte, structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, bool *firstClic, int *drapeauxActuels, int *totalDrapeaux, int *debutPartie, int *mort)
{
    switch (difficulte)
    {
    case 1:
        if (firstClic && abscisseSouris() > 485 && abscisseSouris() < 580 && ordonneeSouris() > 220 && ordonneeSouris() < 290)
        {
            difficulte = reloadDifficulte(2, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
        }
        if (firstClic && abscisseSouris() > 590 && abscisseSouris() < 680 && ordonneeSouris() > 220 && ordonneeSouris() < 290)
        {
            difficulte = reloadDifficulte(3, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
        }
        break;
    case 2:
        if (firstClic && abscisseSouris() > 545 && abscisseSouris() < 635 && ordonneeSouris() > 370 && ordonneeSouris() < 430)
        {
            difficulte = reloadDifficulte(1, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
        }
        if (firstClic && abscisseSouris() > 735 && abscisseSouris() < 830 && ordonneeSouris() > 370 && ordonneeSouris() < 430)
        {
            difficulte = reloadDifficulte(3, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
        }
        break;
    case 3:
        if (abscisseSouris() > 695 && abscisseSouris() < 785 && ordonneeSouris() > 510 && ordonneeSouris() < 570)
        {
            difficulte = reloadDifficulte(1, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
        }
        if (abscisseSouris() > 790 && abscisseSouris() < 880 && ordonneeSouris() > 510 && ordonneeSouris() < 570)
        {
            difficulte = reloadDifficulte(2, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
        }
        break;

    default:
        break;
    }
    return difficulte;
}

void afficheDrap(int drapeauxActuels, int totalDrapeaux, int firstClic, DonneesImageRGB **listeImages)
{
    static char chnDrap[100] = "";
    static char chnDrapTot[100] = "";
    if (firstClic)
    {
        ecrisImage(0, hauteurFenetre() - 40, 40, 40, listeImages[11]->donneesRGB);
        couleurCourante(0, 0, 0);
        epaisseurDeTrait(1);
        sprintf(chnDrap, "%d", drapeauxActuels);
        afficheChaine(chnDrap, 30, 60, hauteurFenetre() - 40);
        afficheChaine("/", 30, 100, hauteurFenetre() - 40);
        sprintf(chnDrapTot, "%d", totalDrapeaux);
        afficheChaine(chnDrapTot, 30, 125, hauteurFenetre() - 40);
    }
    else
    {
        strcpy(chnDrap, "");
        strcpy(chnDrapTot, "");
    }
}

void afficheTemps(int debutPartie)
{
    int tempsEcoule = (int)difftime(time(NULL), debutPartie);
    char ch[50];
    sprintf(ch, "Temps : %d s", tempsEcoule);
    couleurCourante(0, 0, 0);
    afficheChaine(ch, 20, largeurFenetre() / 3, hauteurFenetre() - 30);
}

void rejouer(int difficulte, structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, bool *firstClic, int *drapeauxActuels, int *totalDrapeaux, int *debutPartie, int *mort)
{

    if (difficulte == 1 && firstClic && abscisseSouris() > 370 && abscisseSouris() < 680 && ordonneeSouris() > 410 && ordonneeSouris() < 490)
    {

        reloadDifficulte(difficulte, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
    }
    if (difficulte == 2 && firstClic && abscisseSouris() > 520 && abscisseSouris() < 830 && ordonneeSouris() > 550 && ordonneeSouris() < 650)
    {

        reloadDifficulte(difficulte, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
    }
    if (difficulte == 3 && firstClic && abscisseSouris() > 670 && abscisseSouris() < 980 && ordonneeSouris() > 700 && ordonneeSouris() < 800)
    {

        reloadDifficulte(difficulte, t, tabMask, tabDrap, caseDevoile, firstClic, drapeauxActuels, totalDrapeaux, debutPartie, mort);
    }
}

void devoileBombes(structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, int firstClic)
{
    for (int i = 0; i < t->rows; i++)
    {
        for (int j = 0; j < t->cols; j++)
        {
            if (t->tableau[i][j] == 9)
            {
                ajouteCaseDevoile(caseDevoile, j * 30 + 50, i * 30 + 50, j * 30 + 80, i * 30 + 80, 9, tabMask, i, j);
            }
        }
    }
}

void perdre(structTab *t, structTab *tabMask, structTab *tabDrap, structCaseDevoile *caseDevoile, int firstClic)
{
    devoileBombes(t, tabMask, tabDrap, caseDevoile, firstClic);
}

void afficheMort(int mort, int difficulte, DonneesImageRGB **listeAssets)
{
    if (mort)
    {
        switch (difficulte)
        {
        case 1:
            ecrisImage(largeurFenetre() / 2 - 250, hauteurFenetre() / 2 - 70, listeAssets[3]->largeurImage, listeAssets[3]->hauteurImage, listeAssets[3]->donneesRGB);
            break;
        case 2:
            ecrisImage(largeurFenetre() / 2 - 300, hauteurFenetre() / 2 - 70, listeAssets[4]->largeurImage, listeAssets[4]->hauteurImage, listeAssets[4]->donneesRGB);
            break;
        case 3:
            ecrisImage(largeurFenetre() / 2 - 350, hauteurFenetre() / 2 - 150, listeAssets[5]->largeurImage, listeAssets[5]->hauteurImage, listeAssets[5]->donneesRGB);
            break;

        default:
            break;
        }
    }
}

int gagne(int drapeauxActuels, int totalDrapeaux, structTab t, structTab tabDrap)
{
    if (totalDrapeaux != 0 && drapeauxActuels == totalDrapeaux)
    {
        for (int i = 0; i < tabDrap.rows; i++)
        {
            for (int j = 0; j < tabDrap.cols; j++)
            {
                if (tabDrap.tableau[i][j] == 1 && t.tableau[i][j] != 9)
                {
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}

void afficheGagne(int drapeauxActuels, int totalDrapeaux, structTab t, structTab tabDrap, int difficulte, DonneesImageRGB **listeAssets, int *peutJouer)
{
    if (gagne(drapeauxActuels, totalDrapeaux, t, tabDrap) == 1)
    {
        switch (difficulte)
        {
        case 1:
            ecrisImage(largeurFenetre() / 2 - 250, hauteurFenetre() / 2 - 70, listeAssets[6]->largeurImage, listeAssets[6]->hauteurImage, listeAssets[6]->donneesRGB);
            break;
        case 2:
            ecrisImage(largeurFenetre() / 2 - 300, hauteurFenetre() / 2 - 70, listeAssets[7]->largeurImage, listeAssets[7]->hauteurImage, listeAssets[7]->donneesRGB);
            break;
        case 3:
            ecrisImage(largeurFenetre() / 2 - 350, hauteurFenetre() / 2 - 150, listeAssets[8]->largeurImage, listeAssets[8]->hauteurImage, listeAssets[8]->donneesRGB);
            break;

        default:
            break;
        }
        *peutJouer = 1;
    }
}