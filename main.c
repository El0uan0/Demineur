#include <stdlib.h>        // Pour pouvoir utiliser exit()
#include <stdio.h>         // Pour pouvoir utiliser printf()
#include <math.h>          // Pour pouvoir utiliser sin() et cos()
#include "GFXLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXLib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "tableau.h"
#include "grille.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

int main(int argc, char **argv)
{
    initialiseGfx(argc, argv);

    prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);

    /* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
        qui elle-meme utilise fonctionAffichage ci-dessous */
    lanceBoucleEvenements();

    return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
    static int difficulte = 3;
    static structTab t;
    static structTab tabMask;
    static structCaseDevoile caseDevoile;

    switch (evenement)
    {
    case Initialisation:
        t = creeTab(difficulte);
        tabMask = creeTabMask(t);
        remplirTabMines(&t);
        remplirTabChiffres(&t);
        initCaseDevoile(&caseDevoile, 1000);
        demandeTemporisation(20);
        afficheTab(t);
        break;

    case Temporisation:
        rafraichisFenetre();
        break;

    case Affichage:
        afficheGrille(difficulte, &t);
        devoileCase(getCol(abscisseSouris()), getRow(ordonneeSouris()), &caseDevoile, &t, &tabMask);
        dessineCaseDevoile(&caseDevoile);
        break;

    case Clavier:
        break;

    case ClavierSpecial:
        break;

    case BoutonSouris:
        switch (etatBoutonSouris())
        {
        case GaucheAppuye:
            break;
        case GaucheRelache:
            break;
        case DroiteAppuye:
        case DroiteRelache:
            break;
        case MilieuAppuye:
        case MilieuRelache:
            break;
        case ScrollDown:
            break;
        case ScrollUp:
            break;
        case ScrollRight:
            break;
        case ScrollLeft:
            break;
        }
        break;
    case Souris:
        break;

    case Inactivite:
        break;

    case Redimensionnement:
        break;
    }
}
