#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tableau.h"

structTab creeTab(int difficulty)
{
    structTab t;
    srand(time(NULL));
    switch (difficulty)
    {
    case 1:
        t.rows = 15;
        t.cols = 10;
        break;
    case 2:
        t.rows = 20;
        t.cols = 15;
        break;
    case 3:
        t.rows = 25;
        t.cols = 20;
        break;
    default:
        printf("Difficulté invalide.\n");
        t.rows = 0;
        t.cols = 0;
        break;
    }

    for (int i = 0; i < t.rows; i++)
    {
        for (int j = 0; j < t.cols; j++)
        {
            t.tableau[i][j] = 0;
        }
    }

    return t;
}

void afficheTab(structTab t)
{
    int **tableauTMP = (int **)malloc(t.rows * sizeof(int *));
    for (int i = 0; i < t.rows; i++)
    {
        tableauTMP[i] = (int *)malloc(t.cols * sizeof(int));
    }

    for (int i = 0; i < t.rows; i++)
    {
        for (int j = 0; j < t.cols; j++)
        {
            tableauTMP[t.rows - i - 1][j] = t.tableau[i][j];
        }
    }

    for (int i = 0; i < t.rows; i++)
    {
        for (int j = 0; j < t.cols; j++)
        {
            printf("%d", tableauTMP[i][j]);
        }
        printf("\n");
    }

    // Libérer la mémoire allouée dynamiquement
    for (int i = 0; i < t.rows; i++)
    {
        free(tableauTMP[i]);
    }
    free(tableauTMP);
}

void remplirTabMines(structTab *t)
{
    srand(time(NULL));
    int tmp = 0;
    for (int i = 0; i < t->rows; i++)
    {
        for (int j = 0; j < t->cols; j++)
        {
            tmp = rand() % 10;
            if (tmp < 3)
            {
                t->tableau[i][j] = 9;
            }
            else
            {
                t->tableau[i][j] = 0;
            }
        }
    }
}

void remplirTabChiffres(structTab *t)
{
    int cmbBombes = 0;
    for (int i = 0; i < t->rows; i++)
    {
        for (int j = 0; j < t->cols; j++)
        {
            cmbBombes = 0;
            switch (t->tableau[i][j])
            {
            case 0:
                // Haut
                if (i > 0 && t->tableau[i - 1][j] == 9)
                {
                    cmbBombes++;
                }

                // Bas
                if (i < t->rows - 1 && t->tableau[i + 1][j] == 9)
                {
                    cmbBombes++;
                }

                // Gauche
                if (j > 0 && t->tableau[i][j - 1] == 9)
                {
                    cmbBombes++;
                }

                // Droite
                if (j < t->cols - 1 && t->tableau[i][j + 1] == 9)
                {
                    cmbBombes++;
                }

                // Diagonale haut-gauche
                if (i > 0 && j > 0 && t->tableau[i - 1][j - 1] == 9)
                {
                    cmbBombes++;
                }

                // Diagonale haut-droite
                if (i > 0 && j < t->cols - 1 && t->tableau[i - 1][j + 1] == 9)
                {
                    cmbBombes++;
                }

                // Diagonale bas-gauche
                if (i < t->rows - 1 && j > 0 && t->tableau[i + 1][j - 1] == 9)
                {
                    cmbBombes++;
                }

                // Diagonale bas-droite
                if (i < t->rows - 1 && j < t->cols - 1 && t->tableau[i + 1][j + 1] == 9)
                {
                    cmbBombes++;
                }
                t->tableau[i][j] = cmbBombes;
                break;

            default:
                break;
            }
        }
    }
}