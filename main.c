#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h>  // Pour pouvoir utiliser printf()
#include <math.h>   // Pour pouvoir utiliser sin() et cos()
#include "gfxlib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "gfxlib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "gfxlib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "tableau.h"
 
// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

void afficheGrille(int difficulte, structTab *t)
{
    switch (difficulte)
    {
    case 1:
        redimensionneFenetre(410, 565);
        break;
    case 2:
        redimensionneFenetre(565, 720);
        break;
    case 3:
        redimensionneFenetre(720, 875);
        break;
    }
    couleurCourante(0, 255, 0);
    int x1 = 50, y1 = 50, x2 = 80, y2 = 80;
    for (int i = 0; i < t->cols; ++i)
    {
        for (int j = 0; j < t->rows; ++j)
        {
            rectangle(x1, y1, x2, y2);
            x1 += 31, x2 += 31;
        }
        x1 = 50, x2 = 80;
        y1 += 31, y2 += 31;
    }
}

int main(int argc, char **argv)
{
    initialiseGfx(argc, argv);

    prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);

    /* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
        qui elle-meme utilise fonctionAffichage ci-dessous */
    lanceBoucleEvenements();

    // afficheGrille(difficulte);


    return 0;
}

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
    int difficulte = 1;
    structTab t;
    t = creeTab(difficulte);
    afficheGrille(difficulte, &t);
}
