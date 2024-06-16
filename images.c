#include <stdlib.h>        // Pour pouvoir utiliser exit()
#include <stdio.h>         // Pour pouvoir utiliser printf()
#include <math.h>          // Pour pouvoir utiliser sin() et cos()
#include "GFXLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GFXLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GFXLib/ESLib.h"
#include "images.h"

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
}