#ifndef PLACE_H
#define PLACE_H

#include <stdbool.h>

struct Place
{
    char title[32];
    char shortdescription[255];
    char description[255];
    char asciiart[255];
    int directions[4];			// Ha 0 akkor oda nem mehet
    bool isSafePlace;           // true -> nem találkozhat ellenséggel
    bool isVisited;
    bool beHereToWin;

};

void showPlaceDetails(struct PlayState *playState);
void readPlacesFromFile(struct PlayState *playState);
void readPlaceFromFile(char *folder, int i, struct Place *place);

#endif
