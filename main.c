#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h>  // Pour pouvoir utiliser printf()
#include <math.h>   // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include "GFXLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXLib/ESLib.h"  // Pour utiliser valeurAleatoire()
#include "tableau.h"
#include "grille.h"
#include "images.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

int main(int argc, char **argv)
{
    initialiseGfx(argc, argv);

    prepareFenetreGraphique("Demineur", LargeurFenetre, HauteurFenetre);

    lanceBoucleEvenements();

    return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
    static bool firstClic = 0;
    static int difficulte = 3;
    static int peutJouer = 0;
    static int mort = 0;
    static int drapeauxActuels;
    static int totalDrapeaux;
    static int debutPartie;
    static structTab t = {0};
    static structTab tabMask = {0};
    static structTab tabDrap = {0};
    static structCaseDevoile caseDevoile = {0};
    static DonneesImageRGB *listeImages[12] = {0};
    static DonneesImageRGB *listeAssets[12] = {0};

    switch (evenement)
    {
    case Initialisation:
        t = creeTab(difficulte);
        tabMask = creeTabMask(t);
        tabDrap = creeTabMask(t);
        initImages(listeImages);
        initAssets(listeAssets);
        initCaseDevoile(&caseDevoile, t.cols * t.rows);
        debutPartie = time(NULL);
        demandeTemporisation(20);
        break;

    case Temporisation:
        rafraichisFenetre();
        break;

    case Affichage:
        afficheGrille(difficulte, &t);
        afficheOverlay(difficulte, listeAssets);
        dessineCaseDevoile(&caseDevoile, listeImages);
        dessineDrap(tabDrap, listeImages);
        afficheDrap(drapeauxActuels, totalDrapeaux, firstClic, listeImages);
        afficheTemps(debutPartie);
        afficheMort(mort, difficulte, listeAssets);
        afficheGagne(drapeauxActuels, totalDrapeaux, t, tabDrap, difficulte, listeAssets, &peutJouer);
        break;

    case Clavier:
        break;
    case ClavierSpecial:
        break;

    case BoutonSouris:
        switch (etatBoutonSouris())
        {
        case GaucheAppuye:
            if (firstClic == false && estDansTab(t, getCol(abscisseSouris()), getRow(ordonneeSouris())))
            {
                remplirTabMines(&t);
                meursPasAuDebut(getCol(abscisseSouris()), getRow(ordonneeSouris()), &t);
                remplirTabChiffres(&t);
                initCaseDevoile(&caseDevoile, 1000);
                initDrap(t, &drapeauxActuels, &totalDrapeaux);
                firstClic = true;
                peutJouer = 1;
            }
            devoileCase(getCol(abscisseSouris()), getRow(ordonneeSouris()), &caseDevoile, &t, &tabMask, &tabDrap, firstClic, &peutJouer, &mort);
            difficulte = choisirDifficulte(difficulte, &t, &tabMask, &tabDrap, &caseDevoile, &firstClic, &drapeauxActuels, &totalDrapeaux, &debutPartie, &mort);
            rejouer(difficulte, &t, &tabMask, &tabDrap, &caseDevoile, &firstClic, &drapeauxActuels, &totalDrapeaux, &debutPartie, &mort);
            break;
        case GaucheRelache:
            break;
        case DroiteAppuye:
            if (firstClic && peutJouer)
            {
                if (estDansTab(t, getCol(abscisseSouris()), getRow(ordonneeSouris())) && tabMask.tableau[getRow(ordonneeSouris())][getCol(abscisseSouris())] == 0 && tabDrap.tableau[getRow(ordonneeSouris())][getCol(abscisseSouris())] == 0 && drapeauxActuels < totalDrapeaux)
                {
                    tabDrap.tableau[getRow(ordonneeSouris())][getCol(abscisseSouris())] = 1;
                    drapeauxActuels++;
                    break;
                }
                if (estDansTab(t, getCol(abscisseSouris()), getRow(ordonneeSouris())) && tabMask.tableau[getRow(ordonneeSouris())][getCol(abscisseSouris())] == 0 && tabDrap.tableau[getRow(ordonneeSouris())][getCol(abscisseSouris())] != 0)
                {
                    tabDrap.tableau[getRow(ordonneeSouris())][getCol(abscisseSouris())] = 0;
                    drapeauxActuels--;
                    break;
                }
                else
                {
                    tabDrap.tableau[getRow(ordonneeSouris())][getCol(abscisseSouris())] = 0;
                }
            }
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
