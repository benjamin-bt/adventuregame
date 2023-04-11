#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "common.h"
#include "dir.h"
#include "display.h"
#include "playstate.h"
#include "place.h"

void showPlaceDetails(struct PlayState *playState)
{
    struct Place *currentPlace = &playState->places[playState->currentPlaceId];

    if (!currentPlace->isVisited)
    {
        if (strlen(currentPlace->asciiart) > 0)
        {
            displayAsciiArt(playState, currentPlace->asciiart);
        }

        printf("%s\r\n", currentPlace->description);
        currentPlace->isVisited = true;
    }
    else
    {
        printf("%s\r\n", currentPlace->shortdescription);
    }
}

void readPlacesFromFile(struct PlayState *playState)
{
    char folder[255];
    sprintf(folder, "%s%s\\places\\", playState->dataRoot, playState->currentQuest);

    playState->numberOfPlaces = countFilesInFolder(folder);

    playState->places = (struct Place*)malloc ((playState->numberOfPlaces + 1) * sizeof(struct Place));

    for (int i=1; i<=playState->numberOfPlaces; i++)
    {
        readPlaceFromFile(folder, i, playState->places + i);
    }
}

void readPlaceFromFile(char *folder, int i, struct Place *place)
{
    char filename[255];
    FILE *fp;
    char buffer[255];

    sprintf(filename, "%s%d.place", folder, i);
    fp = fopen(filename, "r");

    fgets(buffer, sizeof(buffer), fp);
    strncpy(place->title, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(place->shortdescription, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(place->description, buffer, max(strlen(buffer)-1,0));

    fgets(buffer,  sizeof(buffer), fp);
    strncpy(place->asciiart, buffer, max(strlen(buffer)-1,0));

    fscanf(fp, "%d %d %d %d", &place->directions[0], &place->directions[1], &place->directions[2], &place->directions[3]);

    int safeplace;
    fscanf(fp, "%d", &safeplace);
    place->isSafePlace = (safeplace != 0);

    int beHereToWin;
    fscanf(fp, "%d", &beHereToWin);
    place->beHereToWin = (beHereToWin != 0);

    place->isVisited = false;

    fclose(fp);
}
