// images.h
#ifndef IMAGES_H
#define IMAGES_H

#include "GFXLib/BmpLib.h"

void initImages(DonneesImageRGB **listeImages);
void initAssets(DonneesImageRGB **listeAssets);
void afficheOverlay(int difficulte, DonneesImageRGB **listeAssets);

#endif