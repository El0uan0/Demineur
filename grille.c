#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h>  // Pour pouvoir utiliser printf()
#include <math.h>   // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "gfxlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "gfxlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "gfxlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "tableau.h"
#include "grille.h"

void afficheGrille(int difficulte, structTab *t)
{
    srand(time(NULL));
    int larg = largeurFenetre();
    int haut = hauteurFenetre();
    switch (difficulte)
    {
    case 1:
        if (larg != 400 || haut != 550)
        {
            redimensionneFenetre(400, 550);
        }
        break;
    case 2:
        if (larg != 550 || haut != 700)
        {
            redimensionneFenetre(550, 700);
        }
        break;
    case 3:
        if (larg != 700 || haut != 850)
        {
            redimensionneFenetre(700, 850);
        }
        break;
    }
    // Dessine les carrés (cases)
    // couleurCourante(0, 255, 0);
    int x1 = 50, y1 = 50, x2 = 80, y2 = 80;
    for (int i = 0; i < t->rows; ++i)
    {
        for (int j = 0; j < t->cols; ++j)
        {
            switch (t->tableau[i][j])
            {
            case 0:;
                couleurCourante(255, 255, 255);
                break;
            case 9:
                couleurCourante(255, 0, 0);
                break;
            default:
                couleurCourante(0, 255, 0);
                break;
            }
            rectangle(x1, y1, x2, y2);
            x1 += 30, x2 += 30;
        }
        x1 = 50, x2 = 80;
        y1 += 30, y2 += 30;
    }

    couleurCourante(0, 0, 0); // Dessine les lignes pour démarquer les cases
    x1 = 80, y1 = 0;
    for (int i = 0; i < t->cols; ++i)
    {
        ligne(x1, y1, x1, 2 * 30 * t->rows);
        x1 += 30;
    }
    x1 = 0, y1 = 80;
    for (int i = 0; i < t->rows; ++i)
    {
        ligne(x1, y1, 2 * 30 * t->cols, y1);
        y1 += 30;
    }
}

int getCol(int x)
{
    if (x < largeurFenetre() - 50 && x > 50)
    {

        // printf("Col : %d\n", (x - 50) / 30 + 1);
        return (x - 50) / 30 + 1;
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
        // printf("Ligne : %d\n", (y - 50) / 30 + 1);
        return (y - 50) / 30 + 1;
    }
    else
    {
        return -1;
    }
}

int getValTab(structTab t, int x, int y)
{
    if (x == -1 || y == -1)
    {
        printf("Pas sur une case\n");
        return -1;
    }
    else
    {
        // printf("%d\n", t.tableau[y - 1][x - 1]);
        return t.tableau[y - 1][x - 1];
    }
}

void ajouteCaseDevoile(structCaseDevoile *caseDevoile, int x1, int y1, int x2, int y2)
{
    caseDevoile->tableau[caseDevoile->indice][0] = x1;
    caseDevoile->tableau[caseDevoile->indice][1] = y1;
    caseDevoile->tableau[caseDevoile->indice][2] = x2;
    caseDevoile->tableau[caseDevoile->indice][3] = y2;
    caseDevoile->indice += 1;
}

void devoileCase(int col, int row, structCaseDevoile *caseDevoile)
{
    if (etatBoutonSouris() == GaucheAppuye)
    {
        couleurCourante(0, 0, 0);
        rectangle((col - 1) * 30 + 50, (row - 1) * 30 + 50, (col - 1) * 30 + 80, (row - 1) * 30 + 80);
        ajouteCaseDevoile(caseDevoile, (col - 1) * 30 + 50, (row - 1) * 30 + 50, (col - 1) * 30 + 80, (row - 1) * 30 + 80);
    }
}

void dessineCaseDevoile(structCaseDevoile *caseDevoile)
{
    for (int i = 0; i < sizeof(caseDevoile->tableau); i++)
    {
        if (caseDevoile->tableau[i][3] != 0) //[3] est Y2, qui ne pourra jamais etre nul
        {
            rectangle(caseDevoile->tableau[i][0], caseDevoile->tableau[i][1], caseDevoile->tableau[i][2], caseDevoile->tableau[i][3]);
        }
        else
        {
            break;
        }
    }
}

void afficheCaseDevoile(structCaseDevoile *caseDevoile)
{
    for (int i = 0; i < sizeof(caseDevoile->tableau); i++)
    {
        if (caseDevoile->tableau[i][3] != 0) //[3] est Y2, qui ne pourra jamais etre nul
        {
            printf("X1 : %d\n", caseDevoile->tableau[i][0]);
            printf("Y1 : %d\n", caseDevoile->tableau[i][1]);
            printf("X2 : %d\n", caseDevoile->tableau[i][2]);
            printf("Y1 : %d\n", caseDevoile->tableau[i][3]);
        }
        else
        {
            break;
        }
    }
}