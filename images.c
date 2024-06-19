#include <stdlib.h>        // Pour pouvoir utiliser exit()
#include <stdio.h>         // Pour pouvoir utiliser printf()
#include <math.h>          // Pour pouvoir utiliser sin() et cos()
#include "GFXLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXLib/ESLib.h"
#include "images.h"
#include "grille.h"
#include "tableau.h"

void initImages(DonneesImageRGB **listeImages)
{
    listeImages[0] = lisBMPRGB("images/0.bmp");
    listeImages[1] = lisBMPRGB("images/1.bmp");
    listeImages[2] = lisBMPRGB("images/2.bmp");
    listeImages[3] = lisBMPRGB("images/3.bmp");
    listeImages[4] = lisBMPRGB("images/4.bmp");
    listeImages[5] = lisBMPRGB("images/5.bmp");
    listeImages[6] = lisBMPRGB("images/6.bmp");
    listeImages[7] = lisBMPRGB("images/7.bmp");
    listeImages[8] = lisBMPRGB("images/8.bmp");
    listeImages[9] = lisBMPRGB("images/bombe.bmp");
    listeImages[10] = lisBMPRGB("images/drapeau.bmp");
    listeImages[11] = lisBMPRGB("images/drapeau_big.bmp");
}

void initAssets(DonneesImageRGB **listeAssets)
{
    listeAssets[0] = lisBMPRGB("assets/asset.bmp");
    listeAssets[1] = lisBMPRGB("assets/asset2.bmp");
    listeAssets[2] = lisBMPRGB("assets/asset3.bmp");
}

void afficheOverlay(int difficulte, DonneesImageRGB **listeAssets)
{
    if (difficulte == 1)
    {
        ecrisImage(largeurFenetre() - 350, 50, listeAssets[0]->largeurImage, listeAssets[0]->hauteurImage, listeAssets[0]->donneesRGB);
    }
    if (difficulte == 2)
    {
        ecrisImage(largeurFenetre() - 350, 50, listeAssets[1]->largeurImage, listeAssets[1]->hauteurImage, listeAssets[1]->donneesRGB);
    }
    if (difficulte == 3)
    {
        ecrisImage(largeurFenetre() - 350, 50, listeAssets[2]->largeurImage, listeAssets[2]->hauteurImage, listeAssets[2]->donneesRGB);
    }
}